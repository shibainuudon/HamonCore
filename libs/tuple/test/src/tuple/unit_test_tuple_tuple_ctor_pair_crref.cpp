/**
 *	@file	unit_test_tuple_tuple_ctor_pair_crref.cpp
 *
 *	@brief	pair<U1, U2> const&& を引数に取るコンストラクタのテスト
 *
 *	template<class U1, class U2> constexpr explicit(see below) tuple(const pair<U1, U2>&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_pair_crref_test
{

struct Explicit
{
	Explicit(int&) = delete;
	Explicit(int const&) = delete;
	Explicit(int&&) = delete;
	explicit HAMON_CXX11_CONSTEXPR Explicit(int const&& x) : n(x) {}
	int n;
};

struct Implicit
{
	Implicit(int&) = delete;
	Implicit(int const&) = delete;
	Implicit(int&&) = delete;
	HAMON_CXX11_CONSTEXPR Implicit(int const&& x) : n(x) {}
	int n;
};

struct NoThrow
{
	NoThrow(int&) = delete;
	NoThrow(int const&) = delete;
	NoThrow(int&&) = delete;
	HAMON_CXX11_CONSTEXPR NoThrow(int const&& x) noexcept : n(x) {}
	int n;
};

static_assert( hamon::is_constructible<hamon::tuple<short, float>, hamon::pair<int, double> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Explicit>, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, Implicit> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<Implicit, int> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> &&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<short, float>, hamon::pair<int, double> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit>, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> &&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::tuple<short, float>, hamon::pair<int, double> const&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, NoThrow>,  hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::pair<int, int> &&>::value, "");

GTEST_TEST(TupleTest, CtorPairCRRefTest)
{
	{
		hamon::pair<short, float> const t1((short)1, 2.0f);
		hamon::tuple<int, double> const t2(hamon::move(t1));
		EXPECT_EQ(1, hamon::adl_get<0>(t2));
		EXPECT_EQ(2, hamon::adl_get<1>(t2));
	}
	{
		hamon::pair<int, int> const t1(5, 6);
		hamon::tuple<Explicit, Implicit> const t2(hamon::move(t1));
		EXPECT_EQ(5, hamon::adl_get<0>(t2).n);
		EXPECT_EQ(6, hamon::adl_get<1>(t2).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<short, float> t1((short)1, 2.0f);
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, double> t2(hamon::move(t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::adl_get<0>(t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::adl_get<1>(t2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> t1(3, 4);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit, Explicit> t2(hamon::move(t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::adl_get<0>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::adl_get<1>(t2).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> t1(5, 6);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit, Implicit> t2(hamon::move(t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::adl_get<0>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, hamon::adl_get<1>(t2).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> t1(7, 8);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit, Explicit> t2 {hamon::move(t1)};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, hamon::adl_get<0>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, hamon::adl_get<1>(t2).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int> t1(9, 10);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit, Implicit> t2 = {hamon::move(t1)};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::adl_get<0>(t2).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::adl_get<1>(t2).n);
	}
}

}	// namespace ctor_pair_crref_test

}	// namespace hamon_tuple_test
