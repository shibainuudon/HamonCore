/**
 *	@file	unit_test_chrono_time_point_add.cpp
 *
 *	@brief	operator+() のテスト
 *
 *	template<class Clock, class Duration1, class Rep2, class Period2>
 *	constexpr time_point<Clock, common_type_t<Duration1, duration<Rep2, Period2>>>
 *	operator+(const time_point<Clock, Duration1>& lhs, const duration<Rep2, Period2>& rhs);
 *
 *	template<class Rep1, class Period1, class Clock, class Duration2>
 *	constexpr time_point<Clock, common_type_t<duration<Rep1, Period1>, Duration2>>
 *	operator+(const duration<Rep1, Period1>& lhs, const time_point<Clock, Duration2>& rhs);
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_add_test
{

struct MyClock
{};

GTEST_TEST(TimePointTest, AddTest)
{
	{
		using Duration1 = hamon::chrono::duration<int, std::ratio<1, 1000>>;
		using Duration2 = hamon::chrono::duration<float, std::ratio<1>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, hamon::chrono::duration<float, std::ratio<1, 1000>>>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<TimePoint1>() + hamon::declval<Duration2>()),
			TimePoint2
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::declval<Duration2>() + hamon::declval<TimePoint1>()),
			TimePoint2
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<TimePoint1>() + hamon::declval<Duration2>()), "");
		static_assert(noexcept(hamon::declval<Duration2>() + hamon::declval<TimePoint1>()), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3002,
			(TimePoint1{Duration1{2}} + Duration2{3}).time_since_epoch().count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2003,
			(Duration2{2} + TimePoint1{Duration1{3}}).time_since_epoch().count());
	}
	{
		using Duration1 = hamon::chrono::duration<double, std::ratio<200>>;
		using Duration2 = hamon::chrono::duration<short, std::ratio<1, 1000>>;
		using TimePoint1 = hamon::chrono::time_point<MyClock, Duration1>;
		using TimePoint2 = hamon::chrono::time_point<MyClock, hamon::chrono::duration<double, std::ratio<1, 1000>>>;

		static_assert(hamon::is_same<
			decltype(hamon::declval<TimePoint1>() + hamon::declval<Duration2>()),
			TimePoint2
		>::value, "");
		static_assert(hamon::is_same<
			decltype(hamon::declval<Duration2>() + hamon::declval<TimePoint1>()),
			TimePoint2
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(hamon::declval<TimePoint1>() + hamon::declval<Duration2>()), "");
		static_assert(noexcept(hamon::declval<Duration2>() + hamon::declval<TimePoint1>()), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(600004,
			(TimePoint1{Duration1{3}} + Duration2{4}).time_since_epoch().count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(800003,
			(Duration2{3} + TimePoint1{Duration1{4}}).time_since_epoch().count());
	}
}

}	// namespace time_point_add_test

}	// namespace hamon_chrono_test
