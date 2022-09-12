﻿/**
 *	@file	unit_test_functional_ranges_greater_equal.cpp
 *
 *	@brief	ranges::greater_equal のテスト
 */

#include <hamon/functional/ranges/greater_equal.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable_r.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_greater_equal_test
{

struct X { };
int operator==(X, X) { return 2; }
int operator!=(X, X) { return 0; }
int operator<(X, X) noexcept { return 0; }
int operator>(X, X) { return 0; }
int operator<=(X, X) { return 3; }
int operator>=(X, X) { return 4; }

GTEST_TEST(FunctionalTest, RangesGreaterEqualTest)
{
	using F = hamon::ranges::greater_equal;
	static_assert( std::is_default_constructible<F>::value, "");
	static_assert( std::is_copy_constructible<F>::value, "");
	static_assert( std::is_move_constructible<F>::value, "");
	static_assert( std::is_copy_assignable<F>::value, "");
	static_assert( std::is_move_assignable<F>::value, "");

	static_assert(!hamon::is_invocable<F>::value, "");
	static_assert(!hamon::is_invocable<F, int&>::value, "");
	static_assert(!hamon::is_invocable<F, int, void>::value, "");
	static_assert(!hamon::is_invocable<F, int, void*>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, F&, int&, int>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, F, const long&, char>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, const F&, short, int&>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, const F, const char, char>::value, "");

	static_assert( has_is_transparent<F>::value, "");

	static_assert( hamon::ranges::greater_equal{}(99, 99.0), "");
	static_assert( hamon::ranges::greater_equal{}(99.01, 99), "");
	static_assert(!hamon::ranges::greater_equal{}(99, 140L), "");

	{
		F f;
		int a[2]{};
		EXPECT_TRUE( f(&a, (void*)&a[0]));
		EXPECT_TRUE( f((void*)&a[1], &a));
		EXPECT_TRUE( f(&a + 1, (void*)(a + 1)));
		EXPECT_TRUE(!f(&a, (void*)(a + 1)));
	}

	static_assert(hamon::is_nothrow_invocable_r<bool, F&, X, X>::value, "");

	{
		X x;
		F f;
		EXPECT_TRUE(f(x, x));
	}
}

}	// namespace ranges_greater_equal_test

}	// namespace hamon_functional_test