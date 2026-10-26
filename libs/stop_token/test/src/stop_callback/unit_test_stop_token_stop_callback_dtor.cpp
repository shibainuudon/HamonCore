/**
 *	@file	unit_test_stop_token_stop_callback_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~stop_callback();
 */

#include <hamon/stop_token/stop_callback.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <hamon/memory/make_unique.hpp>
#include <hamon/optional.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

#include <functional>	// std::function

namespace hamon_stop_callback_test
{

namespace dtor_test
{

struct CallbackHolder;

struct DeleteHolder
{
	CallbackHolder& holder_;
	void operator()() const;
};

struct CallbackHolder
{
	hamon::unique_ptr<hamon::stop_callback<DeleteHolder>> callback_;
};

inline void DeleteHolder::operator()() const
{
	holder_.callback_.reset();
}

GTEST_TEST(StopCallbackTest, DtorTest)
{
	// Unregisters the callback from the owned stop state, if any
	{
		hamon::stop_source ss;
		bool called = false;

		{
			auto f = [&] { called = true; };
			hamon::stop_callback<decltype(f)> sc(ss.get_token(), f);
		}
		ss.request_stop();
		EXPECT_FALSE(called);
	}

	// The destructor does not block waiting for the execution of another
	// callback registered by an associated stop_callback.
	{
		hamon::stop_source ss;

		hamon::atomic<int> startedIndex{0};
		hamon::atomic<bool> callbackFinish{false};

		hamon::optional<hamon::stop_callback<std::function<void()>>> sc1(hamon::in_place, ss.get_token(), [&] {
			startedIndex = 1;
			startedIndex.notify_all();
			callbackFinish.wait(false);
		});

		hamon::optional<hamon::stop_callback<std::function<void()>>> sc2(hamon::in_place, ss.get_token(), [&] {
			startedIndex = 2;
			startedIndex.notify_all();
			callbackFinish.wait(false);
		});

		auto thread = hamon::thread([&] { ss.request_stop(); });

		startedIndex.wait(0);

		// now one of the callback has started but not finished.
		if (startedIndex == 1)
		{
			sc2.reset();   // destructor should not block
		}
		else if (startedIndex == 2)
		{
			sc1.reset();   // destructor should not block
		}
		else
		{
			EXPECT_TRUE(false); // something is wrong
		}

		callbackFinish = true;
		callbackFinish.notify_all();
		thread.join();
	}

	// If callback is concurrently executing on another thread, then the
	// return from the invocation of callback strongly happens before ([intro.races])
	// callback is destroyed.
	{
		struct Callback
		{
			hamon::atomic<bool>& started_;
			hamon::atomic<bool>& waitDone_;
			hamon::atomic<bool>& finished_;
			bool moved = false;

			Callback(hamon::atomic<bool>& started, hamon::atomic<bool>& waitDone, hamon::atomic<bool>& finished)
				: started_(started), waitDone_(waitDone), finished_(finished)
			{
			}
			Callback(Callback&& other) : started_(other.started_), waitDone_(other.waitDone_), finished_(other.finished_)
			{
				other.moved = true;
			}

			void operator()() const
			{
				struct ScopedGuard
				{
					hamon::atomic<bool>& g_finished_;
					~ScopedGuard() { g_finished_.store(true, hamon::memory_order_relaxed); }
				};

				started_ = true;
				started_.notify_all();
				waitDone_.wait(false);
				ScopedGuard g{ finished_ };
			}

			~Callback()
			{
				if (!moved)
				{
					// destructor has to be called after operator() returns
					EXPECT_TRUE(finished_.load(hamon::memory_order_relaxed));
				}
			}
		};

		hamon::stop_source ss;

		hamon::atomic<bool> started {false};
		hamon::atomic<bool> waitDone{false};
		hamon::atomic<bool> finished{false};

		hamon::optional<hamon::stop_callback<Callback>> sc{
			hamon::in_place, ss.get_token(), Callback{started, waitDone, finished} };

		auto thread1 = hamon::thread([&] { ss.request_stop(); });
		started.wait(false);

		auto thread2 = hamon::thread([&] {
			using namespace hamon::chrono_literals;
			hamon::this_thread::sleep_for(1_ms);
			waitDone = true;
			waitDone.notify_all();
		});

		sc.reset(); // destructor should block until operator() returns, i.e. waitDone to be true

		thread1.join();
		thread2.join();
	}

	// If callback is executing on the current thread, then the destructor does not block ([defns.block])
	// waiting for the return from the invocation of callback.
	{
		hamon::stop_source ss;

		CallbackHolder holder;
		holder.callback_ = hamon::make_unique<hamon::stop_callback<DeleteHolder>>(ss.get_token(), DeleteHolder{ holder });

		EXPECT_TRUE(holder.callback_ != nullptr);

		ss.request_stop(); // the callbacks deletes itself. if the destructor blocks, it would be deadlock
		EXPECT_TRUE(holder.callback_ == nullptr);
	}
}

}	// namespace dtor_test

}	// namespace hamon_stop_callback_test
