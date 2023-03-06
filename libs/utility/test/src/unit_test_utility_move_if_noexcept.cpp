/**
 *	@file	unit_test_utility_move_if_noexcept.cpp
 *
 *	@brief	move_if_noexcept のテスト
 */

#include <hamon/utility/move_if_noexcept.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <utility>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace move_if_noexcept_test
{

struct A
{
	A(A const&) noexcept(true) {}
	A(A&&)      noexcept(true) {}
};

struct B
{
	B(B const&) noexcept(true) {}
	B(B&&)      noexcept(false) {}
};

struct C
{
	C(C const&) = delete;
	C(C&&)      noexcept(true) {}
};

struct D
{
	D(D const&) = delete;
	D(D&&)      noexcept(false) {}
};

static_assert( hamon::is_nothrow_move_constructible<A>::value, "");
static_assert( hamon::is_copy_constructible<A>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<B>::value, "");
static_assert( hamon::is_copy_constructible<B>::value, "");
static_assert( hamon::is_nothrow_move_constructible<C>::value, "");
static_assert(!hamon::is_copy_constructible<C>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<D>::value, "");
static_assert(!hamon::is_copy_constructible<D>::value, "");

static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<int&>())),       int&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<int const&>())), int const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<A&>())),       A &&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<A const&>())), A const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<B&>())),       B const&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<B const&>())), B const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<C&>())),       C &&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<C const&>())), C const&&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<D&>())),       D &&>::value, "");
static_assert(hamon::is_same<decltype(hamon::move_if_noexcept(std::declval<D const&>())), D const&&>::value, "");

GTEST_TEST(UtilityTest, MoveIfNoexceptTest)
{
	{
		HAMON_CXX11_CONSTEXPR int i1 = 42;
		HAMON_CXX11_CONSTEXPR int i2 = hamon::move_if_noexcept(i1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, i2);
	}
}

}	// namespace move_if_noexcept_test

}	// namespace hamon_utility_test
