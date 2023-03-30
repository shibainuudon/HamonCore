/**
 *	@file	unit_test_pair_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 * 
 *	constexpr explicit(see below) pair();
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_default_test
{

struct Explicit
{
	explicit HAMON_CXX11_CONSTEXPR Explicit() : n(1) {}
	int n;
};

struct Implicit
{
	HAMON_CXX11_CONSTEXPR Implicit() : n(2) {}
	int n;
};

struct NoDefault
{
	HAMON_CXX11_CONSTEXPR NoDefault(int x) : n(x) {}
	int n;
};

struct NoThrow
{
	HAMON_CXX11_CONSTEXPR NoThrow() noexcept : n(1) {}
	int n;
};

static_assert( hamon::is_default_constructible<hamon::pair<Explicit, Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::pair<Explicit, Implicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::pair<Implicit, Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::pair<Implicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::pair<NoDefault, NoDefault>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::pair<NoDefault, int>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::pair<int,       NoDefault>>::value, "");
static_assert( hamon::is_default_constructible<hamon::pair<int,       int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::pair<NoThrow,   NoThrow>>::value, "");
static_assert( hamon::is_default_constructible<hamon::pair<NoThrow,   int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::pair<int,       NoThrow>>::value, "");
static_assert( hamon::is_default_constructible<hamon::pair<int,       int>>::value, "");

static_assert(!hamon::is_implicitly_default_constructible<hamon::pair<Explicit, Explicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::pair<Explicit, Implicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::pair<Implicit, Explicit>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::pair<Implicit, Implicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::pair<Explicit, int>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::pair<int,      Explicit>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::pair<Implicit, int>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::pair<int,      Implicit>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::pair<int,      int>>::value, "");

static_assert(!hamon::is_nothrow_default_constructible<hamon::pair<Explicit, Explicit>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::pair<Explicit, int>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::pair<int,      Explicit>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::pair<Explicit, NoThrow>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::pair<NoThrow,  Explicit>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::pair<NoThrow,  NoThrow>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::pair<NoThrow,  int>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::pair<int,      NoThrow>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::pair<int,      int>>::value, "");

GTEST_TEST(PairTest, CtorDefaultTest)
{
	{
		hamon::pair<int, int> p;
		EXPECT_EQ(0, p.first);
		EXPECT_EQ(0, p.second);
	}
	{
		hamon::pair<Explicit, Implicit> p{};
		EXPECT_EQ(1, p.first.n);
		EXPECT_EQ(2, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, Explicit> p;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, Implicit> p{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<Implicit, Explicit> p;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<Implicit, Implicit> p = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p.second.n);
	}
}

}	// namespace ctor_default_test

}	// namespace hamon_pair_test
