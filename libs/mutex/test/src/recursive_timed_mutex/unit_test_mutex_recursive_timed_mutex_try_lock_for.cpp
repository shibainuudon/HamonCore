/**
 *	@file	unit_test_mutex_recursive_timed_mutex_try_lock_for.cpp
 *
 *	@brief	try_lock_for のテスト
 *
 *	template<class Rep, class Period>
 *	bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
 */

#include <hamon/mutex/recursive_timed_mutex.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_recursive_timed_mutex_test
{

namespace try_lock_for_test
{

namespace chrono = std::chrono;

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::recursive_timed_mutex>().try_lock_for(chrono::milliseconds(1))), bool>, "");
static_assert(!noexcept(hamon::declval<hamon::recursive_timed_mutex>().try_lock_for(chrono::milliseconds(1))), "");

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

template <class Function>
chrono::microseconds measure(Function f)
{
	auto start = chrono::high_resolution_clock::now();
	f();
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::microseconds>(end - start);
}

GTEST_TEST(RecursiveTimedMutexTest, TryLockForTest)
{
	// Try to lock a mutex that is not locked yet. This should succeed immediately.
	{
		hamon::recursive_timed_mutex m;
		bool succeeded = m.try_lock_for(chrono::milliseconds(1));
		EXPECT_TRUE(succeeded);
		m.unlock();
	}

	// Lock a mutex that is already locked by this thread. This should succeed immediately and the mutex
	// should only be unlocked after a matching number of calls to unlock() on the same thread.
	{
		hamon::recursive_timed_mutex m;
		int lock_count = 0;
		for (int i = 0; i != 10; ++i)
		{
			EXPECT_TRUE(m.try_lock_for(chrono::milliseconds(1)));
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

	// Try to lock an already-locked mutex for a long enough amount of time and succeed.
	// This is technically flaky, but we use such long durations that it should pass even
	// in slow or contended environments.
	{
		chrono::milliseconds const wait_time(100);
		chrono::milliseconds const tolerance = wait_time * 3;
		hamon::atomic<bool> ready(false);

		hamon::recursive_timed_mutex m;
		m.lock();

		hamon::thread t([&] {
			auto elapsed = measure([&] {
				ready = true;
				bool succeeded = m.try_lock_for(wait_time);
				EXPECT_TRUE(succeeded);
				m.unlock();
			});

			// Ensure we didn't wait significantly longer than our timeout. This is technically
			// flaky and non-conforming because an implementation is free to block for arbitrarily
			// long, but any decent quality implementation should pass this test.
			EXPECT_TRUE(elapsed - wait_time < tolerance);
		});

		// Wait for the thread to be ready to take the lock before we unlock it from here, otherwise
		// there's a high chance that we're not testing the "locking an already locked" mutex use case.
		// There is still technically a race condition here.
		while (!ready)
		{
			/* spin */;
		}
//		hamon::this_thread::sleep_for(wait_time / 5);	// TODO
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds((wait_time / 5).count()));

		m.unlock(); // this should allow the thread to lock 'm'
		t.join();
	}

	// Try to lock an already-locked mutex for a short amount of time and fail.
	// Again, this is technically flaky but we use such long durations that it should work.
	{
		chrono::milliseconds const wait_time(10);
		chrono::milliseconds const tolerance(750); // in case the thread we spawned goes to sleep or something

		hamon::recursive_timed_mutex m;
		m.lock();

		hamon::thread t([&] {
			auto elapsed = measure([&] {
				bool succeeded = m.try_lock_for(wait_time);
				EXPECT_FALSE(succeeded);
			});

			// Ensure we failed within some bounded time.
			EXPECT_TRUE(elapsed - wait_time < tolerance);
		});

		t.join();

		m.unlock();
	}
}

}	// namespace try_lock_for_test

}	// namespace hamon_recursive_timed_mutex_test
