/**
 *	@file	unit_test_atomic_detail_atomic_increment.cpp
 *
 *	@brief	atomic_increment のテスト
 */

#include <hamon/atomic/detail/atomic_increment.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>
#include <thread>

namespace hamon_atomic_test
{

namespace atomic_increment_test
{

template <typename T>
void test(hamon::memory_order order)
{
	{
		T x = 3;
		auto after = hamon::detail::atomic_increment(&x);
		EXPECT_EQ(T(4), after);
		EXPECT_EQ(T(4), x);
	}
	{
		T x = 42;
		auto after = hamon::detail::atomic_increment(&x, order);
		EXPECT_EQ(T(43), after);
		EXPECT_EQ(T(43), x);
	}
}

GTEST_TEST(Atomic, AtomicIncrementTest)
{
	test<signed char>(hamon::memory_order::relaxed);
	test<unsigned char>(hamon::memory_order::consume);
	test<short>(hamon::memory_order::acquire);
	test<unsigned short>(hamon::memory_order::release);
	test<int>(hamon::memory_order::acq_rel);
	test<unsigned int>(hamon::memory_order::seq_cst);
	test<long>(hamon::memory_order::relaxed);
	test<unsigned long>(hamon::memory_order::consume);
	test<long long>(hamon::memory_order::acquire);
	test<unsigned long long>(hamon::memory_order::release);

	{
		int x = 0;
		std::thread t1{[&x]{
			for (int i = 0; i < 10000; ++i)
			{
				// ++x;
				hamon::detail::atomic_increment(&x);
			}
		}};
		std::thread t2{[&x]{
			for (int i = 0; i < 10000; ++i)
			{
				// ++x;
				hamon::detail::atomic_increment(&x);
			}
		}};
		t1.join();
		t2.join();
		EXPECT_EQ(20000, x);
	}
}

}	// namespace atomic_increment_test

}	// namespace hamon_atomic_test
