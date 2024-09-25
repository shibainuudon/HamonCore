/**
 *	@file	unit_test_atomic_memory_order.cpp
 *
 *	@brief	memory_order のテスト
 */

#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>

GTEST_TEST(Atomic, MemoryOrderTest)
{
	EXPECT_EQ(hamon::memory_order::relaxed, hamon::memory_order_relaxed);
	EXPECT_EQ(hamon::memory_order::consume, hamon::memory_order_consume);
	EXPECT_EQ(hamon::memory_order::acquire, hamon::memory_order_acquire);
	EXPECT_EQ(hamon::memory_order::release, hamon::memory_order_release);
	EXPECT_EQ(hamon::memory_order::acq_rel, hamon::memory_order_acq_rel);
	EXPECT_EQ(hamon::memory_order::seq_cst, hamon::memory_order_seq_cst);
}
