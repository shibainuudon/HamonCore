/**
 *	@file	unit_test_atomic_atomic_overview.cpp
 *
 *	@brief	atomic のテスト
 */

#include <hamon/atomic/atomic.hpp>
#include <gtest/gtest.h>

#include <thread>

namespace hamon_atomic_test
{
namespace atomic_overview_test
{

// スピンロックの実装
// Boost Atomic Library - Usage Example
// http://www.boost.org/doc/libs/1_53_0/doc/html/atomic/usage_examples.html#boost_atomic.usage_examples.example_spinlock

class spinlock
{
private:
	enum LockState { Locked, Unlocked };
	hamon::atomic<LockState> state_;

public:
	spinlock() : state_(Unlocked) {}

	void lock()
	{
		// 現在の状態をLockedと入れ替える
		while (state_.exchange(Locked, hamon::memory_order_acquire) == Locked)
		{
			// busy-wait...アンロックされるまで待機
		}
	}

	void unlock()
	{
		// 値をUnlockedに更新
		state_.store(Unlocked, hamon::memory_order_release);
	}
};


class my_mutex
{
	hamon::atomic<bool> state_{ false }; // false:unlock, true:lock
public:
	void lock() noexcept
	{
		while (state_.exchange(true) == true)
		{
			state_.wait(true);
		}
	}

	void unlock() noexcept
	{
		state_.store(false);
		state_.notify_one();
	}
};

GTEST_TEST(AtomicTest, AtomicOverviewTest)
{
	{
		int x = 0;
		spinlock lock;

		auto f = [&]()
		{
			for (int i = 0; i < 10000; ++i)
			{
				lock.lock();
				x++;
				lock.unlock();
			}
		};

		std::thread t1{f};
		std::thread t2{f};

		t1.join();
		t2.join();

		EXPECT_EQ(20000, x);
	}
	{
		int x = 0;
		my_mutex mut;

		auto f = [&]()
		{
			for (int i = 0; i < 10000; ++i)
			{
				mut.lock();
				x++;
				mut.unlock();
			}
		};

		std::thread t1{f};
		std::thread t2{f};

		t1.join();
		t2.join();

		EXPECT_EQ(20000, x);
	}
}

}	// namespace atomic_overview_test
}	// namespace hamon_atomic_test
