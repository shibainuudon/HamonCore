/**
 *	@file	unit_test_condition_variable_condition_variable_wait.cpp
 *
 *	@brief	wait(lock) のテスト
 *
 *	void wait(unique_lock<mutex>& lock);
 */

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_test
{

namespace wait_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::condition_variable&>().wait(hamon::declval<hamon::unique_lock<hamon::mutex>&>())), void>, "");
static_assert(!noexcept(hamon::declval<hamon::condition_variable&>().wait(hamon::declval<hamon::unique_lock<hamon::mutex>&>())), "");

hamon::condition_variable cv;
hamon::mutex mut;

int test1 = 0;
int test2 = 0;

void f()
{
	hamon::unique_lock<hamon::mutex> lk(mut);
	EXPECT_TRUE(test2 == 0);
	test1 = 1;
	cv.notify_one();
	while (test2 == 0)
	{
		cv.wait(lk);
	}
	EXPECT_TRUE(test2 != 0);
}

GTEST_TEST(ConditionVariableTest, WaitTest)
{
	hamon::unique_lock<hamon::mutex> lk(mut);
	hamon::thread t(f);
	EXPECT_TRUE(test1 == 0);
	while (test1 == 0)
	{
		cv.wait(lk);
	}
	EXPECT_TRUE(test1 != 0);
	test2 = 1;
	lk.unlock();
	cv.notify_one();
	t.join();
}

}	// namespace wait_test

}	// namespace hamon_condition_variable_test
