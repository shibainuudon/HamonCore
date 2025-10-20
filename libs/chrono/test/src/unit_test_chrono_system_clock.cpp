/**
 *	@file	unit_test_chrono_system_clock.cpp
 *
 *	@brief	system_clock のテスト
 */

#include <hamon/chrono/system_clock.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, SystemClockTest)
{
	using Clock = hamon::chrono::system_clock;
	using rep        = typename Clock::rep;
	using period     = typename Clock::period;
	using duration   = typename Clock::duration;
	using time_point = typename Clock::time_point;

	static_assert(hamon::is_same<rep, typename duration::rep>::value, "");
	static_assert(hamon::is_same<period, typename duration::period>::value, "");
	static_assert(hamon::is_same<duration, typename time_point::duration>::value, "");
	static_assert(Clock::is_steady || !Clock::is_steady, "");

	static_assert(hamon::is_signed<rep>::value, "");

	static_assert(noexcept(Clock::now()), "");
	static_assert(hamon::is_same<time_point, decltype(Clock::now())>::value, "");
	{
		Clock::time_point t1 = Clock::now();
		EXPECT_TRUE(t1.time_since_epoch().count() != 0);
		EXPECT_TRUE(Clock::time_point::min() < t1);
		EXPECT_TRUE(Clock::time_point::max() > t1);
	}
	{
		Clock::time_point t1 = Clock::from_time_t(Clock::to_time_t(Clock::now()));
		(void)t1;
	}
	{
		std::time_t t1 = Clock::to_time_t(Clock::now());
		(void)t1;
	}
}

}	// namespace hamon_chrono_test
