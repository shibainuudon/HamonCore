/**
 *	@file	unit_test_atomic_detail_atomic_fetch_sub.cpp
 *
 *	@brief	atomic_fetch_sub のテスト
 */

#include <hamon/atomic/detail/atomic_fetch_sub.hpp>
#include <gtest/gtest.h>
#include <thread>

GTEST_TEST(Atomic, AtomicFetchSubTest)
{
	{
		long x = 3;
		long before = hamon::detail::atomic_fetch_sub(&x, 2);
		EXPECT_EQ(3, before);
		EXPECT_EQ(1, x);
	}
	{
		long x = 0;
		std::thread t1{[&x]{
			for (int i = 0; i < 10000; ++i)
			{
				// x -= 2;
				hamon::detail::atomic_fetch_sub(&x, 2);
			}
		}};
		std::thread t2{[&x]{
			for (int i = 0; i < 10000; ++i)
			{
				// x -= 3;
				hamon::detail::atomic_fetch_sub(&x, 3);
			}
		}};
		t1.join();
		t2.join();
		EXPECT_EQ(-50000, x);
	}
}
