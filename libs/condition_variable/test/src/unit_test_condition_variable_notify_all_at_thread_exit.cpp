/**
 *	@file	unit_test_condition_variable_notify_all_at_thread_exit.cpp
 *
 *	@brief	notify_all_at_thread_exit のテスト
 *
 *	void notify_all_at_thread_exit(condition_variable& cond, unique_lock<mutex> lk);
 */

#include <hamon/condition_variable/notify_all_at_thread_exit.hpp>
#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/chrono.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_test
{

namespace notify_all_at_thread_exit_test
{

#if 0	// TODO
hamon::condition_variable cv;
hamon::mutex mut;

typedef hamon::chrono::milliseconds ms;
typedef hamon::chrono::high_resolution_clock Clock;

void func()
{
	hamon::unique_lock<hamon::mutex> lk(mut);
	hamon::notify_all_at_thread_exit(cv, hamon::move(lk));
	hamon::this_thread::sleep_for(ms(300));
}

GTEST_TEST(ConditionVariableTest, NotifyAllAtThreadExitTest)
{
	hamon::unique_lock<hamon::mutex> lk(mut);
	hamon::thread t(func);
	Clock::time_point t0 = Clock::now();
	cv.wait(lk);
	Clock::time_point t1 = Clock::now();
	EXPECT_TRUE(t1 - t0 > ms(250));
	t.join();
}
#endif

}	// namespace notify_all_at_thread_exit_test

}	// namespace hamon_condition_variable_test
