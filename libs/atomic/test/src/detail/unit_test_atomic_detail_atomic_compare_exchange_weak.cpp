/**
 *	@file	unit_test_atomic_detail_atomic_compare_exchange_weak.cpp
 *
 *	@brief	atomic_compare_exchange_weak のテスト
 */

#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>
#include <thread>

namespace hamon_atomic_test
{

namespace atomic_compare_exchange_weak_test
{

template <typename T>
void test()
{
	{
		T x = 3;
		T expected = 1;
		while (!hamon::detail::atomic_compare_exchange_weak(&x, &expected, T(2)));
		EXPECT_EQ(T(2), x);
		EXPECT_EQ(T(3), expected);
	}
	{
		T x = 3;
		T expected = 1;
		while (!hamon::detail::atomic_compare_exchange_weak(&x, &expected, T(2), hamon::memory_order::relaxed, hamon::memory_order::relaxed));
		EXPECT_EQ(T(2), x);
		EXPECT_EQ(T(3), expected);
	}
}

GTEST_TEST(Atomic, AtomicCompareExchangeWeakTest)
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

}	// namespace atomic_compare_exchange_weak_test

}	// namespace hamon_atomic_test
