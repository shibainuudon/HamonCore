/**
 *	@file	unit_test_thread_jthread_join.cpp
 *
 *	@brief	join のテスト
 *
 *	void join();
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/thread/this_thread.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace join_test
{

static_assert(!noexcept(hamon::declval<hamon::jthread&>().join()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::jthread&>().join()), void>, "");

GTEST_TEST(JThreadTest, JoinTest)
{
	// Effects: Blocks until the thread represented by *this has completed.
	{
		hamon::atomic_int calledTimes{0};
		hamon::vector<hamon::jthread> jts;
		constexpr auto numberOfThreads = 10u;
		jts.reserve(numberOfThreads);
		for (auto i = 0u; i < numberOfThreads; ++i)
		{
			jts.emplace_back(hamon::jthread([&] {
				hamon::this_thread::sleep_for(hamon::chrono::milliseconds(2));
				calledTimes.fetch_add(1, hamon::memory_order_relaxed);
			}));
		}

		for (auto i = 0u; i < numberOfThreads; ++i)
		{
			jts[i].join();
		}

		// If join did block, calledTimes must equal to numberOfThreads
		// If join did not block, there is a chance that the check below happened
		// before test threads incrementing the counter, thus calledTimed would
		// be less than numberOfThreads.
		// This is not going to catch issues 100%. Creating more threads to increase
		// the probability of catching the issue
		EXPECT_TRUE(calledTimes.load(hamon::memory_order_relaxed) == numberOfThreads);
	}

	// Synchronization: The completion of the thread represented by *this synchronizes with
	// ([intro.multithread]) the corresponding successful join() return.
	{
		bool flag = false;
		hamon::jthread jt([&] { flag = true; });
		jt.join();
		EXPECT_TRUE(flag); // non atomic write is visible to the current thread
	}

	// Postconditions: The thread represented by *this has completed. get_id() == id().
	{
		hamon::jthread jt([] {});
		EXPECT_TRUE(jt.get_id() != hamon::jthread::id());
		jt.join();
		EXPECT_TRUE(jt.get_id() == hamon::jthread::id());
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	// Throws: system_error when an exception is required ([thread.req.exception]).
	// invalid_argument - if the thread is not joinable.
	{
		hamon::jthread jt;
		try
		{
			jt.join();
			EXPECT_TRUE(false);
		}
		catch (const hamon::system_error& err)
		{
			EXPECT_TRUE(err.code() == hamon::errc::invalid_argument);
		}
	}
#endif
}

}	// namespace join_test

}	// namespace hamon_jthread_test
