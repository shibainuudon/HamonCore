/**
 *	@file	unit_test_chrono_time_point_ceil.cpp
 *
 *	@brief	ceil() のテスト
 *
 *	template<class ToDuration, class Clock, class Duration>
 *	constexpr time_point<Clock, ToDuration> ceil(const time_point<Clock, Duration>& tp);
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_ceil_test
{

struct MyClock
{};

template <typename ToDuration, typename Clock, typename Duration, typename = void>
struct is_invocable_ceil
	: public hamon::false_type {};

template <typename ToDuration, typename Clock, typename Duration>
struct is_invocable_ceil<ToDuration, Clock, Duration,
	hamon::void_t<decltype(hamon::chrono::ceil<ToDuration>(hamon::declval<hamon::chrono::time_point<Clock, Duration>>()))>>
	: public hamon::true_type {};

static_assert( is_invocable_ceil<hamon::chrono::duration<int>, MyClock, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_ceil<hamon::chrono::duration<int>, MyClock, hamon::chrono::duration<float>>::value, "");
static_assert( is_invocable_ceil<hamon::chrono::duration<float>, MyClock, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_ceil<hamon::chrono::duration<float>, MyClock, hamon::chrono::duration<float>>::value, "");
static_assert(!is_invocable_ceil<int, MyClock, hamon::chrono::duration<int>>::value, "");
//static_assert(!is_invocable_ceil<hamon::chrono::duration<int>, MyClock, int>::value, "");

GTEST_TEST(TimePointTest, CeilTest)
{
	using hamon::chrono::ceil;
	{
		using Duration = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using TimePoint = hamon::chrono::time_point<MyClock, Duration>;
		using ToDuration = hamon::chrono::duration<int, hamon::ratio<1>>;
		using ToTimePoint = hamon::chrono::time_point<MyClock, ToDuration>;
		static_assert(hamon::is_same<
			decltype(ceil<ToDuration>(hamon::declval<TimePoint>())),
			ToTimePoint
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(ceil<ToDuration>(hamon::declval<TimePoint>())), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-3900}}).time_since_epoch().count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-3500}}).time_since_epoch().count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-3100}}).time_since_epoch().count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-3000}}).time_since_epoch().count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-2900}}).time_since_epoch().count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-2500}}).time_since_epoch().count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-2100}}).time_since_epoch().count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-2000}}).time_since_epoch().count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-1900}}).time_since_epoch().count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-1500}}).time_since_epoch().count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-1100}}).time_since_epoch().count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{-1000}}).time_since_epoch().count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ -900}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ -500}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ -100}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{    0}}).time_since_epoch().count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{  100}}).time_since_epoch().count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{  500}}).time_since_epoch().count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{  900}}).time_since_epoch().count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 1000}}).time_since_epoch().count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 1100}}).time_since_epoch().count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 1500}}).time_since_epoch().count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 1900}}).time_since_epoch().count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 2000}}).time_since_epoch().count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 2100}}).time_since_epoch().count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 2500}}).time_since_epoch().count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 2900}}).time_since_epoch().count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 3000}}).time_since_epoch().count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 3100}}).time_since_epoch().count(),  4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 3500}}).time_since_epoch().count(),  4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ceil<ToDuration>(TimePoint{Duration{ 3900}}).time_since_epoch().count(),  4);
	}
	{
		using Duration = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using TimePoint = hamon::chrono::time_point<MyClock, Duration>;
		using ToDuration = hamon::chrono::duration<float, hamon::ratio<1>>;
		using ToTimePoint = hamon::chrono::time_point<MyClock, ToDuration>;
		static_assert(hamon::is_same<
			decltype(ceil<ToDuration>(hamon::declval<TimePoint>())),
			ToTimePoint
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(ceil<ToDuration>(hamon::declval<TimePoint>())), "");
#endif

		{
			HAMON_CXX11_CONSTEXPR TimePoint d1{Duration{1500}};
			HAMON_CXX11_CONSTEXPR ToTimePoint d2 = ceil<ToDuration>(d1);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d2.time_since_epoch().count(), 1.5f);
		}
		{
			HAMON_CXX11_CONSTEXPR TimePoint d1{Duration{-1500}};
			HAMON_CXX11_CONSTEXPR ToTimePoint d2 = ceil<ToDuration>(d1);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d2.time_since_epoch().count(), -1.5f);
		}
	}
}

}	// namespace time_point_ceil_test

}	// namespace hamon_chrono_test
