/**
 *	@file	unit_test_chrono_steady_clock.cpp
 *
 *	@brief	steady_clock のテスト
 */

#include <hamon/chrono/steady_clock.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, SteadyClockTest)
{
	using Clock = hamon::chrono::steady_clock;
	using rep        = typename Clock::rep;
	using period     = typename Clock::period;
	using duration   = typename Clock::duration;
	using time_point = typename Clock::time_point;

	static_assert(hamon::is_same<rep, typename duration::rep>::value, "");
	static_assert(hamon::is_same<period, typename duration::period>::value, "");
	static_assert(hamon::is_same<duration, typename time_point::duration>::value, "");
	static_assert(Clock::is_steady, "");

	static_assert(noexcept(Clock::now()), "");
	static_assert(hamon::is_same<time_point, decltype(Clock::now())>::value, "");
	{
		auto t1 = Clock::now();
		auto t2 = Clock::now();
		EXPECT_TRUE(t2 >= t1);
		EXPECT_TRUE(t2 != time_point{});
	}
}

}	// namespace hamon_chrono_test
