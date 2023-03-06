/**
 *	@file	unit_test_functional_ranges_not_equal_to.cpp
 *
 *	@brief	ranges::not_equal_to のテスト
 */

#include <hamon/functional/ranges/not_equal_to.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable_r.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <gtest/gtest.h>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_not_equal_to_test
{

struct X { };
int operator==(X, X) noexcept { return 2; }
int operator!=(X, X) { return 0; }

GTEST_TEST(FunctionalTest, RangesNotEqualToTest)
{
	using F = hamon::ranges::not_equal_to;
	static_assert( hamon::is_default_constructible<F>::value, "");
	static_assert( hamon::is_copy_constructible<F>::value, "");
	static_assert( hamon::is_move_constructible<F>::value, "");
	static_assert( hamon::is_copy_assignable<F>::value, "");
	static_assert( hamon::is_move_assignable<F>::value, "");

	static_assert(!hamon::is_invocable<F>::value, "");
	static_assert(!hamon::is_invocable<F, int&>::value, "");
	static_assert(!hamon::is_invocable<F, int, void>::value, "");
	static_assert(!hamon::is_invocable<F, int, void*>::value, "");
	static_assert( hamon::is_invocable<F, int*, void*>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, F&, int&, int>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, F, const long&, char>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, const F&, short, int&>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, const F, const char, char>::value, "");

	static_assert( has_is_transparent<F>::value, "");

	static_assert(!hamon::ranges::not_equal_to{}(99, 99.0), "");
	static_assert( hamon::ranges::not_equal_to{}(99, 99.01), "");
	static_assert( hamon::ranges::not_equal_to{}(99, 140L), "");

	{
		F f;
		int a[2]{};
		EXPECT_TRUE(!f(&a, (void*)&a[0]));
		EXPECT_TRUE( f(&a, (void*)&a[1]));
		EXPECT_TRUE(!f(&a + 1, (void*)(a + 2)));
	}

	static_assert(hamon::is_nothrow_invocable_r<bool, F&, X, X>::value, "");

	{
		X x;
		F f;
		EXPECT_TRUE(!f(x, x));
	}
}

}	// namespace ranges_not_equal_to_test

}	// namespace hamon_functional_test
