/**
 *	@file	unit_test_tuple_tuple_ctor_value_copy.cpp
 *
 *	@brief	Types const&... を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit(see below) tuple(const Types&...);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
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
	HAMON_CXX11_CONSTEXPR NoThrow(int x) : n(x) {}
	HAMON_CXX11_CONSTEXPR NoThrow(Implicit const& rhs) noexcept : n(rhs.n) {}
	int n;
};

struct NoCopy
{
	HAMON_CXX11_CONSTEXPR NoCopy(int x) : n(x) {}
	HAMON_CXX11_CONSTEXPR NoCopy(NoCopy const& rhs) = delete;
	int n;
};

static_assert(!hamon::is_constructible<hamon::tuple<>, int const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<int>, int const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit>, Explicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit>, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy>,   NoCopy   const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit>, Implicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy>,   NoCopy   const&, NoCopy   const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Explicit const&, Explicit const&, Explicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit, Implicit>, Explicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, NoCopy>,   Explicit const&, Explicit const&, NoCopy   const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Implicit, Explicit>, Explicit const&, Implicit const&, Explicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Implicit, Implicit>, Explicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Implicit, NoCopy>,   Explicit const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, NoCopy,   Explicit>, Explicit const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, NoCopy,   Implicit>, Explicit const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, NoCopy,   NoCopy>,   Explicit const&, NoCopy   const&, NoCopy   const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Explicit, Explicit>, Implicit const&, Explicit const&, Explicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Explicit, Implicit>, Implicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, Explicit, NoCopy>,   Implicit const&, Explicit const&, NoCopy   const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Implicit, Explicit>, Implicit const&, Implicit const&, Explicit const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Implicit, Implicit>, Implicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, Implicit, NoCopy>,   Implicit const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, NoCopy,   Explicit>, Implicit const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, NoCopy,   Implicit>, Implicit const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Implicit, NoCopy,   NoCopy>,   Implicit const&, NoCopy   const&, NoCopy   const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   Explicit, Explicit>, NoCopy   const&, Explicit const&, Explicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   Explicit, Implicit>, NoCopy   const&, Explicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   Explicit, NoCopy>,   NoCopy   const&, Explicit const&, NoCopy   const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   Implicit, Explicit>, NoCopy   const&, Implicit const&, Explicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   Implicit, Implicit>, NoCopy   const&, Implicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   Implicit, NoCopy>,   NoCopy   const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   NoCopy,   Explicit>, NoCopy   const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   NoCopy,   Implicit>, NoCopy   const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<NoCopy,   NoCopy,   NoCopy>,   NoCopy   const&, NoCopy   const&, NoCopy   const&>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit>, Explicit const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit>, Implicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<NoCopy>,   NoCopy   const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Explicit const&, Explicit const&, Explicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit, Implicit>, Explicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit, Explicit>, Explicit const&, Implicit const&, Explicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit, Implicit>, Explicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit, Explicit>, Implicit const&, Explicit const&, Explicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit, Implicit>, Implicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit, Explicit>, Implicit const&, Implicit const&, Explicit const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit, Implicit>, Implicit const&, Implicit const&, Implicit const&>::value, "");

static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Explicit>, Explicit const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit>, Implicit const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoCopy>,   NoCopy   const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow>,  NoThrow   const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow, NoThrow, NoThrow>, NoThrow const&, NoThrow const&, NoThrow const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow, NoThrow, Implicit>, NoThrow const&, NoThrow const&, Implicit const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow, Implicit, NoThrow>, NoThrow const&, Implicit const&, NoThrow const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow, Implicit, Implicit>, NoThrow const&, Implicit const&, Implicit const&>::value, "");

GTEST_TEST(TupleTest, CtorValueCopyTest)
{
	using std::get;
	{
		std::string const s = "hello";
		hamon::tuple<std::string> t{s};
		EXPECT_TRUE(get<0>(t) == "hello");
	}
	{
		int const n = 42;
		std::string const s = "world";
		float const f = 2.5f;
		hamon::tuple<int, std::string, float> t{n, s, f};
		EXPECT_TRUE(get<0>(t) == 42);
		EXPECT_TRUE(get<1>(t) == "world");
		EXPECT_TRUE(get<2>(t) == 2.5f);
	}
	{
		Explicit const x1(8);
		Implicit const x2(9);
		hamon::tuple<Explicit, Implicit, Explicit> t {x1, x2, x1};
		EXPECT_TRUE(get<0>(t).n == 8);
		EXPECT_TRUE(get<1>(t).n == 9);
		EXPECT_TRUE(get<2>(t).n == 8);
	}
	{
		HAMON_CXX11_CONSTEXPR int x1 = 1;
		HAMON_CXX11_CONSTEXPR hamon::tuple<int> t(x1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t) == 1);
	}
	{
		HAMON_CXX11_CONSTEXPR int   x1 = 2;
		HAMON_CXX11_CONSTEXPR float x2 = 2.5f;
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, float> t = {x1, x2};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t) == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t) == 2.5f);
	}
	{
		HAMON_CXX11_CONSTEXPR int    x1 = 3;
		HAMON_CXX11_CONSTEXPR char   x2 = 'b';
		HAMON_CXX11_CONSTEXPR double x3 = 4.5;
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, char, double> t = {x1, x2, x3};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t) == 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t) == 'b');
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<2>(t) == 4.5);
	}
	{
		HAMON_CXX11_CONSTEXPR Explicit x1(5);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit> t{x1};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t).n == 5);
	}
	{
		HAMON_CXX11_CONSTEXPR Implicit x1(6);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit> t = {x1};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t).n == 6);
	}
	{
		HAMON_CXX11_CONSTEXPR Implicit x1(7);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit, Implicit> t = {x1, x1};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t).n == 7);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t).n == 7);
	}
	{
		HAMON_CXX11_CONSTEXPR Explicit x1(8);
		HAMON_CXX11_CONSTEXPR Implicit x2(9);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit, Implicit, Explicit> t {x1, x2, x1};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t).n == 8);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t).n == 9);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<2>(t).n == 8);
	}
	{
		HAMON_CXX11_CONSTEXPR Implicit x1(1);
		HAMON_CXX11_CONSTEXPR Implicit x2(2);
		HAMON_CXX11_CONSTEXPR Implicit x3(3);
		HAMON_CXX11_CONSTEXPR hamon::tuple<Implicit, Implicit, Implicit> t = {x1, x2, x3};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<0>(t).n == 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<1>(t).n == 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(get<2>(t).n == 3);
	}
}

}	// namespace ctor_value_copy_test

}	// namespace hamon_tuple_test
