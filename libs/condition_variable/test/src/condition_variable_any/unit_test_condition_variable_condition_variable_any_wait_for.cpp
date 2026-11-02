/**
 *	@file	unit_test_condition_variable_condition_variable_any_wait_for.cpp
 *
 *	@brief	wait_for(lock, rel_time) のテスト
 *
 *	template<class Lock, class Rep, class Period>
 *	cv_status wait_for(Lock& lock, chrono::duration<Rep, Period> rel_time);
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_any_test
{

namespace wait_for_test
{

namespace chrono = hamon::chrono;

template <typename Mutex>
struct MyLock : hamon::unique_lock<Mutex>
{
	using hamon::unique_lock<Mutex>::unique_lock;
};

template <typename Function>
chrono::microseconds measure(Function f)
{
	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
	f();
	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::microseconds>(end - start);
}

template <typename Lock, typename Mutex = typename Lock::mutex_type>
void test1()
{
	// Test unblocking via a call to notify_one() in another thread.
	//
	// To test this, we set a very long timeout in wait_for() and we wait
	// again in case we get awoken spuriously. Note that it can actually
	// happen that we get awoken spuriously and fail to recognize it
	// (making this test useless), but the likelihood should be small.
	{
		hamon::atomic<bool> ready(false);
		hamon::atomic<bool> likely_spurious(true);
		auto timeout = chrono::seconds(3600);
		hamon::condition_variable_any cv;
		Mutex mutex;

		hamon::thread t1([&] {
			Lock lock(mutex);
			auto elapsed = measure([&] {
				ready = true;
				do
				{
					static_assert(hamon::is_same_v<decltype(cv.wait_for(lock, timeout)), hamon::cv_status>, "");
					static_assert(!noexcept(cv.wait_for(lock, timeout)), "");
					hamon::cv_status result = cv.wait_for(lock, timeout);
					EXPECT_TRUE(result == hamon::cv_status::no_timeout);
				}
				while (likely_spurious);
			});

			// This can technically fail if we have many spurious awakenings, but in practice the
			// tolerance is so high that it shouldn't be a problem.
			EXPECT_TRUE(elapsed < timeout);
		});

		hamon::thread t2([&] {
			while (!ready)
			{
				// spin
			}

			// Acquire the same mutex as t1. This blocks the condition variable inside its wait call
			// so we can notify it while it is waiting.
			Lock lock(mutex);
			cv.notify_one();
			likely_spurious = false;
			lock.unlock();
		});

		t2.join();
		t1.join();
	}
}

template <typename Lock, typename Mutex = typename Lock::mutex_type>
void test2()
{
	// Test unblocking via a timeout.
	//
	// To test this, we create a thread that waits on a condition variable
	// with a certain timeout, and we never awaken it. To guard against
	// spurious wakeups, we wait again whenever we are awoken for a reason
	// other than a timeout.
	{
		auto timeout = chrono::milliseconds(25);	// 250
		hamon::condition_variable_any cv;
		Mutex mutex;

		hamon::thread t1([&] {
			Lock lock(mutex);
			hamon::cv_status result;
			do
			{
				auto elapsed = measure([&] { result = cv.wait_for(lock, timeout); });
				if (result == hamon::cv_status::timeout)
				{
					EXPECT_TRUE(elapsed >= timeout);
				}
			}
			while (result != hamon::cv_status::timeout);
		});

		t1.join();
	}
}

template <typename Lock, typename Mutex = typename Lock::mutex_type>
void test3()
{
	// Regression test for LWG 3504: wait_for() with a floating-point
	{
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock(mutex);

		using float_sec = chrono::duration<float>;
		const float_sec total{ 0.025f };		// 0.25f

		auto start = chrono::steady_clock::now();
		hamon::cv_status status = hamon::cv_status::no_timeout;

		while (status == hamon::cv_status::no_timeout)
		{
			auto left = total - chrono::duration_cast<float_sec>(chrono::steady_clock::now() - start);
			if (left <= float_sec::zero())
			{
				break;
			}
			status = cv.wait_for(lock, left);
		}

		auto elapsed = chrono::steady_clock::now() - start;
		EXPECT_TRUE(elapsed >= chrono::milliseconds(25));	// 200
		//EXPECT_TRUE(elapsed < chrono::milliseconds(60));	// 600
	}
}

GTEST_TEST(ConditionVariableAnyTest, WaitForTest)
{
	hamon::thread tests[] =
	{
		hamon::thread([] {test1<hamon::unique_lock<hamon::mutex>>();}),
		hamon::thread([] {test1<hamon::unique_lock<hamon::timed_mutex>>();}),
		hamon::thread([] {test1<MyLock<hamon::mutex>>();}),
		hamon::thread([] {test1<MyLock<hamon::timed_mutex>>();}),

		hamon::thread([] {test2<hamon::unique_lock<hamon::mutex>>();}),
		hamon::thread([] {test2<hamon::unique_lock<hamon::timed_mutex>>();}),
		hamon::thread([] {test2<MyLock<hamon::mutex>>();}),
		hamon::thread([] {test2<MyLock<hamon::timed_mutex>>();}),

		hamon::thread([] {test3<hamon::unique_lock<hamon::mutex>>();}),
		hamon::thread([] {test3<hamon::unique_lock<hamon::timed_mutex>>();}),
		hamon::thread([] {test3<MyLock<hamon::mutex>>();}),
		hamon::thread([] {test3<MyLock<hamon::timed_mutex>>();}),
	};
	for (auto& t : tests)
	{
		t.join();
	}
}

}	// namespace wait_for_test

}	// namespace hamon_condition_variable_any_test
