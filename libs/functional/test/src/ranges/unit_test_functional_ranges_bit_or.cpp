/**
 *	@file	unit_test_functional_ranges_bit_or.cpp
 *
 *	@brief	ranges::bit_or のテスト
 */

#include <hamon/functional/ranges/bit_or.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_bit_or_test
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

constexpr B operator|(B const& lhs, B const& rhs)
{
	return {lhs.value | rhs.value};
}

GTEST_TEST(FunctionalTest, RangesBitOrTest)
{
	using F = hamon::ranges::bit_or;

	static_assert( has_is_transparent<F>::value, "");

	static_assert( hamon::is_default_constructible<F>::value, "");
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

	static_assert(F{}(0x0F, 0x35) == 0x3F, "");
	static_assert(F{}(0xF0, 0x35) == 0xF5, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{0x1234}, B{0xFF00}).value == 0xFF34, "");
	static_assert(F{}(B{0x1234}, B{0x0FF0}).value == 0x1FF4, "");
	static_assert(F{}(B{0x1234}, B{0x00FF}).value == 0x12FF, "");
	static_assert(F{}(B{0x1234}, B{0xF0FF}).value == 0xF2FF, "");
}

}	// namespace ranges_bit_or_test

}	// namespace hamon_functional_test
