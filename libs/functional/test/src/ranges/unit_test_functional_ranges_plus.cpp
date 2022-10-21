﻿/**
 *	@file	unit_test_functional_ranges_plus.cpp
 *
 *	@brief	ranges::plus のテスト
 */

#include <hamon/functional/ranges/plus.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_plus_test
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

constexpr B operator+(B const& lhs, B const& rhs)
{
	return {lhs.value + rhs.value};
}

GTEST_TEST(FunctionalTest, RangesPlusTest)
{
	using F = hamon::ranges::plus;

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

	static_assert(F{}( 10,  3) ==  13, "");
	static_assert(F{}( 10, -3) ==   7, "");
	static_assert(F{}(-10,  3) ==  -7, "");
	static_assert(F{}(-10, -3) == -13, "");

	static_assert(F{}( 2.5,  5) ==  7.5, "");
	static_assert(F{}( 2.5, -5) == -2.5, "");
	static_assert(F{}(-2.5,  5) ==  2.5, "");
	static_assert(F{}(-2.5, -5) == -7.5, "");

	static_assert(F{}( 3,  1.5f) ==  4.5, "");
	static_assert(F{}( 3, -1.5f) ==  1.5, "");
	static_assert(F{}(-3,  1.5f) == -1.5, "");
	static_assert(F{}(-3, -1.5f) == -4.5, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{42}, B{5}).value == 47, "");
}

}	// namespace ranges_plus_test

}	// namespace hamon_functional_test
