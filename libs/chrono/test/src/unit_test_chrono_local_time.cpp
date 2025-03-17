/**
 *	@file	unit_test_chrono_local_time.cpp
 *
 *	@brief	local_time のテスト
 */

#include <hamon/chrono/local_time.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, LocalTimeTest)
{
	namespace chrono = hamon::chrono;
	using system_clock = chrono::system_clock;

	chrono::local_time<system_clock::duration> now{system_clock::now().time_since_epoch()};
	EXPECT_TRUE(now.time_since_epoch().count() != 0);
}

}	// namespace hamon_chrono_test
