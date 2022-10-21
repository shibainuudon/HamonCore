/**
 *	@file	unit_test_functional_ranges_logical_not.cpp
 *
 *	@brief	ranges::logical_not のテスト
 */

#include <hamon/functional/ranges/logical_not.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_logical_not_test
{

struct A
{
	bool value = false;
};

struct B
{
	bool value = false;
	constexpr B(bool v) : value(v) {}
};

constexpr B operator!(B const& lhs)
{
	return {!lhs.value};
}

GTEST_TEST(FunctionalTest, RangesLogicalNotTest)
{
	using F = hamon::ranges::logical_not;

	static_assert( has_is_transparent<F>::value, "");

	static_assert( std::is_default_constructible<F>::value, "");
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
	static_assert( hamon::is_invocable<F, bool>::value, "");
	static_assert( hamon::is_invocable<F, int>::value, "");
	static_assert( hamon::is_invocable<F, float>::value, "");

	static_assert( hamon::is_nothrow_invocable<F, bool>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, float>::value, "");

	static_assert(F{}(0) == true, "");
	static_assert(F{}(1) == false, "");

	static_assert(F{}(false) == true, "");
	static_assert(F{}(true)  == false, "");

	static_assert(!hamon::is_invocable<F, A>::value, "");
	static_assert( hamon::is_invocable<F, B>::value, "");

	static_assert(F{}(B{false}).value == true, "");
	static_assert(F{}(B{true} ).value == false, "");
}

}	// namespace ranges_logical_not_test

}	// namespace hamon_functional_test
