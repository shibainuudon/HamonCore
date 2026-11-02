/**
 *	@file	unit_test_condition_variable_condition_variable_any_wait_token_pred.cpp
 *
 *	@brief	wait(lock, stoken, pred) のテスト
 *
 *	template<class Lock, class Predicate>
 *	bool wait(Lock& lock, stop_token stoken, Predicate pred);
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/mutex.hpp>
#include <hamon/shared_mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_any_test
{

namespace wait_token_pred_test
{

template <typename Mutex, typename Lock>
void test()
{
	// stop_requested before hand
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };
		ss.request_stop();

		auto f = []() { return false; };
		static_assert(hamon::is_same_v<decltype(cv.wait(lock, ss.get_token(), f)), bool>, "");
		static_assert(!noexcept(cv.wait(lock, ss.get_token(), f)), "");

		// [Note 1: The returned value indicates whether the predicate evaluated to true regardless of whether there was a stop request.]
		auto r1 = cv.wait(lock, ss.get_token(), []() { return false; });
		EXPECT_TRUE(!r1);

		auto r2 = cv.wait(lock, ss.get_token(), []() { return true; });
		EXPECT_TRUE(r2);

		// Postconditions: lock is locked by the calling thread.
		EXPECT_TRUE(lock.owns_lock());
	}

	// no stop request
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };
		auto r1 = cv.wait(lock, ss.get_token(), []() { return true; });
		EXPECT_TRUE(r1);

		bool flag = false;
		auto thread = hamon::thread([&]() {
			hamon::this_thread::sleep_for(hamon::chrono::milliseconds(2));
			hamon::unique_lock<Mutex> lock2{ mutex };
			flag = true;
			cv.notify_all();
		});

		auto r2 = cv.wait(lock, ss.get_token(), [&]() { return flag; });
		EXPECT_TRUE(flag);
		EXPECT_TRUE(r2);
		thread.join();

		EXPECT_TRUE(lock.owns_lock());
	}

	// stop request comes while waiting
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };

		hamon::atomic_bool start{false};
		hamon::atomic_bool done{false};
		auto thread = hamon::thread([&]() {
			start.wait(false);
			ss.request_stop();

			while (!done)
			{
				cv.notify_all();
				hamon::this_thread::sleep_for(hamon::chrono::milliseconds(2));
			}
		});

		auto r = cv.wait(lock, ss.get_token(), [&]() {
			start.store(true);
			start.notify_all();
			return false;
		});
		EXPECT_TRUE(!r);
		done = true;
		thread.join();

		EXPECT_TRUE(lock.owns_lock());
	}

	// #76807 Hangs in hamon::condition_variable_any when used with hamon::stop_token
	{
		class MyThread
		{
		public:
			MyThread()
			{
				thread_ = hamon::jthread([this](hamon::stop_token st) {
					while (!st.stop_requested())
					{
						hamon::unique_lock<hamon::mutex> lock{ m_ };
						cv_.wait(lock, st, [] { return false; });
					}
				});
			}

		private:
			hamon::mutex m_;
			hamon::condition_variable_any cv_;
			hamon::jthread thread_;
		};

		MyThread my_thread;
		(void)my_thread;
	}

	// request_stop potentially in-between check and wait
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };

		hamon::atomic_bool pred_started{false};
		hamon::atomic_bool request_stop_called{false};
		auto thread = hamon::thread([&]() {
			pred_started.wait(false);
			ss.request_stop();
			request_stop_called.store(true);
			request_stop_called.notify_all();
		});

		auto r = cv.wait(lock, ss.get_token(), [&]() {
			pred_started.store(true);
			pred_started.notify_all();
			request_stop_called.wait(false);
			return false;
		});
		EXPECT_TRUE(!r);
		thread.join();

		EXPECT_TRUE(lock.owns_lock());
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	// Throws: Any exception thrown by pred.
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };

		try
		{
			cv.wait(lock, ss.get_token(), []() -> bool { throw 5; });
			EXPECT_TRUE(false);
		}
		catch (int i)
		{
			EXPECT_TRUE(i == 5);
		}
	}
#endif
}

GTEST_TEST(ConditionVariableAnyTest, WaitTokenPredTest)
{
	hamon::thread tests[] =
	{
		hamon::thread([] {test<hamon::mutex, hamon::unique_lock<hamon::mutex>>();}),
		hamon::thread([] {test<hamon::shared_mutex, hamon::shared_lock<hamon::shared_mutex>>();}),
	};
	for (auto& t : tests)
	{
		t.join();
	}
}

}	// namespace wait_token_pred_test

}	// namespace hamon_condition_variable_any_test
