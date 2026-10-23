/**
 *	@file	unit_test_thread_this_thread_sleep_until.cpp
 *
 *	@brief	this_thread::sleep_until のテスト
 *
 *	template<class Clock, class Duration>
 *	void sleep_until(const chrono::time_point<Clock, Duration>& abs_time);
 */

#include <hamon/thread/this_thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/chrono.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace this_thread_sleep_until_test
{

GTEST_TEST(ThisThreadTest, SleepUntilTest)
{
	static_assert(!noexcept(hamon::this_thread::sleep_until(hamon::chrono::system_clock::now())), "");
	static_assert(hamon::is_same_v<decltype(hamon::this_thread::sleep_until(hamon::chrono::system_clock::now())), void>, "");

	{
		auto start = hamon::chrono::high_resolution_clock::now();
		hamon::this_thread::sleep_until(hamon::chrono::steady_clock::now() + hamon::chrono::milliseconds(10));
		auto end = hamon::chrono::high_resolution_clock::now();
		hamon::chrono::duration<double, hamon::milli> elapsed = end - start;
		EXPECT_GE(elapsed.count(), 10.0);
	}
	{
		auto start = hamon::chrono::high_resolution_clock::now();
		hamon::this_thread::sleep_until(hamon::chrono::system_clock::now() + hamon::chrono::milliseconds(20));
		auto end = hamon::chrono::high_resolution_clock::now();
		hamon::chrono::duration<double, hamon::milli> elapsed = end - start;
		EXPECT_GE(elapsed.count(), 20.0);
	}
}

}	// namespace this_thread_sleep_until_test

}	// namespace hamon_thread_test
