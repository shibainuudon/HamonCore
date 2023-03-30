/**
 *	@file	unit_test_pair_ctor_value_copy.cpp
 *
 *	@brief	pair::pair(const T1&, const T2&) のテスト
 * 
 *	constexpr explicit(see below)
 *	pair(const T1& x, const T2& y);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_value_copy_test
{

struct Explicit
{
	explicit HAMON_CXX11_CONSTEXPR Explicit(int x) : n(x) {}
	explicit HAMON_CXX11_CONSTEXPR Explicit(Explicit const& rhs) : n(rhs.n) {}
	int n;
};

struct Implicit
{
	HAMON_CXX11_CONSTEXPR Implicit(int x) : n(x) {}
	HAMON_CXX11_CONSTEXPR Implicit(Implicit const& rhs) : n(rhs.n) {}
	int n;
};

struct NoThrow
{
	HAMON_CXX11_CONSTEXPR NoThrow(NoThrow const& rhs) noexcept : n(rhs.n) {}
	int n;
};

static_assert( hamon::is_constructible<hamon::pair<Explicit, Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Implicit>, Explicit const&, Implicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Implicit, Explicit>, Implicit const&, Explicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Implicit, Implicit>, Implicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, Explicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, Implicit const&, Explicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, Implicit const&, Implicit const&>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Implicit>, Explicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Explicit>, Implicit const&, Explicit const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, Implicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, int>,      Explicit const&, int      const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<int,      Explicit>, int      const&, Explicit const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, int>,      Implicit const&, int      const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<int,      Implicit>, int      const&, Implicit const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<int,      int>,      int      const&, int      const&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  NoThrow const&,  NoThrow const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  Implicit>, NoThrow const&,  Implicit const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, NoThrow>,  Implicit const&, NoThrow const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, Implicit>, Implicit const&, Implicit const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<int,      int>,      int const&,      int const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<int,      Implicit>, int const&,      Implicit const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, int>,      Implicit const&, int const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<int,      NoThrow>,  int const&,      NoThrow const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  int>,      NoThrow const&,  int const&>::value, "");

GTEST_TEST(PairTest, CtorValueCopyTest)
{
	{
		int const x1 = 1;
		int const x2 = 2;
		hamon::pair<int, int> p(x1, x2);
		EXPECT_EQ(1, p.first);
		EXPECT_EQ(2, p.second);
	}
	{
		Explicit const x1(3);
		Implicit const x2(4);
		hamon::pair<Explicit, Implicit> p{x1, x2};
		EXPECT_EQ(3, p.first.n);
		EXPECT_EQ(4, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR int const x1 = 1;
		HAMON_CXX11_CONSTEXPR int const x2 = 2;
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p(x1, x2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR int const x1 = 3;
		HAMON_CXX11_CONSTEXPR int const x2 = 4;
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p{x1, x2};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR int const x1 = 5;
		HAMON_CXX11_CONSTEXPR int const x2 = 6;
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p = {x1, x2};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR Explicit const x1(1);
		HAMON_CXX11_CONSTEXPR Explicit const x2(2);
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, Explicit> p(x1, x2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR Explicit const x1(3);
		HAMON_CXX11_CONSTEXPR Implicit const x2(4);
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, Implicit> p{x1, x2};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR Implicit const x1(5);
		HAMON_CXX11_CONSTEXPR Explicit const x2(6);
		HAMON_CXX11_CONSTEXPR hamon::pair<Implicit, Explicit> p{x1, x2};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR Implicit const x1(7);
		HAMON_CXX11_CONSTEXPR Implicit const x2(8);
		HAMON_CXX11_CONSTEXPR hamon::pair<Implicit, Implicit> p = {x1, x2};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, p.second.n);
	}
}

}	// namespace ctor_value_copy_test

}	// namespace hamon_pair_test
