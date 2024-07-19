/**
 *	@file	unit_test_memory_ranges_destroy_at.cpp
 *
 *	@brief	ranges::destroy_at のテスト
 */

#include <hamon/memory/ranges/destroy_at.hpp>
#include <hamon/memory/ranges/construct_at.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace ranges_destroy_at_test
{

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
#define MEMORY_TEST_CONSTEXPR				constexpr
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

struct X
{
	int value;
	static int destruct_count;
	~X()
	{
		++destruct_count;
	}
};

int X::destruct_count = 0;

struct S
{
	bool* m_destructed;

	constexpr S(bool* p) : m_destructed(p) {}

	HAMON_CXX20_CONSTEXPR ~S() { *m_destructed = true; }
};

struct A
{
	~A(){}
};

struct B
{
	~B()noexcept(false){}
};

struct C
{
private:
	~C(){}
};

template <typename T, typename = void>
struct invocable_destroy_at
	: public hamon::false_type {};

template <typename T>
struct invocable_destroy_at<
	T, hamon::void_t<decltype(hamon::ranges::destroy_at(hamon::declval<T*>()))>>
	: public hamon::true_type {};

static_assert( invocable_destroy_at<X>::value, "");
static_assert( invocable_destroy_at<S>::value, "");
static_assert( invocable_destroy_at<A>::value, "");
static_assert(!invocable_destroy_at<B>::value, "");
static_assert(!invocable_destroy_at<C>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

MEMORY_TEST_CONSTEXPR bool constexpr_test()
{
	std::allocator<S> alloc;
	S* p = alloc.allocate(1);
	bool destructed = false;
	hamon::ranges::construct_at(p, &destructed);
	VERIFY(!destructed);
	hamon::ranges::destroy_at(p);
	VERIFY( destructed);
	alloc.deallocate(p, 1);
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesDestroyAtTest)
{
	X::destruct_count = 0;
	{
		alignas(X) unsigned char buf[sizeof(X)];
		new (buf) X();
		hamon::ranges::destroy_at(reinterpret_cast<X*>(buf));
		EXPECT_EQ(1, X::destruct_count);
	}
	EXPECT_EQ(1, X::destruct_count);

	X::destruct_count = 0;
	{
		X x[4] = {};
		hamon::ranges::destroy_at(&x);
		EXPECT_EQ(4, X::destruct_count);
	}
	EXPECT_EQ(8, X::destruct_count);

	{
		int x = {};
		hamon::ranges::destroy_at(&x);
	}

	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test());
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ranges_destroy_at_test

}	// namespace hamon_memory_test
