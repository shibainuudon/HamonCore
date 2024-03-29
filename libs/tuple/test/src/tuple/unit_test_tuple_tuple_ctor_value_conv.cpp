﻿/**
 *	@file	unit_test_tuple_tuple_ctor_value_conv.cpp
 *
 *	@brief	UTypes&&... を引数に取るコンストラクタのテスト
 *
 *	template<class... UTypes> constexpr explicit(see below) tuple(UTypes&&... u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_value_conv_test
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

struct NoCtor
{
	HAMON_CXX11_CONSTEXPR NoCtor(int x) = delete;
	int n;
};

static_assert(!hamon::is_constructible<hamon::tuple<>, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>, int&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>, int&&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>, int const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit>, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit>, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<NoThrow>,  int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor>,   int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Implicit>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, NoCtor>,   int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor,   Implicit>, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCtor,   NoCtor>,   int, int>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, int, Explicit>, int, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, int, Explicit>, int*, int, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, int, Explicit>, int, int*, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, int, Explicit>, int, int, int*>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<int>, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit>, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit>, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit>, int, int>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, int,      Implicit>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, int,      Implicit>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit, Implicit>, int, int, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, int,      Explicit>, int, int, int>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::tuple<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  Implicit>, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, NoThrow>,  int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, Implicit>, int, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<int,      NoThrow,  NoThrow>,  int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, NoThrow,  NoThrow>,  int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<int,      Implicit, NoThrow>,  int, int, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<int,      NoThrow,  Implicit>, int, int, int>::value, "");

#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
static_assert( hamon::is_constructible<hamon::tuple<hamon::string>, const char*>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<hamon::string const&>, const char*>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<hamon::string const&>, hamon::string>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>, long>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int const&>, long>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int const&>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int const&, int>, long, int>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<int, int const&>, int, long>::value, "");
#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

GTEST_TEST(TupleTest, CtorValueConvTest)
{
	{
		hamon::tuple<hamon::string> t{"hello"};
		EXPECT_TRUE(hamon::adl_get<0>(t) == "hello");
	}
	{
		hamon::tuple<int, hamon::string, float> t{31, "world", 4.5f};
		EXPECT_TRUE(hamon::adl_get<0>(t) == 31);
		EXPECT_TRUE(hamon::adl_get<1>(t) == "world");
		EXPECT_TRUE(hamon::adl_get<2>(t) == 4.5f);
	}
	{
		hamon::tuple<Explicit, Implicit, Explicit> t {8, 9, 10};
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 8);
		EXPECT_TRUE(hamon::adl_get<1>(t).n == 9);
		EXPECT_TRUE(hamon::adl_get<2>(t).n == 10);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t(1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 1);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, float> t = {2, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t) == 2.5f);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<short, char, double> t = {3, 'b', 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t) == 'b');
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t) == 4.5);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit> t{5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 5);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit> t = {6};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 6);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit, Implicit> t {7, 8};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 8);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit, Implicit> t = {7, 8};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 8);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit, Implicit, Explicit> t {8, 9, 10};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 8);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 9);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 10);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit, Implicit, Implicit> t = {11, 12, 13};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 11);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 12);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 13);
	}
}

HAMON_WARNING_POP()

}	// namespace ctor_value_conv_test

}	// namespace hamon_tuple_test
