/**
 *	@file	unit_test_atomic_detail_atomic_fetch_add.cpp
 *
 *	@brief	atomic_fetch_add のテスト
 */

#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>
#include <thread>

namespace hamon_atomic_test
{

namespace atomic_fetch_add_test
{

template <typename T>
void test(hamon::memory_order order)
{
	{
		T x = 3;
		auto before = hamon::detail::atomic_fetch_add(&x, T(2));
		EXPECT_EQ(T(3), before);
		EXPECT_EQ(T(5), x);
	}
	{
		T x = 42;
		auto before = hamon::detail::atomic_fetch_add(&x, T(13), order);
		EXPECT_EQ(T(42), before);
		EXPECT_EQ(T(55), x);
	}
}

GTEST_TEST(Atomic, AtomicFetchAddTest)
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
				// x += 2;
				hamon::detail::atomic_fetch_add(&x, 2);
			}
		}};
		std::thread t2{[&x]{
			for (int i = 0; i < 10000; ++i)
			{
				// x += 3;
				hamon::detail::atomic_fetch_add(&x, 3);
			}
		}};
		t1.join();
		t2.join();
		EXPECT_EQ(50000, x);
	}
}

}	// namespace atomic_fetch_add_test

}	// namespace hamon_atomic_test
