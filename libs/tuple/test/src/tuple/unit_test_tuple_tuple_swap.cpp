﻿/**
 *	@file	unit_test_tuple_tuple_swap.cpp
 *
 *	@brief	swapのテスト
 *
 *	constexpr void swap(tuple& rhs) noexcept(see below);
 * 
 *	template<class... Types>
 *	constexpr void swap(tuple<Types...>& x, tuple<Types...>& y) noexcept(see below);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
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

static_assert(!hamon::is_swappable<hamon::tuple<NonMovable,   NonMovable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<int,          NonMovable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonMovable,   int>>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<int,          int>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonSwappable, NonSwappable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<Swappable,    NonSwappable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonSwappable, Swappable>>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<Swappable,    Swappable>>::value, "");

static_assert( hamon::is_nothrow_swappable<hamon::tuple<NothrowSwappable, NothrowSwappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<Swappable,        NothrowSwappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<NothrowSwappable, Swappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<Swappable,        Swappable>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using std::get;
	using std::swap;
	{
		hamon::tuple<int, float> t1(1, 0.5f);
		hamon::tuple<int, float> t2(2, 1.5f);

		t1.swap(t2);
		VERIFY(get<0>(t1) == 2);
		VERIFY(get<1>(t1) == 1.5f);
		VERIFY(get<0>(t2) == 1);
		VERIFY(get<1>(t2) == 0.5f);

		swap(t1, t2);
		VERIFY(get<0>(t1) == 1);
		VERIFY(get<1>(t1) == 0.5f);
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 1.5f);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, SwapTest)
{
	// TODO	std::swapがconstexprでない
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE((test()));
}

}	// namespace swap_test

}	// namespace hamon_tuple_test