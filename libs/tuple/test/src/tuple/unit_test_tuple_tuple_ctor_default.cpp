/**
 *	@file	unit_test_tuple_tuple_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 * 
 *	constexpr explicit(see below) tuple();
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
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

struct NoThrow
{
	HAMON_CXX11_CONSTEXPR NoThrow() noexcept : n(3) {}
	int n;
};

struct NoDefault
{
	HAMON_CXX11_CONSTEXPR NoDefault(int x) : n(x) {}
	int n;
};

static_assert( hamon::is_default_constructible<hamon::tuple<>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Implicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<NoThrow>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Explicit, Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Explicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Explicit, NoDefault>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Implicit, Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Implicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Implicit, NoDefault>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, Explicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, NoDefault>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Explicit, Explicit, Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Explicit, Explicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Explicit, Explicit, NoDefault>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Explicit, Implicit, Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Explicit, Implicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Explicit, Implicit, NoDefault>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Explicit, NoDefault, Explicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Explicit, NoDefault, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Explicit, NoDefault, NoDefault>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Implicit, Explicit, Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Implicit, Explicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Implicit, Explicit, NoDefault>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Implicit, Implicit, Explicit>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Implicit, Implicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Implicit, Implicit, NoDefault>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Implicit, NoDefault, Explicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Implicit, NoDefault, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<Implicit, NoDefault, NoDefault>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, Explicit, Explicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, Explicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, Explicit, NoDefault>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, Implicit, Explicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, Implicit, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, Implicit, NoDefault>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, NoDefault, Explicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, NoDefault, Implicit>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::tuple<NoDefault, NoDefault, NoDefault>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<Explicit,  Implicit,  NoThrow>>::value, "");
static_assert( hamon::is_default_constructible<hamon::tuple<int, float, char>>::value, "");

static_assert( hamon::is_implicitly_default_constructible<hamon::tuple<>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::tuple<int>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Explicit>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::tuple<Implicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<NoDefault>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Explicit, Explicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Explicit, Implicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Implicit, Explicit>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::tuple<Implicit, Implicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Explicit, Explicit, Explicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Explicit, Explicit, Implicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Explicit, Implicit, Explicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Explicit, Implicit, Implicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Implicit, Explicit, Explicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Implicit, Explicit, Implicit>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::tuple<Implicit, Implicit, Explicit>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::tuple<Implicit, Implicit, Implicit>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::tuple<int, float, char>>::value, "");

static_assert( hamon::is_nothrow_default_constructible<hamon::tuple<>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<Explicit>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<Implicit>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::tuple<NoThrow>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<NoDefault>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::tuple<NoThrow, NoThrow>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<NoThrow, Implicit>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<Implicit, NoThrow>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<Implicit, Implicit>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::tuple<NoThrow, NoThrow, NoThrow>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::tuple<int, NoThrow, NoThrow>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::tuple<NoThrow, float, NoThrow>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::tuple<NoThrow, NoThrow, char>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<Implicit, NoThrow, NoThrow>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<NoThrow, Implicit, NoThrow>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::tuple<NoThrow, NoThrow, Implicit>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::tuple<int, float, char>>::value, "");

static_assert( hamon::is_trivially_default_constructible<hamon::tuple<>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::tuple<int>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::tuple<Explicit>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::tuple<Implicit>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::tuple<int, float, char>>::value, "");

GTEST_TEST(TupleTest, CtorDefaultTest)
{
	{
		hamon::tuple<> t{};
		(void)t;
	}
	{
		hamon::tuple<std::string> t{};
		EXPECT_TRUE(hamon::adl_get<0>(t) == "");
	}
	{
		hamon::tuple<int, std::string, float> t{};
		EXPECT_TRUE(hamon::adl_get<0>(t) == 0);
		EXPECT_TRUE(hamon::adl_get<1>(t) == "");
		EXPECT_TRUE(hamon::adl_get<2>(t) == 0.0f);
	}
	{
		hamon::tuple<Implicit, Explicit, Implicit> t{};
		EXPECT_TRUE(hamon::adl_get<0>(t).n == 2);
		EXPECT_TRUE(hamon::adl_get<1>(t).n == 1);
		EXPECT_TRUE(hamon::adl_get<2>(t).n == 2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t;
		(void)t;
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, int> t = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 0.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t) == 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, char, int> t{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t) == 0.0f);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t) == 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t) == 0);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit, Explicit, Explicit> t;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 1);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit, Explicit, Implicit> t{};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit, Implicit, Implicit> t = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<0>(t).n == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<1>(t).n == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::adl_get<2>(t).n == 2);
	}
}

}	// namespace ctor_default_test

}	// namespace hamon_tuple_test
