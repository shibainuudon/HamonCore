/**
 *	@file	unit_test_thread.cpp
 *
 *	@brief	thread のテスト
 */

#include <hamon/thread.hpp>
#include <hamon/chrono.hpp>
#include <gtest/gtest.h>

GTEST_TEST(ThreadTest, ThreadTest)
{
#if 0
	hamon::thread t1([&] {
		for (int i = 0; i < 10; ++i)
		{
			std::cout << "Thread 1: " << i << std::endl;
			hamon::this_thread::sleep_for(hamon::chrono::seconds(1));
		}
	});
	hamon::thread t2([&] {
		for (int i = 0; i < 5; ++i)
		{
			std::cout << "Thread 2: " << i << std::endl;
			hamon::this_thread::sleep_for(hamon::chrono::seconds(2));
		}
	});

	for (int i = 0; i < 5; ++i)
	{
		std::cout << "Main Thread: " << i << std::endl;
		hamon::this_thread::sleep_for(hamon::chrono::seconds(3));
	}

	t1.join();
	t2.join();
#endif
}
