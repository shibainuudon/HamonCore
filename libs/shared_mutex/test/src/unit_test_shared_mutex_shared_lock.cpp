/**
 *	@file	unit_test_shared_mutex_shared_lock.cpp
 *
 *	@brief	shared_lock のテスト
 */

#include <hamon/shared_mutex/shared_lock.hpp>
#include <hamon/shared_mutex/shared_mutex.hpp>
#include <hamon/shared_mutex/shared_timed_mutex.hpp>
#include <hamon/chrono.hpp>
#include <gtest/gtest.h>

namespace hamon_shared_mutex_test
{

namespace shared_lock_test
{

template <typename Mutex>
void ctor_test()
{
	Mutex mtx;

	// default ctor
	{
		hamon::shared_lock<Mutex> lk;
		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == nullptr);
	}

	// ref mutex ctor
	{
		hamon::shared_lock<Mutex> lk(mtx);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// defer lock ctor
	{
		hamon::shared_lock<Mutex> lk(mtx, std::defer_lock);
		EXPECT_FALSE(lk.owns_lock());
		EXPECT_FALSE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
		lk.lock();
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// try to lock ctor
	{
		hamon::shared_lock<Mutex> lk(mtx, std::try_to_lock);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// adopt lock ctor
	{
		mtx.lock_shared();
		hamon::shared_lock<Mutex> lk(mtx, std::adopt_lock);
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// try lock shared until ctor
	{
		hamon::shared_lock<Mutex> lk(mtx, std::chrono::steady_clock::now() + std::chrono::seconds(3));
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}

	// try lock shared for ctor
	{
		hamon::shared_lock<Mutex> lk(mtx, std::chrono::seconds(3));
		EXPECT_TRUE(lk.owns_lock());
		EXPECT_TRUE((bool)lk);
		EXPECT_TRUE(lk.mutex() == &mtx);
	}
}

GTEST_TEST(SharedMutexTest, SharedLockTest)
{
	//ctor_test<hamon::shared_mutex>();
	ctor_test<hamon::shared_timed_mutex>();
}

}	// namespace shared_lock_test

}	// namespace hamon_shared_mutex_test
