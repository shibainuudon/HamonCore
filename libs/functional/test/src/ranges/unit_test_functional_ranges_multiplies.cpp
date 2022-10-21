/**
 *	@file	unit_test_functional_ranges_multiplies.cpp
 *
 *	@brief	ranges::multiplies のテスト
 */

#include <hamon/functional/ranges/multiplies.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_multiplies_test
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

constexpr B operator*(B const& lhs, B const& rhs)
{
	return {lhs.value * rhs.value};
}

GTEST_TEST(FunctionalTest, RangesMultipliesTest)
{
	using F = hamon::ranges::multiplies;

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
	static_assert(!hamon::is_invocable<F, int*, void*>::value, "");
	static_assert( hamon::is_invocable<F, int, int>::value, "");
	static_assert( hamon::is_invocable<F, int, float>::value, "");
	static_assert( hamon::is_invocable<F, float, int>::value, "");
	static_assert( hamon::is_invocable<F, float, float>::value, "");

	static_assert( hamon::is_nothrow_invocable<F, int, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, int, float>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, float, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, float, float>::value, "");

	static_assert(F{}( 10,  3) ==  30, "");
	static_assert(F{}( 10, -3) == -30, "");
	static_assert(F{}(-10,  3) == -30, "");
	static_assert(F{}(-10, -3) ==  30, "");

	static_assert(F{}( 2.5,  5) ==  12.5, "");
	static_assert(F{}( 2.5, -5) == -12.5, "");
	static_assert(F{}(-2.5,  5) == -12.5, "");
	static_assert(F{}(-2.5, -5) ==  12.5, "");

	static_assert(F{}( 3,  2.0f) ==  6.0, "");
	static_assert(F{}( 3, -2.0f) == -6.0, "");
	static_assert(F{}(-3,  2.0f) == -6.0, "");
	static_assert(F{}(-3, -2.0f) ==  6.0, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{42}, B{5}).value == 210, "");
}

}	// namespace ranges_multiplies_test

}	// namespace hamon_functional_test
