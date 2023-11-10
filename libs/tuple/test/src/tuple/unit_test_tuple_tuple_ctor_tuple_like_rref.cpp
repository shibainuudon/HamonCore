/**
 *	@file	unit_test_tuple_tuple_ctor_tuple_like_rref.cpp
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

namespace ctor_tuple_like_rref_test
{

struct Explicit
{
	Explicit(int&) = delete;
	Explicit(int const&) = delete;
	Explicit(int const&&) = delete;
	explicit HAMON_CXX11_CONSTEXPR Explicit(int&& x) : n(x) {}
	int n;
};

struct Implicit
{
	Implicit(int&) = delete;
	Implicit(int const&) = delete;
	Implicit(int const&&) = delete;
	HAMON_CXX11_CONSTEXPR Implicit(int&& x) : n(x) {}
	int n;
};

struct NoThrow
{
	NoThrow(int&) = delete;
	NoThrow(int const&) = delete;
	NoThrow(int const&&) = delete;
	HAMON_CXX11_CONSTEXPR NoThrow(int&& x) noexcept : n(x) {}
	int n;
};

static_assert( hamon::is_constructible<hamon::tuple<short, float>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<short, float>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> &>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> const&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 2> &&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<short, float>, hamon::array<int, 2> &&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit, Implicit>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit, Implicit>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit, Implicit>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit, Explicit>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit, Explicit>, hamon::array<int, 3> &&>::value, "");

#if !defined(HAMON_USE_STD_TUPLE)
static_assert( hamon::is_nothrow_constructible<hamon::tuple<short, float>, hamon::array<int, 2> &&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow,  NoThrow>,  hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, NoThrow,  NoThrow>,  hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  Implicit, NoThrow>,  hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow,  Implicit>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, Implicit, Implicit>, hamon::array<int, 3> &&>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::array<int, 2> a = {1, 2};
		hamon::tuple<float, double> t(hamon::move(a));
		VERIFY(1 == hamon::adl_get<0>(t));
		VERIFY(2 == hamon::adl_get<1>(t));
	}
	{
		hamon::array<int, 3> a = {3, 4, 5};
		hamon::tuple<Explicit, Implicit, NoThrow> t(hamon::move(a));
		VERIFY(3 == hamon::adl_get<0>(t).n);
		VERIFY(4 == hamon::adl_get<1>(t).n);
		VERIFY(5 == hamon::adl_get<2>(t).n);
	}
	return true;
}

HAMON_WARNING_POP()

#undef VERIFY

GTEST_TEST(TupleTest, CtorTupleLikeRRefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_tuple_like_rref_test

}	// namespace hamon_tuple_test
