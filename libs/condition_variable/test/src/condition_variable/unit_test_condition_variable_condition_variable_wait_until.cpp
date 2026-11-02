/**
 *	@file	unit_test_condition_variable_condition_variable_wait_until.cpp
 *
 *	@brief	wait_until(lock, abs_time) のテスト
 *
 *	template<class Clock, class Duration>
 *	cv_status wait_until(unique_lock<mutex>& lock,
 *		chrono::time_point<Clock, Duration> abs_time);
 */

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_test
{

namespace wait_until_test
{

namespace chrono = hamon::chrono;

struct TestClock
{
	typedef chrono::milliseconds duration;
	typedef duration::rep rep;
	typedef duration::period period;
	typedef chrono::time_point<TestClock> time_point;
	static const bool is_steady = true;

	static time_point now()
	{
		return time_point(chrono::duration_cast<duration>(chrono::steady_clock::now().time_since_epoch()));
	}
};

template <typename Clock>
void test()
{
	// Test unblocking via a call to notify_one() in another thread.
	//
	// To test this, we set a very long timeout in wait_until() and we wait
	// again in case we get awoken spuriously. Note that it can actually
	// happen that we get awoken spuriously and fail to recognize it
	// (making this test useless), but the likelihood should be small.
	{
		hamon::atomic<bool> ready(false);
		hamon::atomic<bool> likely_spurious(true);
		auto timeout = Clock::now() + chrono::seconds(3600);
		hamon::condition_variable cv;
		hamon::mutex mutex;

		hamon::thread t1([&] {
			hamon::unique_lock<hamon::mutex> lock(mutex);
			ready = true;
			do
			{
				static_assert(hamon::is_same_v<decltype(cv.wait_until(lock, timeout)), hamon::cv_status>, "");
				static_assert(!noexcept(cv.wait_until(lock, timeout)), "");
				hamon::cv_status result = cv.wait_until(lock, timeout);
				EXPECT_TRUE(result == hamon::cv_status::no_timeout);
			}
			while (likely_spurious);

			// This can technically fail if we have many spurious awakenings, but in practice the
			// tolerance is so high that it shouldn't be a problem.
			EXPECT_TRUE(Clock::now() < timeout);
		});

		hamon::thread t2([&] {
			while (!ready)
			{
				// spin
			}

			// Acquire the same mutex as t1. This blocks the condition variable inside its wait call
			// so we can notify it while it is waiting.
			hamon::unique_lock<hamon::mutex> lock(mutex);
			cv.notify_one();
			likely_spurious = false;
			lock.unlock();
		});

		t2.join();
		t1.join();
	}

	// Test unblocking via a timeout.
	//
	// To test this, we create a thread that waits on a condition variable
	// with a certain timeout, and we never awaken it. To guard against
	// spurious wakeups, we wait again whenever we are awoken for a reason
	// other than a timeout.
	{
		auto timeout = Clock::now() + chrono::milliseconds(25);	// 250
		hamon::condition_variable cv;
		hamon::mutex mutex;

		hamon::thread t1([&] {
			hamon::unique_lock<hamon::mutex> lock(mutex);
			hamon::cv_status result;
			do
			{
				result = cv.wait_until(lock, timeout);
				if (result == hamon::cv_status::timeout)
				{
					EXPECT_TRUE(Clock::now() >= timeout);
				}
			}
			while (result != hamon::cv_status::timeout);
		});

		t1.join();
	}
}

GTEST_TEST(ConditionVariableTest, WaitUntilTest)
{
	hamon::thread tests[] =
	{
		hamon::thread([] {test<TestClock>();}),
		hamon::thread([] {test<chrono::steady_clock>();}),
	};
	for (auto& t : tests)
	{
		t.join();
	}
}

}	// namespace wait_until_test

}	// namespace hamon_condition_variable_test
