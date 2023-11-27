/**
 *	@file	unit_test_pair_ctor_pair_crref.cpp
 *
 *	@brief	変換可能な他のpairオブジェクトからのコンストラクタのテスト
 * 
 *	template<class U1, class U2> constexpr explicit(see below) pair(const pair<U1, U2>&& p);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_pair_crref_test
{

struct Explicit
{
	Explicit(int&) = delete;
	Explicit(int const&) = delete;
	Explicit(int&&) = delete;
	explicit HAMON_CXX11_CONSTEXPR Explicit(int const&& x) : n(x) {}
	int n;
};

struct Implicit
{
	Implicit(int&) = delete;
	Implicit(int const&) = delete;
	Implicit(int&&) = delete;
	HAMON_CXX11_CONSTEXPR Implicit(int const&& x) : n(x) {}
	int n;
};

struct NoThrow
{
	NoThrow(int&) = delete;
	NoThrow(int const&) = delete;
	NoThrow(int&&) = delete;
	HAMON_CXX11_CONSTEXPR NoThrow(int const&& x) noexcept : n(x) {}
	int n;
};

static_assert( hamon::is_constructible<hamon::pair<short, float>, hamon::pair<int, double> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Implicit, Explicit>, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, Implicit> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<Implicit, int> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> &&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::pair<short, float>, hamon::pair<int, double> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Explicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Explicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Explicit>, hamon::pair<int, int> const&&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> &&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::pair<short, float>, hamon::pair<int, double> const&&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, NoThrow>,  hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<Implicit, Implicit>, hamon::pair<int, int> const&&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::pair<int, int> &>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::pair<int, int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::pair<NoThrow,  NoThrow>,  hamon::pair<int, int> &&>::value, "");

#if defined(HAMON_HAS_REFERENCE_CONSTRUCTS_FROM_TEMPORARY)
static_assert(!hamon::is_constructible<hamon::pair<int, int const&>, hamon::pair<int, long> const&&>::value, "");
static_assert(!hamon::is_constructible<hamon::pair<int const&, int>, hamon::pair<long, int> const&&>::value, "");
#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

GTEST_TEST(PairTest, CtorPairCRRefTest)
{
	{
		hamon::pair<short, float> p1(1, 2);
		hamon::pair<int, double>  p2(hamon::move(p1));
		EXPECT_EQ(1, p2.first);
		EXPECT_EQ(2, p2.second);
	}
	{
		hamon::pair<int, int>           p1(3, 4);
		hamon::pair<Explicit, Explicit> p2(hamon::move(p1));
		EXPECT_EQ(3, p2.first.n);
		EXPECT_EQ(4, p2.second.n);
	}
	{
		hamon::pair<int, int>           p1(9, 10);
		hamon::pair<Implicit, Implicit> p2 = {hamon::move(p1)};
		EXPECT_EQ( 9, p2.first.n);
		EXPECT_EQ(10, p2.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<short, float> p1(1, 2);
		HAMON_CXX11_CONSTEXPR hamon::pair<int, double>  p2(hamon::move(p1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, p2.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, p2.second);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int>           p1(3, 4);
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, Explicit> p2(hamon::move(p1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, p2.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, p2.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int>           p1(5, 6);
		HAMON_CXX11_CONSTEXPR hamon::pair<Explicit, Implicit> p2(hamon::move(p1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, p2.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, p2.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int>           p1(7, 8);
		HAMON_CXX11_CONSTEXPR hamon::pair<Implicit, Explicit> p2 {hamon::move(p1)};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, p2.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8, p2.second.n);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair<int, int>           p1(9, 10);
		HAMON_CXX11_CONSTEXPR hamon::pair<Implicit, Implicit> p2 = {hamon::move(p1)};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, p2.first.n);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, p2.second.n);
	}
}

HAMON_WARNING_POP()

}	// namespace ctor_pair_crref_test

}	// namespace hamon_pair_test
