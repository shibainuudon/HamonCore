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

	{
		auto tp = system_clock::now();
		auto tt = system_clock::to_time_t(tp);
		auto tp2 = system_clock::from_time_t(tt);
		(void)tp2;
	}

	//for (int i = 0; i < 100; ++i)
	//{
	//	auto tp = system_clock::now();
	//	auto tt = system_clock::to_time_t(tp);
	//	std::cout << ctime(&tt) << std::endl;

	//	std::this_thread::sleep_for(std::chrono::seconds(1));
	//}
}

}	// namespace hamon_chrono_test
