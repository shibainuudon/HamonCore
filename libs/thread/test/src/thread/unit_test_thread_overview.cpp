/**
 *	@file	unit_test_thread_overview.cpp
 *
 *	@brief	thread のテスト
 */

#include <hamon/thread/thread.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace thread_test
{

GTEST_TEST(ComplexTest, AbsTest)
{
	// https://cpprefjp.github.io/reference/thread/thread.html
	{
		int x = 0, y = 0;

		hamon::thread t([&] { ++x; });
		--y;
		t.join();

		EXPECT_TRUE(x == 1 && y == -1);
	}
}

}	// namespace thread_test

}	// namespace hamon_thread_test
