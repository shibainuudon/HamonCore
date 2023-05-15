/**
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
#include <hamon/tuple/adl_get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/adl_swap.hpp>
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

static_assert( hamon::is_swappable<hamon::tuple<>>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<int>>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<float>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonMovable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonSwappable>>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<Swappable>>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<NothrowSwappable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonMovable,   NonMovable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<int,          NonMovable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonMovable,   int>>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<int,          int>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonSwappable, NonSwappable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<Swappable,    NonSwappable>>::value, "");
static_assert(!hamon::is_swappable<hamon::tuple<NonSwappable, Swappable>>::value, "");
static_assert( hamon::is_swappable<hamon::tuple<Swappable,    Swappable>>::value, "");

static_assert( hamon::is_nothrow_swappable<hamon::tuple<>>::value, "");
static_assert( hamon::is_nothrow_swappable<hamon::tuple<int>>::value, "");
static_assert( hamon::is_nothrow_swappable<hamon::tuple<NothrowSwappable, NothrowSwappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<Swappable,        NothrowSwappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<NothrowSwappable, Swappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::tuple<Swappable,        Swappable>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::tuple<int> t1(10);
		hamon::tuple<int> t2(20);

		t1.swap(t2);
		VERIFY(hamon::adl_get<0>(t1) == 20);
		VERIFY(hamon::adl_get<0>(t2) == 10);

		hamon::adl_swap(t1, t2);
		VERIFY(hamon::adl_get<0>(t1) == 10);
		VERIFY(hamon::adl_get<0>(t2) == 20);
	}
	{
		hamon::tuple<int, float> t1(1, 0.5f);
		hamon::tuple<int, float> t2(2, 1.5f);

		t1.swap(t2);
		VERIFY(hamon::adl_get<0>(t1) == 2);
		VERIFY(hamon::adl_get<1>(t1) == 1.5f);
		VERIFY(hamon::adl_get<0>(t2) == 1);
		VERIFY(hamon::adl_get<1>(t2) == 0.5f);

		hamon::adl_swap(t1, t2);
		VERIFY(hamon::adl_get<0>(t1) == 1);
		VERIFY(hamon::adl_get<1>(t1) == 0.5f);
		VERIFY(hamon::adl_get<0>(t2) == 2);
		VERIFY(hamon::adl_get<1>(t2) == 1.5f);
	}
	{
		hamon::tuple<> t1{};
		hamon::tuple<> t2{};

		t1.swap(t2);

		hamon::adl_swap(t1, t2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, SwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace swap_test

}	// namespace hamon_tuple_test
