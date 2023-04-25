/**
 *	@file	unit_test_tuple_tuple_ctor_tuple_ref.cpp
 *
 *	@brief	tuple<UTypes...>& を引数に取るコンストラクタのテスト
 *
 *	template<class... UTypes> constexpr explicit(see below) tuple(tuple<UTypes...>& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_tuple_ref_test
{

struct Explicit
{
	Explicit(int const&) = delete;
	Explicit(int&&) = delete;
	Explicit(int const&&) = delete;
	explicit HAMON_CXX11_CONSTEXPR Explicit(int& x) : n(x) {}
	int n;
};

struct Implicit
{
	Implicit(int const&) = delete;
	Implicit(int&&) = delete;
	Implicit(int const&&) = delete;
	HAMON_CXX11_CONSTEXPR Implicit(int& x) : n(x) {}
	int n;
};

struct NoThrow
{
	NoThrow(int const&) = delete;
	NoThrow(int&&) = delete;
	NoThrow(int const&&) = delete;
	HAMON_CXX11_CONSTEXPR NoThrow(int& x) noexcept : n(x) {}
	int n;
};

static_assert( hamon::is_constructible<hamon::tuple<short, float>, hamon::tuple<int, double> &>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::tuple<int, int> &>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Implicit>, hamon::tuple<int, int> &>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Explicit>, hamon::tuple<int, int> &>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Implicit>, hamon::tuple<int, int> &>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::tuple<int, Implicit> &>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::tuple<Implicit, int> &>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::tuple<int, int> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::tuple<int, int> const&&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<short, float>, hamon::tuple<int, double> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit>, hamon::tuple<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit>, hamon::tuple<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit>, hamon::tuple<int, int> &>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::tuple<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::tuple<int, int> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::tuple<int, int> const&&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::tuple<short, float>, hamon::tuple<int, double> &>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::tuple<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  Implicit>, hamon::tuple<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, NoThrow>,  hamon::tuple<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, Implicit>, hamon::tuple<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::tuple<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::tuple<int, int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::tuple<int, int> const&&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::tuple<short, float> t1((short)1, 2.0f);
		hamon::tuple<int, double>  t2(t1);
		VERIFY(hamon::adl_get<0>(t2) == 1);
		VERIFY(hamon::adl_get<1>(t2) == 2);
	}
	{
		hamon::tuple<int, int>           t1(3, 4);
		hamon::tuple<Explicit, Explicit> t2(t1);
		VERIFY(hamon::adl_get<0>(t2).n == 3);
		VERIFY(hamon::adl_get<1>(t2).n == 4);
	}
	{
		hamon::tuple<int, int>           t1(5, 6);
		hamon::tuple<Explicit, Implicit> t2(t1);
		VERIFY(hamon::adl_get<0>(t2).n == 5);
		VERIFY(hamon::adl_get<1>(t2).n == 6);
	}
	{
		hamon::tuple<int, int>           t1(7, 8);
		hamon::tuple<Implicit, Explicit> t2 {t1};
		VERIFY(hamon::adl_get<0>(t2).n == 7);
		VERIFY(hamon::adl_get<1>(t2).n == 8);
	}
	{
		hamon::tuple<int, int>           t1(9, 10);
		hamon::tuple<Implicit, Implicit> t2 = {t1};
		VERIFY(hamon::adl_get<0>(t2).n == 9);
		VERIFY(hamon::adl_get<1>(t2).n == 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, CtorTupleRefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_tuple_ref_test

}	// namespace hamon_tuple_test
