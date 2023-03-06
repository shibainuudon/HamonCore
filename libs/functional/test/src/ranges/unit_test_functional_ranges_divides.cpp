/**
 *	@file	unit_test_functional_ranges_divides.cpp
 *
 *	@brief	ranges::divides のテスト
 */

#include <hamon/functional/ranges/divides.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <gtest/gtest.h>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_divides_test
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

constexpr B operator/(B const& lhs, B const& rhs)
{
	return {lhs.value / rhs.value};
}

GTEST_TEST(FunctionalTest, RangesDividesTest)
{
	using F = hamon::ranges::divides;

	static_assert( has_is_transparent<F>::value, "");

	static_assert( hamon::is_default_constructible<F>::value, "");
	static_assert( hamon::is_copy_constructible<F>::value, "");
	static_assert( hamon::is_move_constructible<F>::value, "");
	static_assert( hamon::is_copy_assignable<F>::value, "");
	static_assert( hamon::is_move_assignable<F>::value, "");

	static_assert(!hamon::is_invocable<F>::value, "");
	static_assert(!hamon::is_invocable<F, int&>::value, "");
	static_assert(!hamon::is_invocable<F, int, void>::value, "");
	static_assert(!hamon::is_invocable<F, int, void*>::value, "");
	static_assert(!hamon::is_invocable<F, int*, void*>::value, "");
	static_assert( hamon::is_invocable<F, int, int>::value, "");
	static_assert( hamon::is_invocable<F, int, short>::value, "");
	static_assert( hamon::is_invocable<F, short, int>::value, "");
	static_assert( hamon::is_invocable<F, short, short>::value, "");

	static_assert( hamon::is_nothrow_invocable<F, int, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, int, short>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, short, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, short, short>::value, "");

	static_assert(F{}( 10,  3) ==  3, "");
	static_assert(F{}( 10, -3) == -3, "");
	static_assert(F{}(-10,  3) == -3, "");
	static_assert(F{}(-10, -3) ==  3, "");

	static_assert(F{}( 2.5,  5) ==  0.5, "");
	static_assert(F{}( 2.5, -5) == -0.5, "");
	static_assert(F{}(-2.5,  5) == -0.5, "");
	static_assert(F{}(-2.5, -5) ==  0.5, "");

	static_assert(F{}( 3,  2.0) ==  1.5, "");
	static_assert(F{}( 3, -2.0) == -1.5, "");
	static_assert(F{}(-3,  2.0) == -1.5, "");
	static_assert(F{}(-3, -2.0) ==  1.5, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{42}, B{5}).value == 8, "");
}

}	// namespace ranges_divides_test

}	// namespace hamon_functional_test
