/**
 *	@file	unit_test_functional_ranges_bit_not.cpp
 *
 *	@brief	ranges::bit_not のテスト
 */

#include <hamon/functional/ranges/bit_not.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_bit_not_test
{

struct A
{
	std::uint32_t value = 0;
};

struct B
{
	std::uint32_t value = 0;
	constexpr B(std::uint32_t v) : value(v) {}
};

constexpr B operator~(B const& x)
{
	return {~x.value};
}

GTEST_TEST(FunctionalTest, RangesBitNotTest)
{
	using F = hamon::ranges::bit_not;

	static_assert( has_is_transparent<F>::value, "");

	static_assert( hamon::is_default_constructible<F>::value, "");
	static_assert( std::is_copy_constructible<F>::value, "");
	static_assert( std::is_move_constructible<F>::value, "");
	static_assert( std::is_copy_assignable<F>::value, "");
	static_assert( std::is_move_assignable<F>::value, "");

	static_assert(!hamon::is_invocable<F>::value, "");
	static_assert( hamon::is_invocable<F, int&>::value, "");
	static_assert(!hamon::is_invocable<F, int, void>::value, "");
	static_assert(!hamon::is_invocable<F, int, void*>::value, "");
	static_assert(!hamon::is_invocable<F, int*, void*>::value, "");
	static_assert(!hamon::is_invocable<F, int, int>::value, "");

	static_assert( hamon::is_invocable<F, int>::value, "");
	static_assert(!hamon::is_invocable<F, float>::value, "");

	static_assert( hamon::is_nothrow_invocable<F, int>::value, "");

	static_assert(F{}(std::uint32_t(0xFA)) == std::uint32_t(0xFFFFFF05), "");

	static_assert(!hamon::is_invocable<F, A>::value, "");
	static_assert( hamon::is_invocable<F, B>::value, "");

	static_assert(F{}(B{0x1234}).value == std::uint32_t(0xFFFFEDCB), "");
}

}	// namespace ranges_bit_not_test

}	// namespace hamon_functional_test
