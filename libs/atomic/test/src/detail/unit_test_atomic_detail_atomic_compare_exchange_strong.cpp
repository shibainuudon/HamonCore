/**
 *	@file	unit_test_atomic_detail_atomic_compare_exchange_strong.cpp
 *
 *	@brief	atomic_compare_exchange_strong のテスト
 */

#include <hamon/atomic/detail/atomic_compare_exchange_strong.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>
#include <thread>

namespace hamon_atomic_test
{

namespace atomic_compare_exchange_strong_test
{

template <typename T>
void test()
{
	{
		T x = 3;
		T expected = 3;
		bool result = hamon::detail::atomic_compare_exchange_strong(&x, &expected, T(2));
		EXPECT_TRUE(result);
		EXPECT_EQ(T(2), x);
		EXPECT_EQ(T(3), expected);
	}
	{
		T x = 3;
		T expected = 1;
		bool result = hamon::detail::atomic_compare_exchange_strong(&x, &expected, T(2));
		EXPECT_FALSE(result);
		EXPECT_EQ(T(3), x);
		EXPECT_EQ(T(3), expected);
	}
	{
		T x = 3;
		T expected = 3;
		bool result = hamon::detail::atomic_compare_exchange_strong(&x, &expected, T(2), hamon::memory_order::relaxed, hamon::memory_order::relaxed);
		EXPECT_TRUE(result);
		EXPECT_EQ(T(2), x);
		EXPECT_EQ(T(3), expected);
	}
	{
		T x = 3;
		T expected = 1;
		bool result = hamon::detail::atomic_compare_exchange_strong(&x, &expected, T(2), hamon::memory_order::relaxed, hamon::memory_order::relaxed);
		EXPECT_FALSE(result);
		EXPECT_EQ(T(3), x);
		EXPECT_EQ(T(3), expected);
	}
}

GTEST_TEST(Atomic, AtomicCompareExchangeStrongTest)
{
	test<signed char>();
	test<unsigned char>();
	test<short>();
	test<unsigned short>();
	test<int>();
	test<unsigned int>();
	test<long>();
	test<unsigned long>();
	test<long long>();
	test<unsigned long long>();
}

}	// namespace atomic_compare_exchange_strong_test

}	// namespace hamon_atomic_test
