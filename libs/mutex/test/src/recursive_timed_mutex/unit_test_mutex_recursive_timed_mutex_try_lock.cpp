/**
 *	@file	unit_test_mutex_recursive_timed_mutex_try_lock.cpp
 *
 *	@brief	try_lock のテスト
 *
 *	bool try_lock();
 */

#include <hamon/mutex/recursive_timed_mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_recursive_timed_mutex_test
{

namespace try_lock_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::recursive_timed_mutex>().try_lock()), bool>, "");
static_assert(noexcept(hamon::declval<hamon::recursive_timed_mutex>().try_lock()), "");	// TODO

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

GTEST_TEST(RecursiveTimedMutexTest, TryLockTest)
{
	// Try to lock a mutex that is not locked yet. This should succeed.
	{
		hamon::recursive_timed_mutex m;
		bool succeeded = m.try_lock();
		EXPECT_TRUE(succeeded);
		m.unlock();
	}

	// Try to lock a mutex that is already locked by this thread. This should succeed and the mutex should only
	// be unlocked after a matching number of calls to unlock() on the same thread.
	{
		hamon::recursive_timed_mutex m;
		int lock_count = 0;
		for (int i = 0; i != 10; ++i)
		{
			EXPECT_TRUE(m.try_lock());
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

	// Try to lock a mutex that is already locked by another thread. This should fail.
	{
		hamon::recursive_timed_mutex m;
		m.lock();

		hamon::thread t([&] {
			for (int i = 0; i != 10; ++i)
			{
				bool succeeded = m.try_lock();
				EXPECT_FALSE(succeeded);
			}
		});
		t.join();

		m.unlock();
	}
}

}	// namespace try_lock_test

}	// namespace hamon_recursive_timed_mutex_test
