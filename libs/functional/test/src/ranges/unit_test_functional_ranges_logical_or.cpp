/**
 *	@file	unit_test_functional_ranges_logical_or.cpp
 *
 *	@brief	ranges::logical_or のテスト
 */

#include <hamon/functional/ranges/logical_or.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "functional_test.hpp"

namespace hamon_functional_test
{

namespace ranges_logical_or_test
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

constexpr B operator||(B const& lhs, B const& rhs)
{
	return {lhs.value || rhs.value};
}

GTEST_TEST(FunctionalTest, RangesLogicalOrTest)
{
	using F = hamon::ranges::logical_or;

	static_assert( has_is_transparent<F>::value, "");

	static_assert( hamon::is_default_constructible<F>::value, "");
	static_assert( hamon::is_copy_constructible<F>::value, "");
	static_assert( hamon::is_move_constructible<F>::value, "");
	static_assert( std::is_copy_assignable<F>::value, "");
	static_assert( std::is_move_assignable<F>::value, "");

	static_assert(!hamon::is_invocable<F>::value, "");
	static_assert(!hamon::is_invocable<F, int&>::value, "");
	static_assert(!hamon::is_invocable<F, int, void>::value, "");
	static_assert( hamon::is_invocable<F, int, void*>::value, "");
	static_assert( hamon::is_invocable<F, int*, void*>::value, "");
	static_assert( hamon::is_invocable<F, int, int>::value, "");
	static_assert( hamon::is_invocable<F, int, float>::value, "");
	static_assert( hamon::is_invocable<F, float, int>::value, "");
	static_assert( hamon::is_invocable<F, float, float>::value, "");

	static_assert( hamon::is_nothrow_invocable<F, int, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, int, float>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, float, int>::value, "");
	static_assert( hamon::is_nothrow_invocable<F, float, float>::value, "");

	static_assert(F{}(0, 0) == false, "");
	static_assert(F{}(1, 0) == true, "");
	static_assert(F{}(0, 1) == true, "");
	static_assert(F{}(1, 1) == true, "");

	static_assert(F{}(false, false) == false, "");
	static_assert(F{}(true , false) == true, "");
	static_assert(F{}(false, true ) == true, "");
	static_assert(F{}(true , true ) == true, "");

	static_assert(!hamon::is_invocable<F, A, A>::value, "");
	static_assert(!hamon::is_invocable<F, A, B>::value, "");
	static_assert(!hamon::is_invocable<F, B, A>::value, "");
	static_assert( hamon::is_invocable<F, B, B>::value, "");

	static_assert(F{}(B{false}, B{false}).value == false, "");
	static_assert(F{}(B{true }, B{false}).value == true, "");
	static_assert(F{}(B{false}, B{true }).value == true, "");
	static_assert(F{}(B{true }, B{true }).value == true, "");
}

}	// namespace ranges_logical_or_test

}	// namespace hamon_functional_test
