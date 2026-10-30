/**
 *	@file	unit_test_mutex_scoped_lock_ctor_adopt_lock.cpp
 *
 *	@brief	mutex_typeとadopt_lock_tを引数に取るコンストラクタのテスト
 *
 *	explicit scoped_lock(adopt_lock_t, MutexTypes&... m);
 */

#include <hamon/mutex/scoped_lock.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/recursive_mutex.hpp>
#include <hamon/mutex/adopt_lock_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_scoped_lock_test
{

namespace ctor_adopt_lock_test
{

static_assert( hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::adopt_lock_t, hamon::mutex&>, "");
static_assert(!hamon::is_nothrow_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::adopt_lock_t, hamon::mutex&>, "");
static_assert(!hamon::is_trivially_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::adopt_lock_t, hamon::mutex&>, "");
static_assert(!hamon::is_implicitly_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::adopt_lock_t, hamon::mutex&>, "");

static_assert( hamon::is_constructible_v<hamon::scoped_lock<>, hamon::adopt_lock_t>, "");
static_assert(!hamon::is_constructible_v<hamon::scoped_lock<>, hamon::adopt_lock_t, hamon::mutex&>, "");

static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::adopt_lock_t>, "");
static_assert( hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::adopt_lock_t, hamon::mutex&>, "");
static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::adopt_lock_t, hamon::mutex const&>, "");
static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::adopt_lock_t, hamon::mutex&, hamon::mutex&>, "");

static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex, hamon::recursive_mutex>, hamon::adopt_lock_t>, "");
static_assert( hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex, hamon::recursive_mutex>, hamon::adopt_lock_t, hamon::mutex&, hamon::recursive_mutex&>, "");
static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex, hamon::recursive_mutex>, hamon::adopt_lock_t, hamon::mutex&, hamon::mutex&>, "");

struct TestMutex
{
	bool locked = false;

	TestMutex() = default;

	void lock()
	{
		EXPECT_FALSE(locked);
		locked = true;
	}

	bool try_lock()
	{
		if (locked)
		{
			return false;
		}
		locked = true;
		return true;
	}

	void unlock()
	{
		EXPECT_TRUE(locked);
		locked = false;
	}

	TestMutex(TestMutex const&) = delete;
	TestMutex& operator=(TestMutex const&) = delete;
};

GTEST_TEST(ScopedLockTest, CtorAdoptLockTest)
{
	{
		using LG = hamon::scoped_lock<>;
		LG lg(hamon::adopt_lock);
	}
	{
		TestMutex m1;
		using LG = hamon::scoped_lock<TestMutex>;
		m1.lock();
		{
			LG lg(hamon::adopt_lock, m1);
			EXPECT_TRUE(m1.locked);
		}
		EXPECT_TRUE(!m1.locked);
	}
	{
		TestMutex m1, m2;
		using LG = hamon::scoped_lock<TestMutex, TestMutex>;
		m1.lock(); m2.lock();
		{
			LG lg(hamon::adopt_lock, m1, m2);
			EXPECT_TRUE(m1.locked && m2.locked);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked);
	}
	{
		TestMutex m1, m2, m3;
		using LG = hamon::scoped_lock<TestMutex, TestMutex, TestMutex>;
		m1.lock(); m2.lock(); m3.lock();
		{
			LG lg(hamon::adopt_lock, m1, m2, m3);
			EXPECT_TRUE(m1.locked && m2.locked && m3.locked);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked && !m3.locked);
	}
}

}	// namespace ctor_adopt_lock_test

}	// namespace hamon_scoped_lock_test
