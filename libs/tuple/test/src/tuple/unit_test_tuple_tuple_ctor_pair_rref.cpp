/**
 *	@file	unit_test_tuple_tuple_ctor_pair_rref.cpp
 *
 *	@brief	pair<U1, U2>&& を引数に取るコンストラクタのテスト
 *
 *	template<class U1, class U2> constexpr explicit(see below) tuple(pair<U1, U2>&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_pair_rref_test
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

static_assert( hamon::is_constructible<hamon::tuple<short, float>, hamon::pair<int, double> &&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> &&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Explicit, Implicit>, hamon::pair<int, int> &&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Explicit>, hamon::pair<int, int> &&>::value, "");
static_assert( hamon::is_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, Implicit> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<Implicit, int> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> const&&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::tuple<short, float>, hamon::pair<int, double> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Explicit>, hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Explicit, Implicit>, hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Explicit>, hamon::pair<int, int> &&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> const&&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::tuple<short, float>, hamon::pair<int, double> &&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  Implicit>, hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, NoThrow>,  hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<Implicit, Implicit>, hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::tuple<NoThrow,  NoThrow>,  hamon::pair<int, int> const&&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		hamon::pair<short, float> t1((short)1, 2.0f);
		hamon::tuple<int, double> t2(hamon::move(t1));
		VERIFY(get<0>(t2) == 1);
		VERIFY(get<1>(t2) == 2.0f);
	}
	{
		hamon::pair<int, int> t1(3, 4);
		hamon::tuple<Explicit, Explicit> t2(hamon::move(t1));
		VERIFY(get<0>(t2).n == 3);
		VERIFY(get<1>(t2).n == 4);
	}
	{
		hamon::pair<int, int> t1(5, 6);
		hamon::tuple<Explicit, Implicit> t2(hamon::move(t1));
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	{
		hamon::pair<int, int> t1(7, 8);
		hamon::tuple<Implicit, Explicit> t2 {hamon::move(t1)};
		VERIFY(get<0>(t2).n == 7);
		VERIFY(get<1>(t2).n == 8);
	}
	{
		hamon::pair<int, int> t1(9, 10);
		hamon::tuple<Implicit, Implicit> t2 = {hamon::move(t1)};
		VERIFY(get<0>(t2).n == 9);
		VERIFY(get<1>(t2).n == 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, CtorPairRRefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_pair_rref_test

}	// namespace hamon_tuple_test
