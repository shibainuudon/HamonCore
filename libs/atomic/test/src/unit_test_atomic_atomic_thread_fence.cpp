/**
 *	@file	unit_test_atomic_atomic_thread_fence.cpp
 *
 *	@brief	atomic_thread_fence のテスト
 */

#include <hamon/atomic/atomic_thread_fence.hpp>
#include <hamon/atomic/atomic.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#include <thread>

namespace hamon_atomic_test
{
namespace atomic_thread_fence_test
{

inline HAMON_CXX14_CONSTEXPR bool constexpr_test()
{
	hamon::atomic_thread_fence(hamon::memory_order::relaxed);
	hamon::atomic_thread_fence(hamon::memory_order::acquire);
	hamon::atomic_thread_fence(hamon::memory_order::release);
	hamon::atomic_thread_fence(hamon::memory_order::acq_rel);
	hamon::atomic_thread_fence(hamon::memory_order::seq_cst);
	return true;
}

GTEST_TEST(Atomic, AtomicThreadFenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test());

	{
		int data = 0;
		hamon::atomic<bool> ready(false);

		std::thread t1
		{
			[&]()
			{
				data = 42;
				hamon::atomic_thread_fence(hamon::memory_order::release);
				ready.store(true, hamon::memory_order::relaxed);
			}
		};
		std::thread t2
		{
			[&]()
			{
				while (!ready.load(hamon::memory_order::relaxed)) {}
				hamon::atomic_thread_fence(hamon::memory_order::acquire);
				EXPECT_TRUE(data == 42);
			}
		};
		t1.join();
		t2.join();
	}
}

}	// namespace atomic_thread_fence_test
}	// namespace hamon_atomic_test
