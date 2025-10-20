/**
 *	@file	unit_test_chrono_file_clock.cpp
 *
 *	@brief	file_clock のテスト
 */

#include <hamon/chrono/file_clock.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, FileClockTest)
{
	using Clock = hamon::chrono::file_clock;
	using rep        = typename Clock::rep;
	using period     = typename Clock::period;
	using duration   = typename Clock::duration;
	using time_point = typename Clock::time_point;

	static_assert(hamon::is_same<rep, typename duration::rep>::value, "");
	static_assert(hamon::is_same<period, typename duration::period>::value, "");
	static_assert(hamon::is_same<duration, typename time_point::duration>::value, "");
	static_assert(!Clock::is_steady, "");

	static_assert(hamon::is_signed<rep>::value, "");

	static_assert(noexcept(Clock::now()), "");
	static_assert(hamon::is_same<time_point, decltype(Clock::now())>::value, "");
	{
		auto t1 = Clock::now();
		EXPECT_TRUE(t1.time_since_epoch().count() != 0);
		EXPECT_TRUE(time_point::min() < t1);
		EXPECT_TRUE(time_point::max() > t1);
	}

	// Test round-trip through the system clock, starting from file_clock::now()
	{
		hamon::chrono::file_clock::time_point const ft = hamon::chrono::file_clock::now();
		auto st = hamon::chrono::file_clock::to_sys(ft);
		EXPECT_TRUE(ft == hamon::chrono::file_clock::from_sys(st));
	}

	// Test round-trip through the system clock, starting from system_clock::now()
	{
		hamon::chrono::system_clock::time_point const st = hamon::chrono::system_clock::now();
		auto ft = hamon::chrono::file_clock::from_sys(st);
		EXPECT_TRUE(st == hamon::chrono::file_clock::to_sys(ft));
	}

	// Make sure the value we get is in the ballpark of something reasonable
	{
		hamon::chrono::file_clock::time_point const file_now = hamon::chrono::file_clock::now();
		hamon::chrono::system_clock::time_point const sys_now = hamon::chrono::system_clock::now();
		{
			auto diff = sys_now - hamon::chrono::file_clock::to_sys(file_now);
			EXPECT_TRUE(hamon::chrono::milliseconds(-500) < diff && diff < hamon::chrono::milliseconds(500));
		}
		{
			auto diff = hamon::chrono::file_clock::from_sys(sys_now) - file_now;
			EXPECT_TRUE(hamon::chrono::milliseconds(-500) < diff && diff < hamon::chrono::milliseconds(500));
		}
	}

	// Make sure to_sys and from_sys are consistent with each other
	{
		hamon::chrono::file_clock::time_point const ft = hamon::chrono::file_clock::now();
		hamon::chrono::system_clock::time_point const st = hamon::chrono::system_clock::now();
		auto sys_diff = hamon::chrono::file_clock::to_sys(ft) - st;
		auto file_diff = ft - hamon::chrono::file_clock::from_sys(st);
		EXPECT_TRUE(sys_diff == file_diff);
	}
}

}	// namespace hamon_chrono_test
