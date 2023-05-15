/**
 *	@file	unit_test_pair_swap.cpp
 *
 *	@brief	swap のテスト
 * 
 *	constexpr void pair::swap(pair& p) noexcept(see below);
 * 
 *	template<class T1, class T2>
 *	constexpr void swap(pair<T1, T2>& x, pair<T1, T2>& y) noexcept(noexcept(x.swap(y)));
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/adl_swap.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace swap_test
{

#if !(defined(HAMON_STDLIB_DINKUMWARE) && (HAMON_CXX_STANDARD < 17))
struct NonMovable { NonMovable(NonMovable&&) = delete; };

struct NonSwappable : NonMovable {};
void swap(NonSwappable&, NonSwappable&) = delete;

struct Swappable : NonMovable {};
void swap(Swappable&, Swappable&);

struct NothrowSwappable : NonMovable {};
void swap(NothrowSwappable&, NothrowSwappable&) noexcept;

static_assert(!hamon::is_swappable<NonMovable>::value, "");
static_assert(!hamon::is_swappable<NonSwappable>::value, "");
static_assert( hamon::is_swappable<Swappable>::value, "");
static_assert( hamon::is_swappable<NothrowSwappable>::value, "");

static_assert(!hamon::is_nothrow_swappable<NonMovable>::value, "");
static_assert(!hamon::is_nothrow_swappable<NonSwappable>::value, "");
static_assert(!hamon::is_nothrow_swappable<Swappable>::value, "");
static_assert( hamon::is_nothrow_swappable<NothrowSwappable>::value, "");

static_assert(!hamon::is_swappable<hamon::pair<NonMovable,   NonMovable>>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<int,          NonMovable>>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<NonMovable,   int>>::value, "");
static_assert( hamon::is_swappable<hamon::pair<int,          int>>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<NonSwappable, NonSwappable>>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<Swappable,    NonSwappable>>::value, "");
static_assert(!hamon::is_swappable<hamon::pair<NonSwappable, Swappable>>::value, "");
static_assert( hamon::is_swappable<hamon::pair<Swappable,    Swappable>>::value, "");

static_assert( hamon::is_nothrow_swappable<hamon::pair<NothrowSwappable, NothrowSwappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::pair<Swappable,        NothrowSwappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::pair<NothrowSwappable, Swappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::pair<Swappable,        Swappable>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::pair<int, float> p1(1, 0.5f);
		hamon::pair<int, float> p2(2, 1.5f);

		p1.swap(p2);
		VERIFY(p1.first  == 2);
		VERIFY(p1.second == 1.5f);
		VERIFY(p2.first  == 1);
		VERIFY(p2.second == 0.5f);

		hamon::adl_swap(p1, p2);
		VERIFY(p1.first  == 1);
		VERIFY(p1.second == 0.5f);
		VERIFY(p2.first  == 2);
		VERIFY(p2.second == 1.5f);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, SwapTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE((test()));
}

}	// namespace swap_test

}	// namespace hamon_pair_test
