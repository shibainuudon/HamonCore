﻿/**
 *	@file	unit_test_functional_ranges_bit_xor.cpp
 *
 *	@brief	ranges::bit_xor のテスト
 */

#include <hamon/functional/ranges/bit_xor.hpp>
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

namespace ranges_bit_xor_test
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

constexpr B operator^(B const& lhs, B const& rhs)
{
	return {lhs.value ^ rhs.value};
}

GTEST_TEST(FunctionalTest, RangesBitXorTest)
{
	using F = hamon::ranges::bit_xor;

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
	static_assert(!hamon::is_invocable<F, int, float>::value, "");
	static_assert(!hamon::is_invocable<F, float, int>::value, "");
	static_assert(!hamon::is_invocable<F, float, float>::value, "");

	static_assert( hamon::is_nothrow_invocable<F, int, int>::value, "");

	static_assert(F{}(0xFA, 0x47) == 0xBD, "");
	static_assert(F{}(0x35, 0xf0) == 0xC5, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{0xFA}, B{0x47}).value == 0xBD, "");
	static_assert(F{}(B{0x73}, B{0x20}).value == 0x53, "");
}

}	// namespace ranges_bit_xor_test

}	// namespace hamon_functional_test
