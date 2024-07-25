/**
 *	@file	unit_test_memory_ranges_uninitialized_default_construct.cpp
 *
 *	@brief	ranges::uninitialized_default_construct のテスト
 */

#include <hamon/memory/ranges/uninitialized_default_construct.hpp>
#include <hamon/memory/ranges/construct_at.hpp>
#include <hamon/memory/ranges/destroy.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace ranges_uninitialized_default_construct_test
{

struct X
{
	static int count;
	X() { count++; }
	~X() { count--; }
};

int X::count = 0;

struct S
{
	int value;

	HAMON_CXX14_CONSTEXPR S() : value(42) {}
	HAMON_CXX20_CONSTEXPR ~S() { value = 0; }
};

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCtor
{
	static int count;
	static int count_limit;

	ThrowOnCtor()
	{
		if (count >= count_limit)
		{
			throw 0;
		}
		count++;
	}

	~ThrowOnCtor() { count--; }
};

int ThrowOnCtor::count = 0;
int ThrowOnCtor::count_limit = 100;
#endif

struct A
{
	A(){}
};

struct B
{
	B() = delete;
};

template <typename Void, typename... Args>
struct invocable_uninitialized_default_construct_impl
	: public hamon::false_type {};

template <typename... Args>
struct invocable_uninitialized_default_construct_impl<
	hamon::void_t<decltype(hamon::ranges::uninitialized_default_construct(hamon::declval<Args>()...))>, Args...>
	: public hamon::true_type {};

template <typename... Args>
using invocable_uninitialized_default_construct = invocable_uninitialized_default_construct_impl<void, Args...>;

static_assert(!invocable_uninitialized_default_construct<X>::value, "");
static_assert(!invocable_uninitialized_default_construct<X*>::value, "");
static_assert( invocable_uninitialized_default_construct<X*, X*>::value, "");
static_assert( invocable_uninitialized_default_construct<X[2]>::value, "");
static_assert(!invocable_uninitialized_default_construct<test_input_range<X>>::value, "");
static_assert( invocable_uninitialized_default_construct<test_forward_range<X>>::value, "");
static_assert( invocable_uninitialized_default_construct<test_forward_range<A>>::value, "");
static_assert(!invocable_uninitialized_default_construct<test_forward_range<B>>::value, "");
static_assert(!invocable_uninitialized_default_construct<test_input_range<X>::iterator, test_input_range<X>::sentinel>::value, "");
static_assert( invocable_uninitialized_default_construct<test_forward_range<X>::iterator, test_forward_range<X>::sentinel>::value, "");
static_assert( invocable_uninitialized_default_construct<test_forward_range<A>::iterator, test_forward_range<A>::sentinel>::value, "");
static_assert(!invocable_uninitialized_default_construct<test_forward_range<B>::iterator, test_forward_range<B>::sentinel>::value, "");
static_assert(!invocable_uninitialized_default_construct<test_forward_range<A>::iterator, test_forward_range<X>::sentinel>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
bool test()
{
	{
		constexpr std::size_t num = 3;
		std::allocator<S> alloc;
		S* p = alloc.allocate(num);
		using Range = RangeWrapper<S>;
		Range r(p, p + num);

		auto ret = hamon::ranges::uninitialized_default_construct(r.begin(), r.end());
		static_assert(hamon::is_same<decltype(ret), typename Range::iterator>::value, "");
		VERIFY(ret == r.end());
		VERIFY(p[0].value == 42);
		VERIFY(p[1].value == 42);
		VERIFY(p[2].value == 42);
		hamon::ranges::destroy(r.begin(), r.end());
		alloc.deallocate(p, num);
	}
	{
		constexpr std::size_t num = 4;
		std::allocator<S> alloc;
		S* p = alloc.allocate(num);
		using Range = RangeWrapper<S>;
		Range r(p, p + num);

		auto ret = hamon::ranges::uninitialized_default_construct(r);
		static_assert(hamon::is_same<decltype(ret), typename Range::iterator>::value, "");
		VERIFY(ret == r.end());
		VERIFY(p[0].value == 42);
		VERIFY(p[1].value == 42);
		VERIFY(p[2].value == 42);
		hamon::ranges::destroy(r);
		alloc.deallocate(p, num);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, RangesUninitializedDefaultConstructTest)
{
	//EXPECT_TRUE(test<test_input_range>());
	EXPECT_TRUE(test<test_forward_range>());
	EXPECT_TRUE(test<test_bidirectional_range>());
	EXPECT_TRUE(test<test_random_access_range>());
	EXPECT_TRUE(test<test_contiguous_range>());

	{
		X a[100] = {};
		hamon::ranges::destroy(hamon::ranges::begin(a), hamon::ranges::end(a));
		EXPECT_EQ( 0, X::count);

		hamon::ranges::uninitialized_default_construct(a, a + 10);
		EXPECT_EQ(10, X::count);

		hamon::ranges::destroy(a, a + 10);
		EXPECT_EQ( 0, X::count);
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		ThrowOnCtor a[20] = {};
		hamon::ranges::destroy(hamon::ranges::begin(a), hamon::ranges::end(a));
		EXPECT_EQ( 0, ThrowOnCtor::count);

		hamon::ranges::uninitialized_default_construct(a, a + 10);
		EXPECT_EQ(10, ThrowOnCtor::count);

		hamon::ranges::destroy(a, a + 10);
		EXPECT_EQ( 0, ThrowOnCtor::count);

		ThrowOnCtor::count_limit = 5;
		EXPECT_ANY_THROW(hamon::ranges::uninitialized_default_construct(a, a + 10));
		EXPECT_EQ(0, ThrowOnCtor::count);

		EXPECT_NO_THROW(hamon::ranges::uninitialized_default_construct(a, a + 2));
		EXPECT_ANY_THROW(hamon::ranges::uninitialized_default_construct(a, a + 10));
		EXPECT_EQ(2, ThrowOnCtor::count);
	}
#endif
}

}	// namespace ranges_uninitialized_default_construct_test

}	// namespace hamon_memory_test
