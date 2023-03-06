/**
 *	@file	unit_test_functional_ranges_modulus.cpp
 *
 *	@brief	ranges::modulus のテスト
 */

#include <hamon/functional/ranges/modulus.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_modulus_test
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

constexpr B operator%(B const& lhs, B const& rhs)
{
	return {lhs.value % rhs.value};
}

GTEST_TEST(FunctionalTest, RangesModulusTest)
{
	using F = hamon::ranges::modulus;

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

	static_assert(F{}( 10,  3) ==  1, "");
	static_assert(F{}( 10, -3) ==  1, "");
	static_assert(F{}(-10,  3) == -1, "");
	static_assert(F{}(-10, -3) == -1, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{42}, B{5}).value == 2, "");
}

}	// namespace ranges_modulus_test

}	// namespace hamon_functional_test
