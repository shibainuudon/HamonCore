/**
 *	@file	unit_test_mutex_timed_mutex_try_lock.cpp
 *
 *	@brief	try_lock のテスト
 *
 *	bool try_lock();
 */

#include <hamon/mutex/timed_mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_timed_mutex_test
{

namespace try_lock_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::timed_mutex>().try_lock()), bool>, "");
static_assert(noexcept(hamon::declval<hamon::timed_mutex>().try_lock()), "");	// TODO

GTEST_TEST(TimedMutexTest, TryLockTest)
{
	// Try to lock a mutex that is not locked yet. This should succeed.
	{
		hamon::timed_mutex m;
		bool succeeded = m.try_lock();
		EXPECT_TRUE(succeeded);
		m.unlock();
	}

	// Try to lock a mutex that is already locked. This should fail.
	{
		hamon::timed_mutex m;
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

}	// namespace hamon_timed_mutex_test
