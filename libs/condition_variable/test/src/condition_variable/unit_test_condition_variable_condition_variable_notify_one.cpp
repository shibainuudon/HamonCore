/**
 *	@file	unit_test_condition_variable_condition_variable_notify_one.cpp
 *
 *	@brief	notify_one のテスト
 *
 *	void notify_one() noexcept;
 */

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/atomic.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_test
{

namespace notify_one_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::condition_variable&>().notify_one()), void>, "");
static_assert(noexcept(hamon::declval<hamon::condition_variable&>().notify_one()), "");

hamon::condition_variable cv;
hamon::mutex mut;

hamon::atomic_int test1(0);
hamon::atomic_int test2(0);
hamon::atomic_int ready(2);
hamon::atomic_int which(0);

void f1()
{
	hamon::unique_lock<hamon::mutex> lk(mut);
	EXPECT_TRUE(test1 == 0);
	--ready;
	while (test1 == 0)
	{
		cv.wait(lk);
	}
	which = 1;
	EXPECT_TRUE(test1 == 1);
	test1 = 2;
}

void f2()
{
	hamon::unique_lock<hamon::mutex> lk(mut);
	EXPECT_TRUE(test2 == 0);
	--ready;
	while (test2 == 0)
	{
		cv.wait(lk);
	}
	which = 2;
	EXPECT_TRUE(test2 == 1);
	test2 = 2;
}

GTEST_TEST(ConditionVariableTest, NotifyOneTest)
{
	hamon::thread t1(f1);
	hamon::thread t2(f2);
	{
		while (ready > 0)
		{
			hamon::this_thread::yield();
		}
		// At this point:
		// 1) Both f1 and f2 have entered their condition variable wait.
		// 2) Either f1 or f2 has the mutex locked and is about to wait.
		hamon::unique_lock<hamon::mutex> lk(mut);
		test1 = 1;
		test2 = 1;
		ready = 1;
		cv.notify_one();
	}
	{
		while (which == 0)
		{
			hamon::this_thread::yield();
		}
		hamon::unique_lock<hamon::mutex> lk(mut);
		if (test1 == 2)
		{
			EXPECT_TRUE(test2 == 1);
			t1.join();
			test1 = 0;
		}
		else
		{
			EXPECT_TRUE(test1 == 1);
			EXPECT_TRUE(test2 == 2);
			t2.join();
			test2 = 0;
		}
		which = 0;
		cv.notify_one();
	}
	{
		while (which == 0)
		{
			hamon::this_thread::yield();
		}
		hamon::unique_lock<hamon::mutex> lk(mut);
		if (test1 == 2)
		{
			EXPECT_TRUE(test2 == 0);
			t1.join();
			test1 = 0;
		}
		else
		{
			EXPECT_TRUE(test1 == 0);
			EXPECT_TRUE(test2 == 2);
			t2.join();
			test2 = 0;
		}
	}
}

}	// namespace notify_one_test

}	// namespace hamon_condition_variable_test
