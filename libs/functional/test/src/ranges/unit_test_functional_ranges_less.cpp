/**
 *	@file	unit_test_functional_ranges_less.cpp
 *
 *	@brief	ranges::less のテスト
 */

#include <hamon/functional/ranges/less.hpp>
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

namespace ranges_less_test
{

struct X { };
int operator==(X, X) { return 2; }
int operator!=(X, X) { return 0; }
int operator<(X, X) noexcept { return 0; }
int operator>(X, X) { return 0; }
int operator<=(X, X) { return 3; }
int operator>=(X, X) { return 4; }

struct Y
{
	operator void* () const;
	operator int() const;
};

GTEST_TEST(FunctionalTest, RangesLessTest)
{
	using F = hamon::ranges::less;
	static_assert( hamon::is_default_constructible<F>::value, "");
	static_assert( hamon::is_copy_constructible<F>::value, "");
	static_assert( hamon::is_move_constructible<F>::value, "");
	static_assert( hamon::is_copy_assignable<F>::value, "");
	static_assert( hamon::is_move_assignable<F>::value, "");

	static_assert(!hamon::is_invocable<F>::value, "");
	static_assert(!hamon::is_invocable<F, int&>::value, "");
	static_assert(!hamon::is_invocable<F, int, void>::value, "");
	static_assert(!hamon::is_invocable<F, int, void*>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, F&, int&, int>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, F, const long&, char>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, const F&, short, int&>::value, "");
	static_assert( hamon::is_nothrow_invocable_r<bool, const F, const char, char>::value, "");

	static_assert( has_is_transparent<F>::value, "");

	static_assert(!hamon::ranges::less{}(99, 99.0), "");
	static_assert( hamon::ranges::less{}(99, 99.01), "");
	static_assert( hamon::ranges::less{}(99, 140L), "");

	{
		F f;
		int a[2]{};
		EXPECT_TRUE(!f(&a, (void*)&a[0]));
		EXPECT_TRUE( f(&a, (void*)&a[1]));
		EXPECT_TRUE(!f(&a + 1, (void*)(a + 2)));
		EXPECT_TRUE( f(&a, (void*)(a + 1)));
	}

	static_assert( hamon::is_nothrow_invocable_r<bool, F&, X, X>::value, "");

	{
		X x;
		F f;
		EXPECT_TRUE(!f(x, x));
	}

	// Y{} == Y{} is ambiguous so ranges::less{}(Y{}, Y{}) should be invalid
	static_assert(!hamon::is_invocable<F&, Y, Y>::value, "");
}

}	// namespace ranges_less_test

}	// namespace hamon_functional_test
