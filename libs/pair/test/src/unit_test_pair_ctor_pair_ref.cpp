﻿/**
 *	@file	unit_test_pair_ctor_pair_ref.cpp
 *
 *	@brief	変換可能な他のpairオブジェクトからのコンストラクタのテスト
 * 
 *	template<class U1, class U2> constexpr explicit(see below) pair(pair<U1, U2>& p);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_pair_ref_test
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

static_assert( hamon::is_constructible<hamon::pair<short, float>, hamon::pair<int, double> &>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> &>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Implicit>, hamon::pair<int, int> &>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Implicit, Explicit>, hamon::pair<int, int> &>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, Implicit> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<Implicit, int> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> const&&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::pair<short, float>, hamon::pair<int, double> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Implicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Explicit>, hamon::pair<int, int> &>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> const&&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::pair<short, float>, hamon::pair<int, double> &>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  Implicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, NoThrow>,  hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::pair<int, int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::pair<int, int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::pair<int, int> const&&>::value, "");

#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
static_assert(!hamon::is_constructible<hamon::pair<int, int const&>, hamon::pair<int, long> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int const&, int>, hamon::pair<long, int> &>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::pair<short, float> p1(1, 2);
		hamon::pair<int, double>  p2(p1);
		VERIFY(p2.first  == 1);
		VERIFY(p2.second == 2.0f);
	}
	{
		hamon::pair<int, int>           p1(3, 4);
		hamon::pair<Explicit, Explicit> p2(p1);
		VERIFY(p2.first.n  == 3);
		VERIFY(p2.second.n == 4);
	}
	{
		hamon::pair<int, int>           p1(5, 6);
		hamon::pair<Explicit, Implicit> p2(p1);
		VERIFY(p2.first.n  == 5);
		VERIFY(p2.second.n == 6);
	}
	{
		hamon::pair<int, int>           p1(7, 8);
		hamon::pair<Implicit, Explicit> p2 {p1};
		VERIFY(p2.first.n  == 7);
		VERIFY(p2.second.n == 8);
	}
	{
		hamon::pair<int, int>           p1(9, 10);
		hamon::pair<Implicit, Implicit> p2 = {p1};
		VERIFY(p2.first.n  == 9);
		VERIFY(p2.second.n == 10);
	}
	return true;
}

HAMON_WARNING_POP()

#undef VERIFY

GTEST_TEST(PairTest, CtorPairRefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_pair_ref_test

}	// namespace hamon_pair_test
