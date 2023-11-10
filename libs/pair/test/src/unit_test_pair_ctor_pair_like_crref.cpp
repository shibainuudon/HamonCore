/**
 *	@file	unit_test_pair_ctor_pair_like_crref.cpp
 *
 *	@brief	pair-likeなオブジェクトからのコンストラクタのテスト
 * 
 *  template<pair-like P>
 *	constexpr explicit(see below) pair(P&& p);
 */

#include <hamon/pair.hpp>
#include <hamon/array.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_pair_like_crref_test
{

struct Explicit
{
	Explicit(int&) = delete;
	Explicit(int&&) = delete;
	Explicit(int const&) = delete;
	explicit HAMON_CXX11_CONSTEXPR Explicit(int const&& x) : n(x) {}
	int n;
};

struct Implicit
{
	Implicit(int&) = delete;
	Implicit(int&&) = delete;
	Implicit(int const&) = delete;
	HAMON_CXX11_CONSTEXPR Implicit(int const&& x) : n(x) {}
	int n;
};

struct NoThrow
{
	NoThrow(int&) = delete;
	NoThrow(int&&) = delete;
	NoThrow(int const&) = delete;
	HAMON_CXX11_CONSTEXPR NoThrow(int const&& x) noexcept : n(x) {}
	int n;
};

static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 1> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 1> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int*, 2> const&&>::value, "");

static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> const&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 3> const&&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::pair<short, float>, hamon::array<int, 2> const&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Implicit>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Explicit>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> const&&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::pair<short, float>, hamon::array<int, 2> const&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, NoThrow>,  hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  Implicit>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, Implicit>, hamon::array<int, 2> const&&>::value, "");

GTEST_TEST(PairTest, CtorPairLikeCRRefTest)
{
	{
		hamon::array<int, 2> const a = {1, 2};
		hamon::pair<float, double> const t(hamon::move(a));
		EXPECT_EQ(1, hamon::adl_get<0>(t));
		EXPECT_EQ(2, hamon::adl_get<1>(t));
	}
	{
		hamon::array<int, 2> const a = {3, 4};
		hamon::pair<Explicit, Implicit> const t(hamon::move(a));
		EXPECT_EQ(3, hamon::adl_get<0>(t).n);
		EXPECT_EQ(4, hamon::adl_get<1>(t).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> const a = {1, 2};
		HAMON_CXX11_CONSTEXPR hamon::pair<float, double> const t(hamon::move(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::adl_get<0>(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::adl_get<1>(t));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> const a = {3, 4};
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, NoThrow> const t(hamon::move(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::adl_get<0>(t).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::adl_get<1>(t).n);
	}
}

}	// namespace ctor_pair_like_crref_test

}	// namespace hamon_pair_test
