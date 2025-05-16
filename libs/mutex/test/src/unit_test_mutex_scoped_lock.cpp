/**
 *	@file	unit_test_mutex_scoped_lock.cpp
 *
 *	@brief	scoped_lock のテスト
 */

#include <hamon/mutex/scoped_lock.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>

namespace hamon_mutex_test
{

namespace scoped_lock_test
{

template <typename T, typename = void>
struct has_mutex_type
	: public hamon::false_type {};

template <typename T>
struct has_mutex_type<T, hamon::void_t<typename T::mutex_type>>
	: public hamon::true_type {};

struct TestMutex
{
	bool locked = false;

	TestMutex() = default;

	~TestMutex()
	{
		EXPECT_TRUE(!locked);
	}

	void lock()
	{
		EXPECT_TRUE(!locked); locked = true;
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

void test_mutex()
{
	{
		using LG = hamon::scoped_lock<>;
		static_assert(!has_mutex_type<LG>::value, "");

		LG lg;
		(void)lg;
	}
	{
		using LG = hamon::scoped_lock<TestMutex>;
		static_assert( has_mutex_type<LG>::value, "");
		static_assert(hamon::is_same<typename LG::mutex_type, TestMutex>::value, "");

		TestMutex m1;
		{
			LG lg(m1);
			EXPECT_TRUE(m1.locked);
		}
		EXPECT_TRUE(!m1.locked);
	}
	{
		using LG = hamon::scoped_lock<TestMutex, TestMutex>;
		static_assert(!has_mutex_type<LG>::value, "");

		TestMutex m1, m2;
		{
			LG lg(m1, m2);
			EXPECT_TRUE(m1.locked && m2.locked);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked);
	}
	{
		using LG = hamon::scoped_lock<TestMutex, TestMutex, TestMutex>;
		static_assert(!has_mutex_type<LG>::value, "");

		TestMutex m1, m2, m3;
		{
			LG lg(m1, m2, m3);
			EXPECT_TRUE(m1.locked && m2.locked && m3.locked);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked && !m3.locked);
	}
}

void test_adopt_lock()
{
	{
		using LG = hamon::scoped_lock<>;
		static_assert(!has_mutex_type<LG>::value, "");
		LG lg(std::adopt_lock);
	}
	{
		using LG = hamon::scoped_lock<TestMutex>;
		static_assert( has_mutex_type<LG>::value, "");
		static_assert(hamon::is_same<typename LG::mutex_type, TestMutex>::value, "");

		TestMutex m1;
		m1.lock();
		{
			LG lg(std::adopt_lock, m1);
			EXPECT_TRUE(m1.locked);
		}
		EXPECT_TRUE(!m1.locked);
	}
	{
		using LG = hamon::scoped_lock<TestMutex, TestMutex>;
		static_assert(!has_mutex_type<LG>::value, "");

		TestMutex m1, m2;
		m1.lock(); m2.lock();
		{
			LG lg(std::adopt_lock, m1, m2);
			EXPECT_TRUE(m1.locked && m2.locked);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked);
	}
	{
		using LG = hamon::scoped_lock<TestMutex, TestMutex, TestMutex>;
		static_assert(!has_mutex_type<LG>::value, "");

		TestMutex m1, m2, m3;
		m1.lock(); m2.lock(); m3.lock();
		{
			LG lg(std::adopt_lock, m1, m2, m3);
			EXPECT_TRUE(m1.locked && m2.locked && m3.locked);
		}
		EXPECT_TRUE(!m1.locked && !m2.locked && !m3.locked);
	}
}

#if !defined(HAMON_NO_EXCEPTIONS)
struct TestMutexThrows
{
	bool locked = false;
	bool throws_on_lock = false;

	TestMutexThrows() = default;
	~TestMutexThrows()
	{
		EXPECT_TRUE(!locked);
	}

	void lock()
	{
		EXPECT_TRUE(!locked);
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

void test_exceptions()
{
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
		catch (int) {}
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
		catch (int) {}
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
		catch (int) {}
		EXPECT_TRUE(!m1.locked && !m2.locked && !m3.locked);
	}
#endif
}

void test_ctad()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		TestMutex m;
		hamon::scoped_lock lk(m);
		static_assert(hamon::is_same<decltype(lk), hamon::scoped_lock<TestMutex>>::value, "");
	}
	{
		std::mutex m;
		hamon::scoped_lock lk(m);
		static_assert(hamon::is_same<decltype(lk), hamon::scoped_lock<std::mutex>>::value, "");
	}
	{
		std::mutex m1;
		std::recursive_mutex m2;
		hamon::scoped_lock lk(m1, m2);
		static_assert(hamon::is_same<decltype(lk), hamon::scoped_lock<std::mutex, std::recursive_mutex>>::value, "");
	}
	{
		std::recursive_mutex m1;
		std::recursive_timed_mutex m2;
		std::mutex m3;
		hamon::scoped_lock lk(m1, m2, m3);
		static_assert(hamon::is_same<decltype(lk), hamon::scoped_lock<std::recursive_mutex, std::recursive_timed_mutex, std::mutex>>::value, "");
	}
#endif
}

GTEST_TEST(MutexTest, ScopedLockTest)
{
	test_mutex();
	test_adopt_lock();
	test_exceptions();
	test_ctad();
}

}	// namespace scoped_lock_test

}	// namespace hamon_mutex_test
