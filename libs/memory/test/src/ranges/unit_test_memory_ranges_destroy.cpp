/**
 *	@file	unit_test_memory_ranges_destroy.cpp
 *
 *	@brief	ranges::destroy のテスト
 */

#include <hamon/memory/ranges/destroy.hpp>
#include <hamon/memory/ranges/construct_at.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace ranges_destroy_test
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

template <typename Void, typename... Args>
struct invocable_destroy_impl
	: public hamon::false_type {};

template <typename... Args>
struct invocable_destroy_impl<
	hamon::void_t<decltype(hamon::ranges::destroy(hamon::declval<Args>()...))>, Args...>
	: public hamon::true_type {};

template <typename... Args>
using invocable_destroy = invocable_destroy_impl<void, Args...>;

static_assert(!invocable_destroy<X>::value, "");
static_assert(!invocable_destroy<S>::value, "");
static_assert(!invocable_destroy<A>::value, "");
static_assert(!invocable_destroy<B>::value, "");
static_assert(!invocable_destroy<C>::value, "");
static_assert( invocable_destroy<X[2]>::value, "");
static_assert( invocable_destroy<S[2]>::value, "");
static_assert( invocable_destroy<A[2]>::value, "");
static_assert(!invocable_destroy<B[2]>::value, "");
static_assert(!invocable_destroy<C[2]>::value, "");
static_assert(!invocable_destroy<X*>::value, "");
static_assert( invocable_destroy<X*, X*>::value, "");
static_assert( invocable_destroy<test_input_range<X>>::value, "");
static_assert( invocable_destroy<test_input_range<A>>::value, "");
static_assert(!invocable_destroy<test_input_range<B>>::value, "");
static_assert(!invocable_destroy<test_input_range<C>>::value, "");
static_assert( invocable_destroy<test_input_range<X>::iterator, test_input_range<X>::sentinel>::value, "");
static_assert(!invocable_destroy<test_input_range<X>::iterator, test_input_range<A>::sentinel>::value, "");
static_assert( invocable_destroy<test_input_range<A>::iterator, test_input_range<A>::sentinel>::value, "");
static_assert(!invocable_destroy<test_input_range<B>::iterator, test_input_range<B>::sentinel>::value, "");
static_assert(!invocable_destroy<test_input_range<C>::iterator, test_input_range<C>::sentinel>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
MEMORY_TEST_CONSTEXPR bool constexpr_test()
{
	{
		constexpr std::size_t num = 2;
		std::allocator<S> alloc;
		S* p = alloc.allocate(num);
		bool destructed[num] = {false, false};
		for (std::size_t i = 0; i < num; ++i)
		{
			hamon::ranges::construct_at(&p[i], &destructed[i]);
		}
		VERIFY(!destructed[0]);
		VERIFY(!destructed[1]);

		using Range = RangeWrapper<S>;
		Range r(p, p + num);
		auto ret = hamon::ranges::destroy(r.begin(), r.end());
		VERIFY(ret == r.end());
		VERIFY( destructed[0]);
		VERIFY( destructed[1]);
		alloc.deallocate(p, num);
	}
	{
		constexpr std::size_t num = 3;
		std::allocator<S> alloc;
		S* p = alloc.allocate(num);
		bool destructed[num] = {false, false, false};
		for (std::size_t i = 0; i < num; ++i)
		{
			hamon::ranges::construct_at(&p[i], &destructed[i]);
		}
		VERIFY(!destructed[0]);
		VERIFY(!destructed[1]);
		VERIFY(!destructed[2]);

		using Range = RangeWrapper<S>;
		Range r(p, p + num);
		auto ret = hamon::ranges::destroy(r);
		VERIFY(ret == r.end());
		VERIFY( destructed[0]);
		VERIFY( destructed[1]);
		VERIFY( destructed[2]);
		alloc.deallocate(p, num);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesDestroyTest)
{
	EXPECT_EQ(0, X::destruct_count);
	{
		X x[3] = {};
		hamon::ranges::destroy(x, x+3);
		EXPECT_EQ(3, X::destruct_count);
	}
	EXPECT_EQ(6, X::destruct_count);

	{
		int x[8] = {};
		hamon::ranges::destroy(x, x+8);
	}

	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_input_range>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_forward_range>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_bidirectional_range>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_random_access_range>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_contiguous_range>());
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ranges_destroy_test

}	// namespace hamon_memory_test
