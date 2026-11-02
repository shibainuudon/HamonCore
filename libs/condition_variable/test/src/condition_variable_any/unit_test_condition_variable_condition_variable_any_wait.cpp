/**
 *	@file	unit_test_condition_variable_condition_variable_any_wait.cpp
 *
 *	@brief	wait(lock) のテスト
 *
 *	template<class Lock>
 *	void wait(Lock& lock);
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_any_test
{

namespace wait_test
{

hamon::condition_variable_any cv;

typedef hamon::timed_mutex L0;
typedef hamon::unique_lock<L0> L1;

L0 m0;

int test1 = 0;
int test2 = 0;

void f()
{
	L1 lk(m0);
	EXPECT_TRUE(test2 == 0);
	test1 = 1;
	cv.notify_one();
	while (test2 == 0)
	{
		cv.wait(lk);
	}
	EXPECT_TRUE(test2 != 0);
}

GTEST_TEST(ConditionVariableAnyTest, WaitTest)
{
	L1 lk(m0);
	hamon::thread t(f);
	EXPECT_TRUE(test1 == 0);
	while (test1 == 0)
	{
		static_assert(hamon::is_same_v<decltype(cv.wait(lk)), void>, "");
		static_assert(!noexcept(cv.wait(lk)), "");
		cv.wait(lk);
	}
	EXPECT_TRUE(test1 != 0);
	test2 = 1;
	lk.unlock();
	cv.notify_one();
	t.join();
}

}	// namespace wait_test

}	// namespace hamon_condition_variable_any_test
