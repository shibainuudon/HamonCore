/**
 *	@file	unit_test_chrono_time_point_time_since_epoch.cpp
 *
 *	@brief	time_since_epoch() のテスト
 *
 *	constexpr duration time_since_epoch() const;
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_time_since_epoch_test
{

struct MyClock
{};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Clock, typename Duration>
HAMON_CXX14_CONSTEXPR bool test()
{
	using TimePoint = hamon::chrono::time_point<Clock, Duration>;

	static_assert(hamon::is_same<decltype(hamon::declval<TimePoint>().time_since_epoch()), Duration>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(hamon::declval<TimePoint>().time_since_epoch()), "");
#endif

	TimePoint const tp{Duration{2}};
	VERIFY(tp.time_since_epoch() == Duration{2});

	return true;
}

#undef VERIFY

GTEST_TEST(TimePointTest, TimeSinceEpochTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<int, std::ratio<60>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<long, std::milli>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<float, std::ratio<1, 30>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<double, std::ratio<120>>>()));
}

}	// namespace time_point_time_since_epoch_test

}	// namespace hamon_chrono_test
