/**
 *	@file	unit_test_pair_ctor_value_move.cpp
 *
 *	@brief	pair::pair(U1&&, U2&&) のテスト
 * 
 *	template<class U1 = T1, class U2 = T2>
 *	constexpr explicit(see below) pair(U1&& x, U2&& y);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_value_move_test
{

struct Explicit
{
	explicit HAMON_CXX11_CONSTEXPR Explicit(int x) : n(x) {}
	int n;
};

struct Implicit
{
	HAMON_CXX11_CONSTEXPR Implicit(int x) : n(x) {}
	int n;
};

struct NoThrow
{
	HAMON_CXX11_CONSTEXPR NoThrow(int x) noexcept : n(x) {}
	int n;
};

struct ConvertibleToInt
{
	explicit HAMON_CXX11_CONSTEXPR ConvertibleToInt(int x) : n(x) {}
	HAMON_CXX11_CONSTEXPR operator int() const { return n; }
	int n;
};

static_assert( hamon::is_constructible<hamon::pair<Explicit, Explicit>, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Implicit>, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Implicit, Explicit>, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Implicit, Implicit>, int, int>::value, "");
static_assert( hamon::is_constructible<hamon::pair<int, int>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, int, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, Implicit, int>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int, int>, int*, int>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int, int>, Explicit, Explicit>::value, "");
static_assert( hamon::is_constructible<hamon::pair<int, int>, ConvertibleToInt, ConvertibleToInt>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Explicit>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Implicit>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Explicit>, int, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, int, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<int, int>, int, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<int, int>, ConvertibleToInt, ConvertibleToInt>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  Implicit>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, NoThrow>,  int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, Implicit>, int, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<int, int>, int, int>::value, "");

GTEST_TEST(PairTest, CtorValueMoveTest)
{
	{
		hamon::pair<int, int> p(1, 2);
		EXPECT_EQ(1, p.first);
		EXPECT_EQ(2, p.second);
	}
	{
		hamon::pair<Explicit, Implicit> p(3, 4);
		EXPECT_EQ(3, p.first.n);
		EXPECT_EQ(4, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p(1, 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p{3, 4};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p = {5, 6};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, Explicit> p(1, 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, Implicit> p(3, 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<Implicit, Explicit> p{5, 6};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<Implicit, Implicit> p = {7, 8};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, p.second.n);
	}
}

}	// namespace ctor_value_move_test

}	// namespace hamon_pair_test
