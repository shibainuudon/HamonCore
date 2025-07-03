/**
 *	@file	unit_test_chrono_time_point_decrement.cpp
 *
 *	@brief	operator--() のテスト
 *
 *	constexpr time_point& operator--();
 *	constexpr time_point operator--(int);
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

namespace time_point_decrement_test
{

struct MyClock
{};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Clock, typename Duration>
HAMON_CXX14_CONSTEXPR bool test()
{
	using TimePoint = hamon::chrono::time_point<Clock, Duration>;

	static_assert(hamon::is_same<decltype(--hamon::declval<TimePoint>()), TimePoint&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<TimePoint>()--), TimePoint>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(--hamon::declval<TimePoint>()), "");
	static_assert(noexcept(hamon::declval<TimePoint>()--), "");
#endif

	TimePoint tp{Duration{10}};
	{
		auto tp2 = --tp;
		VERIFY(tp.time_since_epoch().count() == 9);
		VERIFY(tp2.time_since_epoch().count() == 9);
	}
	{
		auto tp2 = tp--;
		VERIFY(tp.time_since_epoch().count() == 8);
		VERIFY(tp2.time_since_epoch().count() == 9);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TimePointTest, DecrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<int, hamon::ratio<60>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<long, hamon::milli>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<float, hamon::ratio<1, 30>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<double, hamon::ratio<120>>>()));
}

}	// namespace time_point_decrement_test

}	// namespace hamon_chrono_test
