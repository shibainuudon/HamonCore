/**
 *	@file	unit_test_chrono_local_days.cpp
 *
 *	@brief	local_days のテスト
 */

#include <hamon/chrono/local_days.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, LocalDaysTest)
{
	namespace chrono = hamon::chrono;

	{
		chrono::local_days d{chrono::days{123}};
		EXPECT_TRUE(d.time_since_epoch().count() == 123);
	}
}

}	// namespace hamon_chrono_test
