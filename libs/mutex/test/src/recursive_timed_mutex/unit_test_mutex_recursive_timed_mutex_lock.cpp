/**
 *	@file	unit_test_mutex_recursive_timed_mutex_lock.cpp
 *
 *	@brief	lock のテスト
 *
 *	void lock();    // blocking
 */

#include <hamon/mutex/recursive_timed_mutex.hpp>
#include <hamon/atomic.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_recursive_timed_mutex_test
{

namespace lock_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::recursive_timed_mutex>().lock()), void>, "");
static_assert(!noexcept(hamon::declval<hamon::recursive_timed_mutex>().lock()), "");

bool is_lockable(hamon::recursive_timed_mutex& m)
{
	bool did_lock;
	hamon::thread t([&] {
		did_lock = m.try_lock();
		if (did_lock)
		{
			m.unlock(); // undo side effects
		}
	});
	t.join();

	return did_lock;
}

GTEST_TEST(RecursiveTimedMutexTest, LockTest)
{
	// Lock a mutex that is not locked yet. This should succeed.
	{
		hamon::recursive_timed_mutex m;
		m.lock();
		m.unlock();
	}

	// Lock a mutex that is already locked by this thread. This should succeed and the mutex should only
	// be unlocked after a matching number of calls to unlock() on the same thread.
	{
		hamon::recursive_timed_mutex m;
		int lock_count = 0;
		for (int i = 0; i != 10; ++i)
		{
			m.lock();
			++lock_count;
		}
		while (lock_count != 0)
		{
			EXPECT_FALSE(is_lockable(m));
			m.unlock();
			--lock_count;
		}
		EXPECT_TRUE(is_lockable(m));
	}

	// Lock a mutex that is already locked by another thread. This should block until it is unlocked.
	{
		hamon::atomic<bool> ready(false);
		hamon::recursive_timed_mutex m;
		m.lock();
		hamon::atomic<bool> is_locked_from_main(true);

		hamon::thread t([&] {
			ready = true;
			m.lock();
			EXPECT_FALSE(is_locked_from_main);
			m.unlock();
		});

		while (!ready)
		{
			/* spin */;
		}

		// We would rather signal this after we unlock, but that would create a race condition.
		// We instead signal it before we unlock, which means that it's technically possible for
		// the thread to take the lock while main is still holding it yet for the test to still pass.
		is_locked_from_main = false;
		m.unlock();

		t.join();
	}

	// Make sure that at most one thread can acquire the mutex concurrently.
	{
		hamon::atomic<int> counter(0);
		hamon::recursive_timed_mutex mutex;

		hamon::vector<hamon::thread> threads;
		for (int i = 0; i != 10; ++i)
		{
			threads.push_back(hamon::thread([&] {
				mutex.lock();
				counter++;
				EXPECT_TRUE(counter == 1);
				counter--;
				mutex.unlock();
			}));
		}

		for (auto& t : threads)
		{
			t.join();
		}
	}
}

}	// namespace lock_test

}	// namespace hamon_recursive_timed_mutex_test
