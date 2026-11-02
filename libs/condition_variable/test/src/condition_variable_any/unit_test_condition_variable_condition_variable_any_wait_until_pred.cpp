/**
 *	@file	unit_test_condition_variable_condition_variable_any_wait_until_pred.cpp
 *
 *	@brief	wait_until(lock, abs_time, pred) のテスト
 *
 *	template<class Lock, class Clock, class Duration, class Predicate>
 *	bool wait_until(Lock& lock, chrono::time_point<Clock, Duration> abs_time, Predicate pred);
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

namespace wait_until_pred_test
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
		using namespace chrono;
		return time_point(duration_cast<duration>(steady_clock::now().time_since_epoch()));
	}
};

template <typename Mutex>
struct MyLock : hamon::unique_lock<Mutex>
{
	using hamon::unique_lock<Mutex>::unique_lock;
};

template <typename Lock, typename Clock, typename Mutex = typename Lock::mutex_type>
void test1()
{
	// Test unblocking via a call to notify_one() in another thread.
	//
	// To test this, we set a very long timeout in wait_until() and we try to minimize
	// the likelihood that we got awoken by a spurious wakeup by updating the
	// likely_spurious flag only immediately before we perform the notification.
	{
		hamon::atomic<bool> ready(false);
		hamon::atomic<bool> likely_spurious(true);
		auto timeout = Clock::now() + chrono::seconds(3600);
		hamon::condition_variable_any cv;
		Mutex mutex;

		hamon::thread t1([&] {
			Lock lock(mutex);
			ready = true;
			auto pred = [&] { return !likely_spurious; };
			static_assert(hamon::is_same_v<decltype(cv.wait_until(lock, timeout, pred)), bool>, "");
			static_assert(!noexcept(cv.wait_until(lock, timeout, pred)), "");
			bool result = cv.wait_until(lock, timeout, pred);
			EXPECT_TRUE(result); // return value should be true since we didn't time out
			EXPECT_TRUE(Clock::now() < timeout);
		});

		hamon::thread t2([&] {
			while (!ready)
			{
				// spin
			}

			// Acquire the same mutex as t1. This ensures that the condition variable has started
			// waiting (and hence released that mutex).
			Lock lock(mutex);

			likely_spurious = false;
			lock.unlock();
			cv.notify_one();
		});

		t2.join();
		t1.join();
	}
}

template <typename Lock, typename Clock, typename Mutex = typename Lock::mutex_type>
void test2()
{
	// Test unblocking via a timeout.
	//
	// To test this, we create a thread that waits on a condition variable with a certain
	// timeout, and we never awaken it. The "stop waiting" predicate always returns false,
	// which means that we can't get out of the wait via a spurious wakeup.
	{
		auto timeout = Clock::now() + chrono::milliseconds(25);	// 250
		hamon::condition_variable_any cv;
		Mutex mutex;

		hamon::thread t1([&] {
			Lock lock(mutex);
			bool result = cv.wait_until(lock, timeout, [] { return false; }); // never stop waiting (until timeout)
			EXPECT_TRUE(!result); // return value should be false since the predicate returns false after the timeout
			EXPECT_TRUE(Clock::now() >= timeout);
		});

		t1.join();
	}
}

template <typename Lock, typename Clock, typename Mutex = typename Lock::mutex_type>
void test3()
{
	// Test unblocking via a spurious wakeup.
	//
	// To test this, we set a fairly long timeout in wait_until() and we basically never
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
		auto timeout = Clock::now() + chrono::seconds(3600);
		hamon::condition_variable_any cv;
		Mutex mutex;

		hamon::thread t1([&] {
			Lock lock(mutex);
			ready = true;
			bool result = cv.wait_until(lock, timeout, [&] { return true; });
			awoken = true;
			EXPECT_TRUE(result);                 // return value should be true since we didn't time out
			EXPECT_TRUE(Clock::now() < timeout); // can technically fail if t2 never executes and we timeout, but very unlikely
		});

		hamon::thread t2([&] {
			while (!ready)
			{
				// spin
			}

			// Acquire the same mutex as t1. This ensures that the condition variable has started
			// waiting (and hence released that mutex).
			Lock lock(mutex);
			lock.unlock();

			// Give some time for t1 to be awoken spuriously so that code path is used.
			hamon::this_thread::sleep_for(hamon::chrono::milliseconds(25));	// seconds(1)

			// We would want to assert that the thread has been awoken after this time,
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

GTEST_TEST(ConditionVariableAnyTest, WaitUntilPredTest)
{
	// Run on multiple threads to speed up the test, and because it ought to work anyways.
	hamon::thread tests[] =
	{
		hamon::thread([] {test1<hamon::unique_lock<hamon::mutex>, TestClock>();}),
		hamon::thread([] {test1<hamon::unique_lock<hamon::mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test1<hamon::unique_lock<hamon::timed_mutex>, TestClock>();}),
		hamon::thread([] {test1<hamon::unique_lock<hamon::timed_mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test1<MyLock<hamon::mutex>, TestClock>();}),
		hamon::thread([] {test1<MyLock<hamon::mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test1<MyLock<hamon::timed_mutex>, TestClock>();}),
		hamon::thread([] {test1<MyLock<hamon::timed_mutex>, chrono::steady_clock>();}),

		hamon::thread([] {test2<hamon::unique_lock<hamon::mutex>, TestClock>();}),
		hamon::thread([] {test2<hamon::unique_lock<hamon::mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test2<hamon::unique_lock<hamon::timed_mutex>, TestClock>();}),
		hamon::thread([] {test2<hamon::unique_lock<hamon::timed_mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test2<MyLock<hamon::mutex>, TestClock>();}),
		hamon::thread([] {test2<MyLock<hamon::mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test2<MyLock<hamon::timed_mutex>, TestClock>();}),
		hamon::thread([] {test2<MyLock<hamon::timed_mutex>, chrono::steady_clock>();}),

		hamon::thread([] {test3<hamon::unique_lock<hamon::mutex>, TestClock>();}),
		hamon::thread([] {test3<hamon::unique_lock<hamon::mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test3<hamon::unique_lock<hamon::timed_mutex>, TestClock>();}),
		hamon::thread([] {test3<hamon::unique_lock<hamon::timed_mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test3<MyLock<hamon::mutex>, TestClock>();}),
		hamon::thread([] {test3<MyLock<hamon::mutex>, chrono::steady_clock>();}),
		hamon::thread([] {test3<MyLock<hamon::timed_mutex>, TestClock>();}),
		hamon::thread([] {test3<MyLock<hamon::timed_mutex>, chrono::steady_clock>();}),
	};
	for (hamon::thread& t : tests)
	{
		t.join();
	}
}

}	// namespace wait_until_pred_test

}	// namespace hamon_condition_variable_any_test
