/**
 *	@file	unit_test_memory_ranges_destroy_n.cpp
 *
 *	@brief	ranges::destroy_n のテスト
 */

#include <hamon/memory/ranges/destroy_n.hpp>
#include <hamon/memory/ranges/construct_at.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace ranges_destroy_n_test
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
struct invocable_destroy_n_impl
	: public hamon::false_type {};

template <typename... Args>
struct invocable_destroy_n_impl<
	hamon::void_t<decltype(hamon::ranges::destroy_n(hamon::declval<Args>()...))>, Args...>
	: public hamon::true_type {};

template <typename... Args>
using invocable_destroy_n = invocable_destroy_n_impl<void, Args...>;

static_assert(!invocable_destroy_n<X>::value, "");
static_assert(!invocable_destroy_n<X, int>::value, "");
static_assert( invocable_destroy_n<X*, int>::value, "");
static_assert( invocable_destroy_n<A*, int>::value, "");
static_assert(!invocable_destroy_n<B*, int>::value, "");
static_assert(!invocable_destroy_n<C*, int>::value, "");
static_assert(!invocable_destroy_n<test_input_range<X>, int>::value, "");
static_assert( invocable_destroy_n<test_input_range<X>::iterator, int>::value, "");
static_assert(!invocable_destroy_n<test_input_range<X>::iterator, test_input_range<X>::sentinel>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
MEMORY_TEST_CONSTEXPR bool constexpr_test()
{
	constexpr std::size_t num = 3;
	hamon::allocator<S> alloc;
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
	auto ret = hamon::ranges::destroy_n(r.begin(), num);
	VERIFY(ret == r.end());
	VERIFY( destructed[0]);
	VERIFY( destructed[1]);
	VERIFY( destructed[2]);
	alloc.deallocate(p, num);
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesDestroyNTest)
{
	EXPECT_EQ(0, X::destruct_count);
	{
		X x[3] = {};
		auto ret = hamon::ranges::destroy_n(x, 3);
		EXPECT_TRUE(ret == x+3);
		EXPECT_EQ(3, X::destruct_count);
	}
	EXPECT_EQ(6, X::destruct_count);

	{
		int x[8] = {};
		auto ret = hamon::ranges::destroy_n(x, 8);
		EXPECT_TRUE(ret == x+8);
	}

	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_input_range>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_forward_range>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_bidirectional_range>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_random_access_range>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(constexpr_test<test_contiguous_range>());
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ranges_destroy_n_test

}	// namespace hamon_memory_test
