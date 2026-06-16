/**
 *	@file	unit_test_tuple_tuple_ctor_tuple_like_cref.cpp
 *
 *	@brief	tuple-likeなオブジェクトからのコンストラクタのテスト
 *
 *	template<tuple-like UTuple> constexpr explicit(see below) tuple(UTuple&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/array.hpp>
#include <hamon/complex.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_tuple_like_cref_test
{

template <typename T, hamon::size_t N>
using Array =
#if defined(HAMON_USE_STD_TUPLE)
	std::array<T, N>;
#else
	hamon::array<T, N>;
#endif

template <typename T>
using Complex =
#if defined(HAMON_USE_STD_TUPLE)
	std::complex<T>;
#else
	hamon::complex<T>;
#endif

struct Explicit
{
	Explicit(int&) = delete;
	Explicit(int&&) = delete;
	Explicit(int const&&) = delete;
	explicit HAMON_CXX11_CONSTEXPR Explicit(int const& x) : n(x) {}
	int n;
};

struct Implicit
{
	Implicit(int&) = delete;
	Implicit(int&&) = delete;
	Implicit(int const&&) = delete;
	HAMON_CXX11_CONSTEXPR Implicit(int const& x) : n(x) {}
	int n;
};

struct NoThrow
{
	NoThrow(int&) = delete;
	NoThrow(int&&) = delete;
	NoThrow(int const&&) = delete;
	HAMON_CXX11_CONSTEXPR NoThrow(int const& x) noexcept : n(x) {}
	int n;
};

static_assert( hamon::is_constructible<hamon::tuple<short, float>, Array<int, 2> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<short, float>, Array<int, 3> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Array<int, 3> &>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Array<int, 3> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Array<int, 3> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Array<int, 3> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Array<int, 2> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<float, float>, Complex<float> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<float, float, float>, Complex<float> const&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<short, float>, Array<int, 2> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit, Implicit>, Array<int, 3> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit, Implicit>, Array<int, 3> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit, Implicit>, Array<int, 3> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit, Explicit>, Array<int, 3> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit, Explicit>, Array<int, 3> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<float, float>, Complex<float> const&>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<short, float>, Array<int, 2> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow,  NoThrow>,  Array<int, 3> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, NoThrow,  NoThrow>,  Array<int, 3> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  Implicit, NoThrow>,  Array<int, 3> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow,  Implicit>, Array<int, 3> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, Implicit, Implicit>, Array<int, 3> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<float, float>, Complex<float> const&>::value, "");
#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

GTEST_TEST(TupleTest, CtorTupleLikeCRefTest)
{
	{
		Array<int, 2> const a = {1, 2};
		hamon::tuple<float, double> const t(a);
		EXPECT_EQ(1, hamon::adl_get<0>(t));
		EXPECT_EQ(2, hamon::adl_get<1>(t));
	}
	{
		Array<int, 3> const a = {3, 4, 5};
		hamon::tuple<Explicit, Implicit, NoThrow> const t(a);
		EXPECT_EQ(3, hamon::adl_get<0>(t).n);
		EXPECT_EQ(4, hamon::adl_get<1>(t).n);
		EXPECT_EQ(5, hamon::adl_get<2>(t).n);
	}
	{
		HAMON_CXX11_CONSTEXPR Array<int, 2> const a = {1, 2};
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, double> const t(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::adl_get<0>(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::adl_get<1>(t));
	}
	{
		HAMON_CXX11_CONSTEXPR Array<int, 3> const a = {3, 4, 5};
		HAMON_CXX11_CONSTEXPR hamon::tuple<Explicit, Implicit, NoThrow> const t(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::adl_get<0>(t).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::adl_get<1>(t).n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::adl_get<2>(t).n);
	}
	{
		HAMON_CXX11_CONSTEXPR Complex<float> const c = {1, 2};
		HAMON_CXX11_CONSTEXPR hamon::tuple<float, float> const t(c);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::adl_get<0>(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::adl_get<1>(t));
	}
}

HAMON_WARNING_POP()

}	// namespace ctor_tuple_like_cref_test

}	// namespace hamon_tuple_test
