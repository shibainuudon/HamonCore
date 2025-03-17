/**
 *	@file	unit_test_chrono_local_seconds.cpp
 *
 *	@brief	local_seconds のテスト
 */

#include <hamon/chrono/local_seconds.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, LocalSecondsTest)
{
	namespace chrono = hamon::chrono;

	{
		chrono::local_seconds s{chrono::seconds{123}};
		EXPECT_TRUE(s.time_since_epoch().count() == 123);
	}
	{
		chrono::local_seconds s{chrono::minutes{123}};
		EXPECT_TRUE(s.time_since_epoch().count() == 123 * 60);
	}
}

}	// namespace hamon_chrono_test
