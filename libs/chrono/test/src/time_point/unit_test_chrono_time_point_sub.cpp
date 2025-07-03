/**
 *	@file	unit_test_chrono_time_point_sub.cpp
 *
 *	@brief	operator-() のテスト
 *
 *	template<class Clock, class Duration1, class Rep2, class Period2>
 *	constexpr time_point<Clock, common_type_t<Duration1, duration<Rep2, Period2>>>
 *	operator-(const time_point<Clock, Duration1>& lhs, const duration<Rep2, Period2>& rhs);
 *
 *	template<class Clock, class Duration1, class Duration2>
 *	constexpr common_type_t<Duration1, Duration2>
 *	operator-(const time_point<Clock, Duration1>& lhs, const time_point<Clock, Duration2>& rhs);
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

namespace time_point_sub_test
{

struct MyClock
{};

GTEST_TEST(TimePointTest, SubTest)
{
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using Duration2 = hamon::chrono::duration<float, hamon::ratio<1>>;
		using CommonDuration = hamon::chrono::duration<float, hamon::ratio<1, 1000>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<TimePoint1>() - hamon::declval<Duration2>()),
			hamon::chrono::time_point<MyClock, CommonDuration>
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::declval<TimePoint1>() - hamon::declval<TimePoint2>()),
			CommonDuration
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<TimePoint1>() - hamon::declval<Duration2>()), "");
		static_assert(noexcept(hamon::declval<TimePoint1>() - hamon::declval<TimePoint2>()), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2998,
			(TimePoint1{Duration1{2}} - Duration2{3}).time_since_epoch().count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2998,
			(TimePoint1{Duration1{2}} - TimePoint2{Duration2{3}}).count());
	}
	{
		using Duration1 = hamon::chrono::duration<double, hamon::ratio<200>>;
		using Duration2 = hamon::chrono::duration<short, hamon::ratio<1, 1000>>;
		using CommonDuration = hamon::chrono::duration<double, hamon::ratio<1, 1000>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, Duration2>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<TimePoint1>() - hamon::declval<Duration2>()),
			hamon::chrono::time_point<MyClock, CommonDuration>
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::declval<TimePoint1>() - hamon::declval<TimePoint2>()),
			CommonDuration
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<TimePoint1>() - hamon::declval<Duration2>()), "");
		static_assert(noexcept(hamon::declval<TimePoint1>() - hamon::declval<TimePoint2>()), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(599996,
			(TimePoint1{Duration1{3}} - Duration2{4}).time_since_epoch().count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(599996,
			(TimePoint1{Duration1{3}} - TimePoint2{Duration2{4}}).count());
	}
}

}	// namespace time_point_sub_test

}	// namespace hamon_chrono_test
