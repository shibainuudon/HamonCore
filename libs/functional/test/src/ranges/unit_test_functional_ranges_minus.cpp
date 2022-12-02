/**
 *	@file	unit_test_functional_ranges_minus.cpp
 *
 *	@brief	ranges::minus のテスト
 */

#include <hamon/functional/ranges/minus.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_minus_test
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

constexpr B operator-(B const& lhs, B const& rhs)
{
	return {lhs.value - rhs.value};
}

GTEST_TEST(FunctionalTest, RangesMinusTest)
{
	using F = hamon::ranges::minus;

	static_assert( has_is_transparent<F>::value, "");

	static_assert( std::is_default_constructible<F>::value, "");
	static_assert( std::is_copy_constructible<F>::value, "");
	static_assert( std::is_move_constructible<F>::value, "");
	static_assert( std::is_copy_assignable<F>::value, "");
	static_assert( std::is_move_assignable<F>::value, "");

	static_assert(!hamon::is_invocable<F>::value, "");
	static_assert(!hamon::is_invocable<F, int&>::value, "");
	static_assert(!hamon::is_invocable<F, int, void>::value, "");
	static_assert(!hamon::is_invocable<F, int, void*>::value, "");
	static_assert( hamon::is_invocable<F, int, int>::value, "");
	static_assert( hamon::is_invocable<F, int, double>::value, "");
	static_assert( hamon::is_invocable<F, double, int>::value, "");
	static_assert( hamon::is_invocable<F, double, double>::value, "");

	static_assert( hamon::is_nothrow_invocable<F, int, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, int, double>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, double, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, double, double>::value, "");

	static_assert(F{}( 10,  3) ==   7, "");
	static_assert(F{}( 10, -3) ==  13, "");
	static_assert(F{}(-10,  3) == -13, "");
	static_assert(F{}(-10, -3) ==  -7, "");

	static_assert(F{}( 2.5,  5) == -2.5, "");
	static_assert(F{}( 2.5, -5) ==  7.5, "");
	static_assert(F{}(-2.5,  5) == -7.5, "");
	static_assert(F{}(-2.5, -5) ==  2.5, "");

	static_assert(F{}( 3,  1.5) ==  1.5, "");
	static_assert(F{}( 3, -1.5) ==  4.5, "");
	static_assert(F{}(-3,  1.5) == -4.5, "");
	static_assert(F{}(-3, -1.5) == -1.5, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{42}, B{5}).value == 37, "");
}

}	// namespace ranges_minus_test

}	// namespace hamon_functional_test
