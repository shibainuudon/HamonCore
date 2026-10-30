/**
 *	@file	unit_test_mutex_unique_lock_overview.cpp
 *
 *	@brief	unique_lock のテスト
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/mutex/try_to_lock_t.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/thread.hpp>
#include <gtest/gtest.h>

namespace hamon_unique_lock_test
{

namespace overview_test
{

hamon::atomic<bool> keep_waiting;
hamon::atomic<bool> child_thread_locked;
hamon::mutex mux;
bool main_thread_unlocked = false;
bool child_thread_unlocked = false;

void lock_thread()
{
	hamon::unique_lock<hamon::mutex> lock(mux);
	EXPECT_TRUE(main_thread_unlocked);
	main_thread_unlocked = false;
	child_thread_unlocked = true;
}

void try_lock_thread()
{
	hamon::unique_lock<hamon::mutex> lock(mux, hamon::try_to_lock_t());
	EXPECT_TRUE(lock.owns_lock());
	child_thread_locked = true;

	while (keep_waiting)
	{
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds(10));
	}

	child_thread_unlocked = true;
}

GTEST_TEST(UniqueLockTest, OverviewTest)
{
	{
		mux.lock();
		hamon::thread t(lock_thread);
		main_thread_unlocked = true;
		mux.unlock();
		t.join();
		EXPECT_TRUE(child_thread_unlocked);
	}

	{
		child_thread_unlocked = false;
		child_thread_locked = false;
		keep_waiting = true;
		hamon::thread t(try_lock_thread);
		while (!child_thread_locked)
		{
			hamon::this_thread::sleep_for(hamon::chrono::milliseconds(10));
		}
		EXPECT_TRUE(!mux.try_lock());
		keep_waiting = false;
		t.join();
		EXPECT_TRUE(child_thread_unlocked);
	}
}

}	// namespace overview_test

}	// namespace hamon_unique_lock_test
