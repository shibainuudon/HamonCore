/**
 *	@file	unit_test_mutex_lock_guard_ctor_mutex.cpp
 *
 *	@brief	mutex_typeを引数に取るコンストラクタのテスト
 *
 *	explicit lock_guard(mutex_type& m);
 */

#include <hamon/mutex/lock_guard.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "lock_guard_test_helper.hpp"

namespace hamon_lock_guard_test
{

namespace ctor_mutex_test
{

static_assert( hamon::is_constructible_v<hamon::lock_guard<MyMutex>, MyMutex&>, "");
static_assert(!hamon::is_nothrow_constructible_v<hamon::lock_guard<MyMutex>, MyMutex&>, "");
static_assert(!hamon::is_trivially_constructible_v<hamon::lock_guard<MyMutex>, MyMutex&>, "");
static_assert(!hamon::is_implicitly_constructible_v<hamon::lock_guard<MyMutex>, MyMutex&>, "");

void do_try_lock(hamon::mutex& m)
{
	EXPECT_FALSE(m.try_lock());
}

GTEST_TEST(LockGuardTest, CtorMutexTest)
{
	{
		MyMutex m;
		EXPECT_FALSE(m.locked);
		hamon::lock_guard<MyMutex> lg(m);
		EXPECT_TRUE(m.locked);
	}
	{
		hamon::mutex m;
		{
			hamon::lock_guard<hamon::mutex> lg(m);
			hamon::thread t(do_try_lock, hamon::ref(m));
			t.join();
		}

		// This should work because the lock_guard unlocked the mutex when it was destroyed above.
		m.lock();
		m.unlock();
	}
}

}	// namespace ctor_mutex_test

}	// namespace hamon_lock_guard_test
