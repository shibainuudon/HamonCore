/**
 *	@file	unit_test_pair_ctor_pair_like_rref.cpp
 *
 *	@brief	pair-likeなオブジェクトからのコンストラクタのテスト
 * 
 *  template<pair-like P>
 *	constexpr explicit(see below) pair(P&& p);
 */

#include <hamon/pair.hpp>
#include <hamon/array.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_pair_like_rref_test
{

struct Explicit
{
	Explicit(int&) = delete;
	explicit HAMON_CXX11_CONSTEXPR Explicit(int&& x) : n(x) {}
	Explicit(int const&) = delete;
	Explicit(int const&&) = delete;
	int n;
};

struct Implicit
{
	Implicit(int&) = delete;
	HAMON_CXX11_CONSTEXPR Implicit(int&& x) : n(x) {}
	Implicit(int const&) = delete;
	Implicit(int const&&) = delete;
	int n;
};

struct NoThrow
{
	NoThrow(int&) = delete;
	HAMON_CXX11_CONSTEXPR NoThrow(int&& x) noexcept : n(x) {}
	NoThrow(int const&) = delete;
	NoThrow(int const&&) = delete;
	int n;
};

static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 1> &&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 1> &&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 3> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int*, 2> &&>::value, "");

static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> &>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 3> &&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::pair<short, float>, hamon::array<int, 2> &&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Implicit>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Explicit>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> &&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::pair<short, float>, hamon::array<int, 2> &&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, NoThrow>,  hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  Implicit>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, Implicit>, hamon::array<int, 2> &&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::array<int, 2> a = {1, 2};
		hamon::pair<float, double> t(hamon::move(a));
		VERIFY(1 == hamon::adl_get<0>(t));
		VERIFY(2 == hamon::adl_get<1>(t));
	}
	{
		hamon::array<int, 2> a = {3, 4};
		hamon::pair<Explicit, Implicit> t(hamon::move(a));
		VERIFY(3 == hamon::adl_get<0>(t).n);
		VERIFY(4 == hamon::adl_get<1>(t).n);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, CtorPairLikeRRefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_pair_like_rref_test

}	// namespace hamon_pair_test
