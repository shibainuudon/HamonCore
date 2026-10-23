/**
 *	@file	unit_test_thread_this_thread_sleep_for.cpp
 *
 *	@brief	this_thread::sleep_for のテスト
 *
 *	template<class Rep, class Period>
 *	void sleep_for(const chrono::duration<Rep, Period>& rel_time);
 */

#include <hamon/thread/this_thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/chrono.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace this_thread_sleep_for_test
{

GTEST_TEST(ThisThreadTest, SleepForTest)
{
	static_assert(!noexcept(hamon::this_thread::sleep_for(hamon::chrono::seconds(1))), "");
	static_assert(hamon::is_same_v<decltype(hamon::this_thread::sleep_for(hamon::chrono::seconds(1))), void>, "");

	hamon::this_thread::sleep_for(hamon::chrono::seconds(0));
	hamon::this_thread::sleep_for(hamon::chrono::seconds(-1));

	{
		auto start = hamon::chrono::high_resolution_clock::now();
		hamon::this_thread::sleep_for(hamon::chrono::nanoseconds(100));
		auto end = hamon::chrono::high_resolution_clock::now();
		hamon::chrono::duration<double, hamon::nano> elapsed = end - start;
		EXPECT_GE(elapsed.count(), 100.0);
	}
	{
		auto start = hamon::chrono::high_resolution_clock::now();
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds(10));
		auto end = hamon::chrono::high_resolution_clock::now();
		hamon::chrono::duration<double, hamon::milli> elapsed = end - start;
		EXPECT_GE(elapsed.count(), 10.0);
	}
}

}	// namespace this_thread_sleep_for_test

}	// namespace hamon_thread_test
