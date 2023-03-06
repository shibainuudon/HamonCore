/**
 *	@file	unit_test_functional_ranges_negate.cpp
 *
 *	@brief	ranges::negate のテスト
 */

#include <hamon/functional/ranges/negate.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_negate_test
{

struct A
{
	int value = 0;
};

struct B
{
	int value = 0;
	constexpr B(int v) : value(v) {}
};

constexpr B operator-(B const& x)
{
	return {-x.value};
}

GTEST_TEST(FunctionalTest, RangesNegateTest)
{
	using F = hamon::ranges::negate;

	static_assert( has_is_transparent<F>::value, "");

	static_assert( hamon::is_default_constructible<F>::value, "");
	static_assert( hamon::is_copy_constructible<F>::value, "");
	static_assert( std::is_move_constructible<F>::value, "");
	static_assert( std::is_copy_assignable<F>::value, "");
	static_assert( std::is_move_assignable<F>::value, "");

	static_assert(!hamon::is_invocable<F>::value, "");
	static_assert( hamon::is_invocable<F, int&>::value, "");
	static_assert(!hamon::is_invocable<F, int, void>::value, "");
	static_assert(!hamon::is_invocable<F, int, void*>::value, "");
	static_assert(!hamon::is_invocable<F, int*, void*>::value, "");
	static_assert( hamon::is_invocable<F, int>::value, "");
	static_assert( hamon::is_invocable<F, long>::value, "");
	static_assert( hamon::is_invocable<F, float>::value, "");
	static_assert( hamon::is_invocable<F, double>::value, "");

	static_assert(F{}( 10) == -10, "");
	static_assert(F{}(-10) ==  10, "");

	static_assert(F{}( 2.5) == -2.5, "");
	static_assert(F{}(-2.5) ==  2.5, "");

	static_assert(F{}( 3.0f) == -3.0f, "");
	static_assert(F{}(-3.0f) ==  3.0f, "");

	static_assert(!hamon::is_invocable<F, A>::value, "");
	static_assert( hamon::is_invocable<F, B>::value, "");

	static_assert(F{}(B{42}).value == -42, "");
}

}	// namespace ranges_negate_test

}	// namespace hamon_functional_test
