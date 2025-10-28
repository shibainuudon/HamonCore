/**
 *	@file	unit_test_chrono_clock_cast.cpp
 *
 *	@brief	clock_cast のテスト
 */

#include <hamon/chrono/clock_cast.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/chrono/year_month_day.hpp>
#include <hamon/chrono/utc_clock.hpp>
#include <hamon/chrono/tai_clock.hpp>
#include <hamon/chrono/gps_clock.hpp>
#include <hamon/chrono/file_clock.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace clock_cast_test
{

GTEST_TEST(ChronoTest, ClockCastTest)
{
	using namespace hamon::chrono;

	sys_days st(2020_y / January / 1);
	const auto ut = utc_clock::from_sys(st);
	const auto tt = tai_clock::from_utc(ut);
	const auto gt = gps_clock::from_utc(ut);
	const auto ft = file_clock::from_sys(st);

	EXPECT_TRUE(clock_cast<utc_clock>(ut) == ut);
	EXPECT_TRUE(clock_cast<utc_clock>(st) == ut);
	EXPECT_TRUE(clock_cast<utc_clock>(tt) == ut);
	EXPECT_TRUE(clock_cast<utc_clock>(gt) == ut);
	EXPECT_TRUE(clock_cast<utc_clock>(ft) == ut);

	EXPECT_TRUE(clock_cast<system_clock>(ut) == st);
	EXPECT_TRUE(clock_cast<system_clock>(st) == st);
	EXPECT_TRUE(clock_cast<system_clock>(tt) == st);
	EXPECT_TRUE(clock_cast<system_clock>(gt) == st);
	EXPECT_TRUE(clock_cast<system_clock>(ft) == st);

	EXPECT_TRUE(clock_cast<tai_clock>(ut) == tt);
	EXPECT_TRUE(clock_cast<tai_clock>(st) == tt);
	EXPECT_TRUE(clock_cast<tai_clock>(tt) == tt);
	EXPECT_TRUE(clock_cast<tai_clock>(gt) == tt);
	EXPECT_TRUE(clock_cast<tai_clock>(ft) == tt);

	EXPECT_TRUE(clock_cast<gps_clock>(ut) == gt);
	EXPECT_TRUE(clock_cast<gps_clock>(st) == gt);
	EXPECT_TRUE(clock_cast<gps_clock>(tt) == gt);
	EXPECT_TRUE(clock_cast<gps_clock>(gt) == gt);
	EXPECT_TRUE(clock_cast<gps_clock>(ft) == gt);

	EXPECT_TRUE(clock_cast<file_clock>(ut) == ft);
	EXPECT_TRUE(clock_cast<file_clock>(st) == ft);
	EXPECT_TRUE(clock_cast<file_clock>(tt) == ft);
	EXPECT_TRUE(clock_cast<file_clock>(gt) == ft);
	EXPECT_TRUE(clock_cast<file_clock>(ft) == ft);

	// N4885 [time.clock.utc.overview]/1 Example 1
	EXPECT_TRUE(clock_cast<utc_clock>(sys_seconds{ sys_days{1970_y / January / 1} }).time_since_epoch() == 0_s);
	EXPECT_TRUE(clock_cast<utc_clock>(sys_seconds{ sys_days{2000_y / January / 1} }).time_since_epoch() == 946684822_s);
}

}	// namespace clock_cast_test

}	// namespace hamon_chrono_test
