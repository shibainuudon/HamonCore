/**
 *	@file	unit_test_condition_variable_condition_variable_any_wait_for_token_pred.cpp
 *
 *	@brief	wait_for(lock, stoken, rel_time, pred) のテスト
 *
 *	template<class Lock, class Rep, class Period, class Predicate>
 *	bool wait_for(Lock& lock, stop_token stoken, chrono::duration<Rep, Period> rel_time, Predicate pred);
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/mutex.hpp>
#include <hamon/shared_mutex.hpp>
#include <hamon/stop_token.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_any_test
{

namespace wait_for_token_pred_test
{

namespace chrono = hamon::chrono;

struct ElapsedTimeCheck
{
	ElapsedTimeCheck(chrono::steady_clock::duration timeoutDuration)
		: timeout_(chrono::steady_clock::now() + timeoutDuration)
	{}

	ElapsedTimeCheck(ElapsedTimeCheck&&) = delete;
	ElapsedTimeCheck& operator=(ElapsedTimeCheck&&) = delete;

	~ElapsedTimeCheck() { EXPECT_TRUE(chrono::steady_clock::now() < timeout_); }

	chrono::time_point<chrono::steady_clock> timeout_;
};

template <typename Mutex, typename Lock>
void test()
{
	using namespace hamon::chrono_literals;

	// stop_requested before hand
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };
		ss.request_stop();

		ElapsedTimeCheck check(1_min);

		auto f = []() { return false; };
		static_assert(hamon::is_same_v<decltype(cv.wait_for(lock, ss.get_token(), -1_h, f)), bool>, "");
		static_assert(!noexcept(cv.wait_for(lock, ss.get_token(), -1_h, f)), "");

		// [Note 4: The returned value indicates whether the predicate evaluated to true
		// regardless of whether the timeout was triggered or a stop request was made.]
		auto r1 = cv.wait_for(lock, ss.get_token(), -1_h, []() { return false; });
		EXPECT_TRUE(!r1);

		auto r2 = cv.wait_for(lock, ss.get_token(), 1_h, []() { return false; });
		EXPECT_TRUE(!r2);

		auto r3 = cv.wait_for(lock, ss.get_token(), -1_h, []() { return true; });
		EXPECT_TRUE(r3);

		auto r4 = cv.wait_for(lock, ss.get_token(), 1_h, []() { return true; });
		EXPECT_TRUE(r4);

		// Postconditions: lock is locked by the calling thread.
		EXPECT_TRUE(lock.owns_lock());
	}

	// no stop request, pred was true
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };

		ElapsedTimeCheck check(1_min);

		auto r1 = cv.wait_for(lock, ss.get_token(), -1_h, []() { return true; });
		EXPECT_TRUE(r1);

		auto r2 = cv.wait_for(lock, ss.get_token(), 1_h, []() { return true; });
		EXPECT_TRUE(r2);
	}

	// no stop request, pred was false, abs_time was in the past
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };

		ElapsedTimeCheck check(1_min);

		auto r1 = cv.wait_for(lock, ss.get_token(), -1_h, []() { return false; });
		EXPECT_TRUE(!r1);
	}

	// no stop request, pred was false until timeout
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };

		auto old_time = chrono::steady_clock::now();

		auto r1 = cv.wait_for(lock, ss.get_token(), 2_ms, [&]() { return false; });

		EXPECT_TRUE((chrono::steady_clock::now() - old_time) >= 2_ms);
		EXPECT_TRUE(!r1);
	}

	// no stop request, pred was false, changed to true before timeout
	{
		hamon::stop_source ss;
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock{ mutex };

		bool flag = false;
		auto thread = hamon::thread([&]() {
			hamon::this_thread::sleep_for(hamon::chrono::milliseconds(2));
			hamon::unique_lock<Mutex> lock2{ mutex };
			flag = true;
			cv.notify_all();
		});

		ElapsedTimeCheck check(10_min);

		auto r1 = cv.wait_for(lock, ss.get_token(), 1_h, [&]() { return flag; });
		EXPECT_TRUE(flag);
		EXPECT_TRUE(r1);

		thread.join();
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

		ElapsedTimeCheck check(10_min);

		auto r = cv.wait_for(lock, ss.get_token(), 1_h, [&]() {
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
						cv_.wait_for(lock, st, 1_h, [] { return false; });
					}
				});
			}

		private:
			hamon::mutex m_;
			hamon::condition_variable_any cv_;
			hamon::jthread thread_;
		};

		ElapsedTimeCheck check(10_min);

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

		ElapsedTimeCheck check(10_min);

		auto r = cv.wait_for(lock, ss.get_token(), 1_h, [&]() {
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
			ElapsedTimeCheck check(10_min);
			cv.wait_for(lock, ss.get_token(), 1_h, []() -> bool { throw 5; });
			EXPECT_TRUE(false);
		}
		catch (int i)
		{
			EXPECT_TRUE(i == 5);
		}
	}
#endif

	// Regression test for LWG 3504: wait_for() with a floating-point
	{
		hamon::condition_variable_any cv;
		Mutex mutex;
		Lock lock(mutex);
		hamon::stop_source ss;

		auto start = chrono::steady_clock::now();
		bool result = cv.wait_for(lock, ss.get_token(), chrono::duration<float>(0.025f), [] { return false; });	// 0.25f
		auto elapsed = chrono::steady_clock::now() - start;

		EXPECT_TRUE(result == false);
		EXPECT_TRUE(elapsed >= chrono::milliseconds(25));	// 200
		//EXPECT_TRUE(elapsed < chrono::milliseconds(60));	// 600
	}
}

GTEST_TEST(ConditionVariableAnyTest, WaitForTokenPredTest)
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

}	// namespace wait_for_token_pred_test

}	// namespace hamon_condition_variable_any_test
