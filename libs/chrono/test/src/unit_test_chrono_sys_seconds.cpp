/**
 *	@file	unit_test_chrono_sys_seconds.cpp
 *
 *	@brief	sys_seconds のテスト
 */

#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, SysSecondsTest)
{
#if 0	// TODO
	namespace chrono = hamon::chrono;
	using namespace hamon::chrono_literals;
	{
		std::stringstream ss;
		ss << chrono::sys_seconds{0_s};
		EXPECT_EQ("1970-01-01 00:00:00", ss.str());
	}
	{
		std::stringstream ss;
		ss << chrono::sys_seconds{946'684'800_s};
		EXPECT_EQ("2000-01-01 00:00:00", ss.str());
	}
	{
		std::stringstream ss;
		ss << chrono::sys_seconds{946'688'523_s};
		EXPECT_EQ("2000-01-01 01:02:03", ss.str());
	}
#endif
}

}	// namespace hamon_chrono_test
