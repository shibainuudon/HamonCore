/**
 *	@file	unit_test_thread_jthread_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~jthread();
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/thread/this_thread.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/stop_token.hpp>
#include <hamon/optional.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace dtor_test
{

GTEST_TEST(JThreadTest, DtorTest)
{
	// !joinable()
	{
		hamon::jthread jt;
		EXPECT_FALSE(jt.joinable());
	}

	// If joinable() is true, calls request_stop() and then join().
	// request_stop is called
	{
		hamon::optional<hamon::jthread> jt = hamon::jthread([] {});
		bool called = false;
		auto f = [&called] { called = true; };
		hamon::stop_callback<decltype(f)> cb(jt->get_stop_token(), f);
		jt.reset();
		EXPECT_TRUE(called);
	}

	// If joinable() is true, calls request_stop() and then join().
	// join is called
	{
		hamon::atomic_int calledTimes{0};
		hamon::vector<hamon::jthread> jts;

		constexpr auto numberOfThreads = 10u;
		jts.reserve(numberOfThreads);
		for (auto i = 0u; i < numberOfThreads; ++i)
		{
			jts.emplace_back(hamon::jthread([&calledTimes] {
				hamon::this_thread::sleep_for(hamon::chrono::milliseconds{ 2 });
				calledTimes.fetch_add(1, hamon::memory_order_relaxed);
			}));
		}
		jts.clear();

		// If join was called as expected, calledTimes must equal to numberOfThreads
		// If join was not called, there is a chance that the check below happened
		// before test threads incrementing the counter, thus calledTimed would
		// be less than numberOfThreads.
		// This is not going to catch issues 100%. Creating more threads would increase
		// the probability of catching the issue
		EXPECT_TRUE(calledTimes.load(hamon::memory_order_relaxed) == numberOfThreads);
	}
}

}	// namespace dtor_test

}	// namespace hamon_jthread_test
