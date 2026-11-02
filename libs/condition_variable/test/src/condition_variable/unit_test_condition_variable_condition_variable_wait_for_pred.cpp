/**
 *	@file	unit_test_condition_variable_condition_variable_wait_for_pred.cpp
 *
 *	@brief	wait_for(lock, rel_time, pred) のテスト
 *
 *	template<class Rep, class Period, class Predicate>
 *	bool wait_for(unique_lock<mutex>& lock,
 *		chrono::duration<Rep, Period> rel_time,
 *		Predicate pred);
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

namespace wait_for_pred_test
{

namespace chrono = hamon::chrono;

template <typename Function>
chrono::microseconds measure(Function f)
{
	auto start = chrono::high_resolution_clock::now();
	f();
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::microseconds>(end - start);
}

void test1()
{
	// Test unblocking via a call to notify_one() in another thread.
	//
	// To test this, we set a very long timeout in wait_for() and we try to minimize
	// the likelihood that we got awoken by a spurious wakeup by updating the
	// likely_spurious flag only immediately before we perform the notification.
	{
		hamon::atomic<bool> ready(false);
		hamon::atomic<bool> likely_spurious(true);
		auto timeout = chrono::seconds(3600);
		hamon::condition_variable cv;
		hamon::mutex mutex;

		hamon::thread t1([&] {
			hamon::unique_lock<hamon::mutex> lock(mutex);
			auto elapsed = measure([&] {
				ready = true;
				auto pred = [&] { return !likely_spurious; };
				static_assert(hamon::is_same_v<decltype(cv.wait_for(lock, timeout, pred)), bool>, "");
				static_assert(!noexcept(cv.wait_for(lock, timeout, pred)), "");
				bool result = cv.wait_for(lock, timeout, pred);
				EXPECT_TRUE(result); // return value should be true since we didn't time out
			});
			EXPECT_TRUE(elapsed < timeout);
		});

		hamon::thread t2([&] {
			while (!ready)
			{
				// spin
			}

			// Acquire the same mutex as t1. This ensures that the condition variable has started
			// waiting (and hence released that mutex).
			hamon::unique_lock<hamon::mutex> lock(mutex);

			likely_spurious = false;
			lock.unlock();
			cv.notify_one();
		});

		t2.join();
		t1.join();
	}
}

void test2()
{
	// Test unblocking via a timeout.
	//
	// To test this, we create a thread that waits on a condition variable with a certain
	// timeout, and we never awaken it. The "stop waiting" predicate always returns false,
	// which means that we can't get out of the wait via a spurious wakeup.
	{
		auto timeout = chrono::milliseconds(25);	// 250
		hamon::condition_variable cv;
		hamon::mutex mutex;

		hamon::thread t1([&] {
			hamon::unique_lock<hamon::mutex> lock(mutex);
			auto elapsed = measure([&] {
				bool result = cv.wait_for(lock, timeout, [] { return false; }); // never stop waiting (until timeout)
				EXPECT_TRUE(!result); // return value should be false since the predicate returns false after the timeout
			});
			EXPECT_TRUE(elapsed >= timeout);
		});

		t1.join();
	}
}

void test3()
{
	// Test unblocking via a spurious wakeup.
	//
	// To test this, we set a fairly long timeout in wait_for() and we basically never
	// wake up the condition variable. This way, we are hoping to get out of the wait
	// via a spurious wakeup.
	//
	// However, since spurious wakeups are not required to even happen, this test is
	// only trying to trigger that code path, but not actually asserting that it is
	// taken. In particular, we do need to eventually ensure we get out of the wait
	// by standard means, so we actually wake up the thread at the end.
	{
		hamon::atomic<bool> ready(false);
		hamon::atomic<bool> awoken(false);
		auto timeout = chrono::seconds(3600);
		hamon::condition_variable cv;
		hamon::mutex mutex;

		hamon::thread t1([&] {
			hamon::unique_lock<hamon::mutex> lock(mutex);
			auto elapsed = measure([&] {
				ready = true;
				bool result = cv.wait_for(lock, timeout, [&] { return true; });
				awoken = true;
				EXPECT_TRUE(result); // return value should be true since we didn't time out
			});
			EXPECT_TRUE(elapsed < timeout); // can technically fail if t2 never executes and we timeout, but very unlikely
		});

		hamon::thread t2([&] {
			while (!ready)
			{
				// spin
			}

			// Acquire the same mutex as t1. This ensures that the condition variable has started
			// waiting (and hence released that mutex).
			hamon::unique_lock<hamon::mutex> lock(mutex);
			lock.unlock();

			// Give some time for t1 to be awoken spuriously so that code path is used.
			hamon::this_thread::sleep_for(hamon::chrono::milliseconds(25));	// chrono::seconds(1)

			// We would want to EXPECT_TRUE that the thread has been awoken after this time,
			// however nothing guarantees us that it ever gets spuriously awoken, so
			// we can't really check anything. This is still left here as documentation.
			bool woke = awoken.load();
			EXPECT_TRUE(woke || !woke);

			// Whatever happened, actually awaken the condition variable to ensure the test
			// doesn't keep running until the timeout.
			cv.notify_one();
		});

		t2.join();
		t1.join();
	}
}

void test4()
{
	// Regression test for LWG 3504: wait_for() with a floating-point
	{
		hamon::condition_variable cv;
		hamon::mutex mutex;
		hamon::unique_lock<hamon::mutex> lock(mutex);

		auto start = chrono::steady_clock::now();
		bool result = cv.wait_for(lock, chrono::duration<float>(0.025f), [] { return false; });	// 0.25f
		auto elapsed = chrono::steady_clock::now() - start;

		EXPECT_TRUE(result == false);
		EXPECT_TRUE(elapsed >= chrono::milliseconds(25));	// 200
		//EXPECT_TRUE(elapsed < chrono::milliseconds(60));	// 600
	}
}

GTEST_TEST(ConditionVariableTest, WaitForPredTest)
{
	hamon::thread tests[] =
	{
		hamon::thread([] {test1();}),
		hamon::thread([] {test2();}),
		hamon::thread([] {test3();}),
		hamon::thread([] {test4();}),
	};
	for (auto& t : tests)
	{
		t.join();
	}
}

}	// namespace wait_for_pred_test

}	// namespace hamon_condition_variable_test
