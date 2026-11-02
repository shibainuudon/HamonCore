/**
 *	@file	unit_test_condition_variable_condition_variable_any_wait_pred.cpp
 *
 *	@brief	wait(lock, pred) のテスト
 *
 *	template<class Lock, class Predicate>
 *	void wait(Lock& lock, Predicate pred);
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

namespace wait_pred_test
{

template <typename Mutex>
struct MyLock : hamon::unique_lock<Mutex>
{
	using hamon::unique_lock<Mutex>::unique_lock;
};

template <typename Lock>
void test()
{
	using Mutex = typename Lock::mutex_type;

	// Test unblocking via a call to notify_one() in another thread.
	//
	// To test this, we try to minimize the likelihood that we got awoken by a
	// spurious wakeup by updating the likely_spurious flag only immediately
	// before we perform the notification.
	{
		hamon::atomic<bool> ready(false);
		hamon::atomic<bool> likely_spurious(true);
		hamon::condition_variable_any cv;
		Mutex mutex;

		hamon::thread t1([&] {
			Lock lock(mutex);
			ready = true;
			auto pred = [&] { return !likely_spurious; };
			static_assert(hamon::is_same_v<decltype(cv.wait(lock, pred)), void>, "");
			static_assert(!noexcept(cv.wait(lock, pred)), "");
			cv.wait(lock, pred);
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

	// Test unblocking via a spurious wakeup.
	//
	// To test this, we basically never wake up the condition variable. This way, we
	// are hoping to get out of the wait via a spurious wakeup.
	//
	// However, since spurious wakeups are not required to even happen, this test is
	// only trying to trigger that code path, but not actually asserting that it is
	// taken. In particular, we do need to eventually ensure we get out of the wait
	// by standard means, so we actually wake up the thread at the end.
	{
		hamon::atomic<bool> ready(false);
		hamon::atomic<bool> awoken(false);
		hamon::condition_variable_any cv;
		Mutex mutex;

		hamon::thread t1([&] {
			Lock lock(mutex);
			ready = true;
			cv.wait(lock, [&] { return true; });
			awoken = true;
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

			// Whatever happened, actually awaken the condition variable to ensure the test finishes.
			cv.notify_one();
		});

		t2.join();
		t1.join();
	}
}

GTEST_TEST(ConditionVariableAnyTest, WaitPredTest)
{
	hamon::thread tests[] =
	{
		hamon::thread([] {test<hamon::unique_lock<hamon::mutex>>();}),
		hamon::thread([] {test<hamon::unique_lock<hamon::timed_mutex>>();}),
		hamon::thread([] {test<MyLock<hamon::mutex>>();}),
		hamon::thread([] {test<MyLock<hamon::timed_mutex>>();}),
	};
	for (auto& t : tests)
	{
		t.join();
	}
}

}	// namespace wait_pred_test

}	// namespace hamon_condition_variable_any_test
