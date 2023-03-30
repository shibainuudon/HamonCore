/**
 *	@file	unit_test_pair_swap_const.cpp
 *
 *	@brief	swap のテスト
 * 
 *	constexpr void pair::swap(const pair& p) const noexcept(see below);
 * 
 *	template<class T1, class T2>
 *	constexpr void swap(const pair<T1, T2>& x, const pair<T1, T2>& y) noexcept(noexcept(x.swap(y)));
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace swap_const_test
{

#if !(defined(HAMON_STDLIB_DINKUMWARE) && (HAMON_CXX_STANDARD < 17))
struct NonMovable { NonMovable(NonMovable&&) = delete; };

struct NonSwappable : NonMovable {};
void swap(NonSwappable const&, NonSwappable const&) = delete;

struct Swappable : NonMovable {};
void swap(Swappable const&, Swappable const&);

struct NothrowSwappable : NonMovable {};
void swap(NothrowSwappable const&, NothrowSwappable const&) noexcept;

static_assert(!hamon::is_swappable<NonMovable const>::value, "");
static_assert(!hamon::is_swappable<NonSwappable const>::value, "");
static_assert( hamon::is_swappable<Swappable const>::value, "");
static_assert( hamon::is_swappable<NothrowSwappable const>::value, "");

static_assert(!hamon::is_nothrow_swappable<NonMovable const>::value, "");
static_assert(!hamon::is_nothrow_swappable<NonSwappable const>::value, "");
static_assert(!hamon::is_nothrow_swappable<Swappable const>::value, "");
static_assert( hamon::is_nothrow_swappable<NothrowSwappable const>::value, "");

static_assert(!hamon::is_swappable<hamon::pair<NonMovable,   NonMovable> const>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<int&,         NonMovable> const>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<NonMovable,   int&> const>::value, "");
static_assert( hamon::is_swappable<hamon::pair<int&,         int&> const>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<NonSwappable, NonSwappable> const>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<Swappable,    NonSwappable> const>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<NonSwappable, Swappable> const>::value, "");
static_assert( hamon::is_swappable<hamon::pair<Swappable,    Swappable> const>::value, "");

static_assert( hamon::is_nothrow_swappable<hamon::pair<NothrowSwappable, NothrowSwappable> const>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::pair<Swappable,        NothrowSwappable> const>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::pair<NothrowSwappable, Swappable> const>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::pair<Swappable,        Swappable> const>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i1 = 10;
		int i2 = 11;
		float f1 = 12;
		float f2 = 13;
		hamon::pair<int&, float&> const p1(i1, f1);
		hamon::pair<int&, float&> const p2(i2, f2);

		p1.swap(p2);
		VERIFY(p1.first  == i1);
		VERIFY(p1.second == f1);
		VERIFY(p2.first  == i2);
		VERIFY(p2.second == f2);
		VERIFY(i1 == 11);
		VERIFY(i2 == 10);
		VERIFY(f1 == 13);
		VERIFY(f2 == 12);

		swap(p1, p2);
		VERIFY(p1.first  == i1);
		VERIFY(p1.second == f1);
		VERIFY(p2.first  == i2);
		VERIFY(p2.second == f2);
		VERIFY(i1 == 10);
		VERIFY(i2 == 11);
		VERIFY(f1 == 12);
		VERIFY(f2 == 13);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, SwapConstTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE((test()));
}

}	// namespace swap_const_test

}	// namespace hamon_pair_test
