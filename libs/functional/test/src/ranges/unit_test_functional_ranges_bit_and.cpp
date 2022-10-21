/**
 *	@file	unit_test_functional_ranges_bit_and.cpp
 *
 *	@brief	ranges::bit_and のテスト
 */

#include <hamon/functional/ranges/bit_and.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_bit_and_test
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

constexpr B operator&(B const& lhs, B const& rhs)
{
	return {lhs.value & rhs.value};
}

GTEST_TEST(FunctionalTest, RangesBitAndTest)
{
	using F = hamon::ranges::bit_and;

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
	static_assert(!hamon::is_invocable<F, int, float>::value, "");
	static_assert(!hamon::is_invocable<F, float, int>::value, "");
	static_assert(!hamon::is_invocable<F, float, float>::value, "");

	static_assert( hamon::is_nothrow_invocable<F, int, int>::value, "");

	static_assert(F{}(0x0F, 0x35) == 0x05, "");
	static_assert(F{}(0xF0, 0x35) == 0x30, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{0x1234}, B{0xFF00}).value == 0x1200, "");
	static_assert(F{}(B{0x1234}, B{0x0FF0}).value == 0x0230, "");
	static_assert(F{}(B{0x1234}, B{0x00FF}).value == 0x0034, "");
	static_assert(F{}(B{0x1234}, B{0xF0FF}).value == 0x1034, "");
}

}	// namespace ranges_bit_and_test

}	// namespace hamon_functional_test
