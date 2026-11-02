/**
 *	@file	unit_test_condition_variable_condition_variable_any_notify_one.cpp
 *
 *	@brief	notify_one のテスト
 *
 *	void notify_one() noexcept;
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/atomic.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_any_test
{

namespace notify_one_test
{

hamon::condition_variable_any cv;

typedef hamon::timed_mutex L0;
typedef hamon::unique_lock<L0> L1;

L0 m0;

int test0 = 0;
int test1 = 0;
int test2 = 0;

void f1()
{
	L1 lk(m0);
	EXPECT_TRUE(test1 == 0);
	while (test1 == 0)
	{
		cv.wait(lk);
	}
	EXPECT_TRUE(test1 == 1);
	test1 = 2;
}

void f2()
{
	L1 lk(m0);
	EXPECT_TRUE(test2 == 0);
	while (test2 == 0)
	{
		cv.wait(lk);
	}
	EXPECT_TRUE(test2 == 1);
	test2 = 2;
}

GTEST_TEST(ConditionVariableAnyTest, NotifyOneTest)
{
	static_assert(hamon::is_same_v<decltype(cv.notify_one()), void>, "");
	static_assert(noexcept(cv.notify_one()), "");

	hamon::thread t1(f1);
	hamon::thread t2(f2);
	hamon::this_thread::sleep_for(hamon::chrono::milliseconds(10));	// 100
	{
		L1 lk(m0);
		test1 = 1;
		test2 = 1;
	}
	cv.notify_one();
	{
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds(10));	// 100
		L1 lk(m0);
	}
	if (test1 == 2)
	{
		t1.join();
		test1 = 0;
	}
	else if (test2 == 2)
	{
		t2.join();
		test2 = 0;
	}
	else
	{
		EXPECT_TRUE(false);
	}

	cv.notify_one();
	{
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds(10));	// 100
		L1 lk(m0);
	}
	if (test1 == 2)
	{
		t1.join();
		test1 = 0;
	}
	else if (test2 == 2)
	{
		t2.join();
		test2 = 0;
	}
	else
	{
		EXPECT_TRUE(false);
	}
}

}	// namespace notify_one_test

}	// namespace hamon_condition_variable_any_test
