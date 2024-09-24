/**
 *	@file	unit_test_atomic_detail_atomic_compare_exchange_strong.cpp
 *
 *	@brief	atomic_compare_exchange_strong のテスト
 */

#include <hamon/atomic/detail/atomic_compare_exchange_strong.hpp>
#include <gtest/gtest.h>
#include <thread>

GTEST_TEST(Atomic, AtomicCompareExchangeStrongTest)
{
	{
		long x = 3;
		long expected = 3;
		bool result = hamon::detail::atomic_compare_exchange_strong(&x, &expected, 2);
		EXPECT_TRUE(result);
		EXPECT_EQ(2, x);
		EXPECT_EQ(3, expected);
	}
	{
		long x = 3;
		long expected = 1;
		bool result = hamon::detail::atomic_compare_exchange_strong(&x, &expected, 2);
		EXPECT_FALSE(result);
		EXPECT_EQ(3, x);
		EXPECT_EQ(3, expected);
	}
}
