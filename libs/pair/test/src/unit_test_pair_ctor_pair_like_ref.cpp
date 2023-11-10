/**
 *	@file	unit_test_pair_ctor_pair_like_ref.cpp
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
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_pair_like_ref_test
{

struct Explicit
{
	explicit HAMON_CXX11_CONSTEXPR Explicit(int& x) : n(x) {}
	Explicit(int&&) = delete;
	Explicit(int const&) = delete;
	Explicit(int const&&) = delete;
	int n;
};

struct Implicit
{
	HAMON_CXX11_CONSTEXPR Implicit(int& x) : n(x) {}
	Implicit(int&&) = delete;
	Implicit(int const&) = delete;
	Implicit(int const&&) = delete;
	int n;
};

struct NoThrow
{
	HAMON_CXX11_CONSTEXPR NoThrow(int& x) noexcept : n(x) {}
	NoThrow(int&&) = delete;
	NoThrow(int const&) = delete;
	NoThrow(int const&&) = delete;
	int n;
};

static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 1> &>::value, "");
static_assert( hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int, 3> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 1> &>::value, "");
static_assert( hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<short, float>, hamon::array<int, 3> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int, int>, hamon::array<int*, 2> &>::value, "");

static_assert( hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 3> &>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::pair<short, float>, hamon::array<int, 2> &>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Implicit>, hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Explicit>, hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Explicit>, hamon::array<int, 2> &>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::pair<short, float>, hamon::array<int, 2> &>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, NoThrow>,  hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  Implicit>, hamon::array<int, 2> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, Implicit>, hamon::array<int, 2> &>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::array<int, 2> a = {1, 2};
		hamon::pair<float, double> t(a);
		VERIFY(1 == hamon::adl_get<0>(t));
		VERIFY(2 == hamon::adl_get<1>(t));
	}
	{
		hamon::array<int, 2> a = {3, 4};
		hamon::pair<Explicit, Implicit> t(a);
		VERIFY(3 == hamon::adl_get<0>(t).n);
		VERIFY(4 == hamon::adl_get<1>(t).n);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, CtorPairLikeRefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_pair_like_ref_test

}	// namespace hamon_pair_test
