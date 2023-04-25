/**
 *	@file	unit_test_tuple_tuple_swap_const.cpp
 *
 *	@brief	swap(プロキシ参照版)のテスト
 *
 *	constexpr void swap(const tuple& rhs) const noexcept(see below);
 *
 *	template<class... Types>
 *	constexpr void swap(const tuple<Types...>& x, const tuple<Types...>& y) noexcept(see below);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
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

static_assert(!hamon::is_swappable<hamon::tuple<NonMovable,   NonMovable> const>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<int&,         NonMovable> const>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonMovable,   int&> const>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<int&,         int&> const>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonSwappable, NonSwappable> const>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<Swappable,    NonSwappable> const>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonSwappable, Swappable> const>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<Swappable,    Swappable> const>::value, "");

static_assert( hamon::is_nothrow_swappable<hamon::tuple<NothrowSwappable, NothrowSwappable> const>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<Swappable,        NothrowSwappable> const>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<NothrowSwappable, Swappable> const>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<Swappable,        Swappable> const>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using std::swap;
	{
		int i1 = 10;
		int i2 = 11;
		float f1 = 12;
		float f2 = 13;
		hamon::tuple<int&, float&> const t1(i1, f1);
		hamon::tuple<int&, float&> const t2(i2, f2);

		t1.swap(t2);
		VERIFY(hamon::adl_get<0>(t1) == i1);
		VERIFY(hamon::adl_get<1>(t1) == f1);
		VERIFY(hamon::adl_get<0>(t2) == i2);
		VERIFY(hamon::adl_get<1>(t2) == f2);
		VERIFY(i1 == 11);
		VERIFY(i2 == 10);
		VERIFY(f1 == 13);
		VERIFY(f2 == 12);

		swap(t1, t2);
		VERIFY(hamon::adl_get<0>(t1) == i1);
		VERIFY(hamon::adl_get<1>(t1) == f1);
		VERIFY(hamon::adl_get<0>(t2) == i2);
		VERIFY(hamon::adl_get<1>(t2) == f2);
		VERIFY(i1 == 10);
		VERIFY(i2 == 11);
		VERIFY(f1 == 12);
		VERIFY(f2 == 13);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, SwapConstTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE((test()));
}

}	// namespace swap_const_test

}	// namespace hamon_tuple_test
