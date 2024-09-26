/**
 *	@file	unit_test_atomic_detail_atomic_exchange.cpp
 *
 *	@brief	atomic_exchange のテスト
 */

#include <hamon/atomic/detail/atomic_exchange.hpp>
#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>
#include <thread>
#include <vector>

namespace hamon_atomic_test
{

namespace atomic_exchange_test
{

template <typename T>
void test(hamon::memory_order order)
{
	{
		T x = 1;
		auto before = hamon::detail::atomic_exchange(&x, T(2));
		EXPECT_EQ(T(1), before);
		EXPECT_EQ(T(2), x);
	}
	{
		T x = 4;
		auto before = hamon::detail::atomic_exchange(&x, T(3), order);
		EXPECT_EQ(T(4), before);
		EXPECT_EQ(T(3), x);
	}
}

GTEST_TEST(Atomic, AtomicExchangeTest)
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
		int count = 0;
		char lock = 0;
		auto f = [&](int n)
		{
			// ループに入る前に適当に待ち時間を入れて、できるだけ他のスレッドと同時に実行されるようにする
			std::this_thread::sleep_for(std::chrono::milliseconds(10 * n));

			for (int i = 0; i < 1000; ++i)
			{
				// spinlock
				while (hamon::detail::atomic_exchange(&lock, char(1), hamon::memory_order::acquire) == 1) {}

				// ここは排他処理されている
				++count;

				hamon::detail::atomic_store(&lock, char(0), hamon::memory_order::release);
			}
		};

		std::vector<std::thread> ts;
		for (int i = 0; i < 10; ++i)
		{
			ts.emplace_back(f, i);
		}
		for (auto& t : ts)
		{
			t.join();
		}

		EXPECT_EQ(1000 * 10, count);
	}
}

}	// namespace atomic_exchange_test

}	// namespace hamon_atomic_test
