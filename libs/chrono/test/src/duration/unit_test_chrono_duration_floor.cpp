﻿/**
 *	@file	unit_test_chrono_duration_floor.cpp
 *
 *	@brief	floor() のテスト
 *
 *	template<class ToDuration, class Rep, class Period>
 *	constexpr ToDuration floor(const duration<Rep, Period>& d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_floor_test
{

template <typename ToDuration, typename Duration, typename = void>
struct is_invocable_floor
	: public hamon::false_type {};

template <typename ToDuration, typename Duration>
struct is_invocable_floor<ToDuration, Duration,
	hamon::void_t<decltype(hamon::chrono::floor<ToDuration>(hamon::declval<Duration>()))>>
	: public hamon::true_type {};

static_assert( is_invocable_floor<hamon::chrono::duration<int>, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_floor<hamon::chrono::duration<int>, hamon::chrono::duration<float>>::value, "");
static_assert( is_invocable_floor<hamon::chrono::duration<float>, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_floor<hamon::chrono::duration<float>, hamon::chrono::duration<float>>::value, "");
static_assert(!is_invocable_floor<int, hamon::chrono::duration<int>>::value, "");
static_assert(!is_invocable_floor<hamon::chrono::duration<int>, int>::value, "");

GTEST_TEST(DurationTest, FloorTest)
{
	using hamon::chrono::floor;
	{
		using Duration = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using ToDuration = hamon::chrono::duration<int, hamon::ratio<1>>;
		static_assert(hamon::is_same<
			decltype(floor<ToDuration>(hamon::declval<Duration>())),
			ToDuration
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(floor<ToDuration>(hamon::declval<Duration>())), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-3900}).count(), -4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-3500}).count(), -4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-3100}).count(), -4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-3000}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-2900}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-2500}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-2100}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-2000}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-1900}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-1500}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-1100}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{-1000}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ -900}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ -500}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ -100}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{    0}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{  100}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{  500}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{  900}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 1000}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 1100}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 1500}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 1900}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 2000}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 2100}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 2500}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 2900}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 3000}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 3100}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 3500}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(floor<ToDuration>(Duration{ 3900}).count(),  3);
	}
	{
		using Duration = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using ToDuration = hamon::chrono::duration<float, hamon::ratio<1>>;
		static_assert(hamon::is_same<
			decltype(floor<ToDuration>(hamon::declval<Duration>())),
			ToDuration
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(floor<ToDuration>(hamon::declval<Duration>())), "");
#endif

		{
			HAMON_CXX11_CONSTEXPR Duration d1{1500};
			HAMON_CXX11_CONSTEXPR ToDuration d2 = floor<ToDuration>(d1);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d2.count(), 1.5f);
		}
		{
			HAMON_CXX11_CONSTEXPR Duration d1{-1500};
			HAMON_CXX11_CONSTEXPR ToDuration d2 = floor<ToDuration>(d1);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d2.count(), -1.5f);
		}
	}
}

}	// namespace duration_floor_test

}	// namespace hamon_chrono_test
