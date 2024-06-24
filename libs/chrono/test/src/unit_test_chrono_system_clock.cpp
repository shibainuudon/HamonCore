/**
 *	@file	unit_test_chrono_system_clock.cpp
 *
 *	@brief	system_clock のテスト
 */

#include <hamon/chrono/system_clock.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <thread>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, SystemClockTest)
{
	using system_clock = hamon::chrono::system_clock;
	using time_point = typename system_clock::time_point;

	{
		auto tp = system_clock::now();
		EXPECT_TRUE(tp != time_point{});
		auto tt = system_clock::to_time_t(tp);
		EXPECT_TRUE(tt != 0);
		auto tp2 = system_clock::from_time_t(tt);
		EXPECT_TRUE(tp2 != time_point{});
	}

#if 0
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4996)
	for (int i = 0; i < 10; ++i)
	{
		auto tp = system_clock::now();
		auto tt = system_clock::to_time_t(tp);
		std::cout << ctime(&tt);

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
HAMON_WARNING_POP()
#endif
}

}	// namespace hamon_chrono_test
