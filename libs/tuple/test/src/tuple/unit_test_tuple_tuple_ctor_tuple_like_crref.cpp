/**
 *	@file	unit_test_tuple_tuple_ctor_tuple_like_crref.cpp
 *
 *	@brief	tuple-likeなオブジェクトからのコンストラクタのテスト
 *
 *	template<tuple-like UTuple> constexpr explicit(see below) tuple(UTuple&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_tuple_like_crref_test
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

static_assert( hamon::is_constructible<hamon::tuple<short, float>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<short, float>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> &>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> &&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 2> const&&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<short, float>, hamon::array<int, 2> const&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit, Implicit>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit, Implicit>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit, Implicit>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit, Explicit>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> const&&>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<short, float>, hamon::array<int, 2> const&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow,  NoThrow>,  hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, NoThrow,  NoThrow>,  hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  Implicit, NoThrow>,  hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow,  Implicit>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, Implicit, Implicit>, hamon::array<int, 3> const&&>::value, "");
#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

GTEST_TEST(TupleTest, CtorTupleLikeCRRefTest)
{
	{
		hamon::array<int, 2> const a = {1, 2};
		hamon::tuple<float, double> const t(hamon::move(a));
		EXPECT_EQ(1, hamon::adl_get<0>(t));
		EXPECT_EQ(2, hamon::adl_get<1>(t));
	}
	{
		hamon::array<int, 3> const a = {3, 4, 5};
		hamon::tuple<Explicit, Implicit, NoThrow> const t(hamon::move(a));
		EXPECT_EQ(3, hamon::adl_get<0>(t).n);
		EXPECT_EQ(4, hamon::adl_get<1>(t).n);
		EXPECT_EQ(5, hamon::adl_get<2>(t).n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> const a = {1, 2};
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, double> const t(hamon::move(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::adl_get<0>(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::adl_get<1>(t));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 3> const a = {3, 4, 5};
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit, Implicit, NoThrow> const t(hamon::move(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::adl_get<0>(t).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::adl_get<1>(t).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::adl_get<2>(t).n);
	}
}

HAMON_WARNING_POP()

}	// namespace ctor_tuple_like_crref_test

}	// namespace hamon_tuple_test
