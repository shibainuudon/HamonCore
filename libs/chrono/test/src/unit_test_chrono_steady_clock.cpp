/**
 *	@file	unit_test_chrono_steady_clock.cpp
 *
 *	@brief	steady_clock のテスト
 */

#include <hamon/chrono/steady_clock.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <thread>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, SteadyClockTest)
{
	using steady_clock = hamon::chrono::steady_clock;
	using time_point = typename steady_clock::time_point;

	{
		auto tp = steady_clock::now();
		EXPECT_TRUE(tp != time_point{});
	}

#if 0
	{
		auto begin = steady_clock::now();
		for (int i = 0; i < 10; ++i)
		{
			auto tp = steady_clock::now();
			std::cout << hamon::chrono::duration_cast<hamon::chrono::milliseconds>(tp - begin).count() << " ms\n";

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
#endif
}

}	// namespace hamon_chrono_test
