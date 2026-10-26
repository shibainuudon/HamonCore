/**
 *	@file	unit_test_stop_token_stop_callback_ctor_rvalue.cpp
 *
 *	@brief	stop_token&& を引数に取るコンストラクタのテスト
 *
 *	template<class Initializer>
 *	explicit stop_callback(stop_token&& st, Initializer&& init)
 *	noexcept(is_nothrow_constructible_v<CallbackFn, Initializer>);
 */

#include <hamon/stop_token/stop_callback.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/atomic.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_callback_test
{

namespace ctor_rvalue_test
{

struct CallbackFunc
{
	CallbackFunc(int) {}
	CallbackFunc(float) noexcept {}
	void operator()() const {}
};

static_assert( hamon::is_constructible_v           <hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, int>, "");
static_assert(!hamon::is_nothrow_constructible_v   <hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, int>, "");
static_assert(!hamon::is_trivially_constructible_v <hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, int>, "");
static_assert(!hamon::is_implicitly_constructible_v<hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, int>, "");
static_assert( hamon::is_constructible_v           <hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, float>, "");
static_assert( hamon::is_nothrow_constructible_v   <hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, float>, "");
static_assert(!hamon::is_trivially_constructible_v <hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, float>, "");
static_assert(!hamon::is_implicitly_constructible_v<hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, float>, "");
static_assert(!hamon::is_constructible_v           <hamon::stop_callback<CallbackFunc>, hamon::stop_token&&, int*>, "");

GTEST_TEST(StopCallbackTest, CtorRValueTest)
{
	// was requested
	{
		hamon::stop_source ss;
		ss.request_stop();

		bool called = false;
		auto f = [&] { called = true; };
		hamon::stop_callback<decltype(f)> sc(ss.get_token(), f);
		EXPECT_TRUE(called);
	}

	// was not requested
	{
		hamon::stop_source ss;

		bool called = false;
		auto f = [&] { called = true; };
		hamon::stop_callback<decltype(f)> sc(ss.get_token(), f);
		EXPECT_FALSE(called);

		ss.request_stop();
		EXPECT_TRUE(called);
	}

	// token has no state
	{
		hamon::stop_token st;
		bool called = false;
		auto f = [&] { called = true; };
		hamon::stop_callback<decltype(f)> sc(hamon::move(st), f);
		EXPECT_FALSE(called);
	}

	// should not be called multiple times
	{
		hamon::stop_source ss;

		int calledTimes = 0;
		auto f = [&] { ++calledTimes; };
		hamon::stop_callback<decltype(f)> sc(ss.get_token(), f);

		hamon::vector<hamon::thread> threads;
		for (auto i = 0; i < 10; ++i)
		{
			threads.emplace_back(hamon::thread([&] { ss.request_stop(); }));
		}

		for (auto& thread : threads)
		{
			thread.join();
		}
		EXPECT_TRUE(calledTimes == 1);
	}

	// adding more callbacks during invoking other callbacks
	{
		hamon::stop_source ss;

		hamon::atomic<bool> startedFlag{false};
		hamon::atomic<bool> finishFlag{false};
		auto f1 = [&]
		{
			startedFlag = true;
			startedFlag.notify_all();
			finishFlag.wait(false);
		};
		hamon::stop_callback<decltype(f1)> sc(ss.get_token(), f1);

		auto thread = hamon::thread([&] { ss.request_stop(); });

		startedFlag.wait(false);

		// first callback is still running, adding another one;
		bool secondCallbackCalled = false;
		auto f2 = [&] { secondCallbackCalled = true; };
		hamon::stop_callback<decltype(f2)> sc2(ss.get_token(), f2);

		finishFlag = true;
		finishFlag.notify_all();

		thread.join();
		EXPECT_TRUE(secondCallbackCalled);
	}

	// adding callbacks on different threads
	{
		hamon::stop_source ss;

		hamon::vector<hamon::thread> threads;
		hamon::atomic<int> callbackCalledTimes{0};
		hamon::atomic<bool> done{false};
		for (auto i = 0; i < 10; ++i)
		{
			threads.emplace_back(hamon::thread([&] {
				auto f = [&] { callbackCalledTimes.fetch_add(1, hamon::memory_order_relaxed); };
				hamon::stop_callback<decltype(f)> sc{ ss.get_token(), f };
				done.wait(false);
			}));
		}
		using namespace hamon::chrono_literals;
		hamon::this_thread::sleep_for(1_ms);
		ss.request_stop();
		done = true;
		done.notify_all();
		for (auto& thread : threads)
		{
			thread.join();
		}
		EXPECT_TRUE(callbackCalledTimes.load(hamon::memory_order_relaxed) == 10);
	}

	// correct overload
	{
		struct CBWithTracking
		{
			bool& lvalueCalled;
			bool& lvalueConstCalled;
			bool& rvalueCalled;
			bool& rvalueConstCalled;

			void operator()()& { lvalueCalled = true; }
			void operator()() const& { lvalueConstCalled = true; }
			void operator()()&& { rvalueCalled = true; }
			void operator()() const&& { rvalueConstCalled = true; }
		};

		// RValue
		{
			bool lvalueCalled = false;
			bool lvalueConstCalled = false;
			bool rvalueCalled = false;
			bool rvalueConstCalled = false;
			hamon::stop_source ss;
			ss.request_stop();

			hamon::stop_callback<CBWithTracking> sc(
				ss.get_token(), CBWithTracking{ lvalueCalled, lvalueConstCalled, rvalueCalled, rvalueConstCalled });
			EXPECT_TRUE(rvalueCalled);
		}

		// RValue
		{
			bool lvalueCalled = false;
			bool lvalueConstCalled = false;
			bool rvalueCalled = false;
			bool rvalueConstCalled = false;
			hamon::stop_source ss;
			ss.request_stop();

			hamon::stop_callback<const CBWithTracking> sc(
				ss.get_token(), CBWithTracking{ lvalueCalled, lvalueConstCalled, rvalueCalled, rvalueConstCalled });
			EXPECT_TRUE(rvalueConstCalled);
		}

		// LValue
		{
			bool lvalueCalled = false;
			bool lvalueConstCalled = false;
			bool rvalueCalled = false;
			bool rvalueConstCalled = false;
			hamon::stop_source ss;
			ss.request_stop();
			CBWithTracking cb{ lvalueCalled, lvalueConstCalled, rvalueCalled, rvalueConstCalled };
			hamon::stop_callback<CBWithTracking&> sc(ss.get_token(), cb);
			EXPECT_TRUE(lvalueCalled);
		}

		// const LValue
		{
			bool lvalueCalled = false;
			bool lvalueConstCalled = false;
			bool rvalueCalled = false;
			bool rvalueConstCalled = false;
			hamon::stop_source ss;
			ss.request_stop();
			CBWithTracking cb{ lvalueCalled, lvalueConstCalled, rvalueCalled, rvalueConstCalled };
			hamon::stop_callback<const CBWithTracking&> sc(ss.get_token(), cb);
			EXPECT_TRUE(lvalueConstCalled);
		}
	}
}

}	// namespace ctor_rvalue_test

}	// namespace hamon_stop_callback_test
