/**
 *	@file	unit_test_mutex_scoped_lock_ctor_mutex.cpp
 *
 *	@brief	mutex_typeを引数に取るコンストラクタのテスト
 *
 *	explicit scoped_lock(MutexTypes&... m);
 */

#include <hamon/mutex/scoped_lock.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/recursive_mutex.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_scoped_lock_test
{

namespace ctor_mutex_test
{

static_assert( hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::mutex&>, "");
static_assert(!hamon::is_nothrow_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::mutex&>, "");
static_assert(!hamon::is_trivially_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::mutex&>, "");
static_assert(!hamon::is_implicitly_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::mutex&>, "");

static_assert( hamon::is_constructible_v<hamon::scoped_lock<>>, "");
static_assert(!hamon::is_constructible_v<hamon::scoped_lock<>, hamon::mutex&>, "");

static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>>, "");
static_assert( hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::mutex&>, "");
static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::mutex const&>, "");
static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::mutex>, hamon::mutex&, hamon::mutex&>, "");

static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::recursive_mutex, hamon::mutex>, hamon::recursive_mutex&>, "");
static_assert( hamon::is_constructible_v<hamon::scoped_lock<hamon::recursive_mutex, hamon::mutex>, hamon::recursive_mutex&, hamon::mutex&>, "");
static_assert(!hamon::is_constructible_v<hamon::scoped_lock<hamon::recursive_mutex, hamon::mutex>, hamon::recursive_mutex&, hamon::recursive_mutex&>, "");

struct TestMutex
{
	bool locked = false;

	TestMutex() = default;

	~TestMutex()
	{
		EXPECT_FALSE(locked);
	}

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

#if !defined(HAMON_NO_EXCEPTIONS)
struct TestMutexThrows
{
	bool locked = false;
	bool throws_on_lock = false;

	TestMutexThrows() = default;

	~TestMutexThrows()
	{
		EXPECT_FALSE(locked);
	}

	void lock()
	{
		EXPECT_FALSE(locked);
		if (throws_on_lock)
		{
			throw 42;
		}
		locked = true;
	}

	bool try_lock()
	{
		if (locked)
		{
			return false;
		}
		lock();
		return true;
	}

	void unlock()
	{
		EXPECT_TRUE(locked);
		locked = false;
	}

	TestMutexThrows(TestMutexThrows const&) = delete;
	TestMutexThrows& operator=(TestMutexThrows const&) = delete;
};
#endif

GTEST_TEST(ScopedLockTest, CtorMutexTest)
{
	{
		using LG = hamon::scoped_lock<>;
		LG lg;
		(void)lg;
	}
	{
		using LG = hamon::scoped_lock<TestMutex>;
		TestMutex m1;
		{
			LG lg(m1);
			EXPECT_TRUE(m1.locked);
		}
		EXPECT_TRUE(!m1.locked);
	}
	{
		using LG = hamon::scoped_lock<TestMutex, TestMutex>;
		TestMutex m1, m2;
		{
			LG lg(m1, m2);
			EXPECT_TRUE(m1.locked && m2.locked);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked);
	}
	{
		using LG = hamon::scoped_lock<TestMutex, TestMutex, TestMutex>;
		TestMutex m1, m2, m3;
		{
			LG lg(m1, m2, m3);
			EXPECT_TRUE(m1.locked && m2.locked && m3.locked);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked && !m3.locked);
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using MT = TestMutexThrows;
		using LG = hamon::scoped_lock<MT>;
		MT m1;
		m1.throws_on_lock = true;
		try
		{
			LG lg(m1);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
		EXPECT_TRUE(!m1.locked);
	}
	{
		using MT = TestMutexThrows;
		using LG = hamon::scoped_lock<MT, MT>;
		MT m1, m2;
		m1.throws_on_lock = true;
		try
		{
			LG lg(m1, m2);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked);
	}
	{
		using MT = TestMutexThrows;
		using LG = hamon::scoped_lock<MT, MT, MT>;
		MT m1, m2, m3;
		m2.throws_on_lock = true;
		try
		{
			LG lg(m1, m2, m3);
			EXPECT_TRUE(false);
		}
		catch (int)
		{
		}
		catch (...)
		{
			EXPECT_TRUE(false);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked && !m3.locked);
	}
#endif
}

}	// namespace ctor_mutex_test

}	// namespace hamon_scoped_lock_test
