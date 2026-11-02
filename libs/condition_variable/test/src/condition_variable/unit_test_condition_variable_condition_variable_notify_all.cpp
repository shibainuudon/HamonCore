/**
 *	@file	unit_test_condition_variable_condition_variable_notify_all.cpp
 *
 *	@brief	notify_all のテスト
 *
 *	void notify_all() noexcept;
 */

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_test
{

namespace notify_all_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::condition_variable&>().notify_all()), void>, "");
static_assert(noexcept(hamon::declval<hamon::condition_variable&>().notify_all()), "");

hamon::condition_variable cv;
hamon::mutex mut;

int test0 = 0;
int test1 = 0;
int test2 = 0;

hamon::atomic<int> ready_count(0);

void f1()
{
	hamon::unique_lock<hamon::mutex> lk(mut);
	EXPECT_TRUE(test1 == 0);
	ready_count += 1;
	while (test1 == 0)
	{
		cv.wait(lk);
	}
	EXPECT_TRUE(test1 == 1);
	test1 = 2;
}

void f2()
{
	hamon::unique_lock<hamon::mutex> lk(mut);
	EXPECT_TRUE(test2 == 0);
	ready_count += 1;
	while (test2 == 0)
	{
		cv.wait(lk);
	}
	EXPECT_TRUE(test2 == 1);
	test2 = 2;
}

GTEST_TEST(ConditionVariableTest, NotifyAllTest)
{
	hamon::thread t1(f1);
	hamon::thread t2(f2);
	while (ready_count.load() != 2)
	{
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds(10));
	}
	{
		hamon::unique_lock<hamon::mutex>lk(mut);
		test1 = 1;
		test2 = 1;
	}
	cv.notify_all();
	{
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds(10));
		hamon::unique_lock<hamon::mutex>lk(mut);
	}
	t1.join();
	t2.join();
	EXPECT_TRUE(test1 == 2);
	EXPECT_TRUE(test2 == 2);
}

}	// namespace notify_all_test

}	// namespace hamon_condition_variable_test
