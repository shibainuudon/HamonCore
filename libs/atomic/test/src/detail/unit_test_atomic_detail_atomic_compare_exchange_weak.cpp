/**
 *	@file	unit_test_atomic_detail_atomic_compare_exchange_weak.cpp
 *
 *	@brief	atomic_compare_exchange_weak のテスト
 */

#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <gtest/gtest.h>
#include <thread>

GTEST_TEST(Atomic, AtomicCompareExchangeWeakTest)
{
	{
		long x = 3;
		long expected = 1;
		while (!hamon::detail::atomic_compare_exchange_weak(&x, &expected, 2));
		EXPECT_EQ(2, x);
		EXPECT_EQ(3, expected);
	}
}
