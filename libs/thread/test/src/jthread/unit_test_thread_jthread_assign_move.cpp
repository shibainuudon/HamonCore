/**
 *	@file	unit_test_thread_jthread_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	jthread& operator=(jthread&&) noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/thread/this_thread.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/stop_token.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace assign_move_test
{

static_assert( hamon::is_move_assignable_v<hamon::jthread>, "");
static_assert( hamon::is_nothrow_move_assignable_v<hamon::jthread>, "");
static_assert(!hamon::is_trivially_move_assignable_v<hamon::jthread>, "");

GTEST_TEST(JThreadTest, AssignMoveTest)
{
	// If &x == this is true, there are no effects.
	{
		hamon::jthread j([] {});
		auto id = j.get_id();
		auto ssource = j.get_stop_source();
		j = hamon::move(j);
		EXPECT_TRUE(j.get_id() == id);
		EXPECT_TRUE(j.get_stop_source() == ssource);
	}

	// if joinable() is true, calls request_stop() and then join()
	// request_stop is called
	{
		hamon::jthread j1([] {});
		bool called = false;
		auto f = [&called] { called = true; };
		hamon::stop_callback<decltype(f)> cb(j1.get_stop_token(), f);

		hamon::jthread j2([] {});
		j1 = hamon::move(j2);
		EXPECT_TRUE(called);
	}

	// if joinable() is true, calls request_stop() and then join()
	// join is called
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
			jts[i] = hamon::jthread{};
		}

		// If join was called as expected, calledTimes must equal to numberOfThreads
		// If join was not called, there is a chance that the check below happened
		// before test threads incrementing the counter, thus calledTimed would
		// be less than numberOfThreads.
		// This is not going to catch issues 100%. Creating more threads to increase
		// the probability of catching the issue
		EXPECT_TRUE(calledTimes.load(hamon::memory_order_relaxed) == numberOfThreads);
	}

	// then assigns the state of x to *this
	{
		hamon::jthread j1([] {});
		hamon::jthread j2([] {});
		auto id2 = j2.get_id();
		auto ssource2 = j2.get_stop_source();

		j1 = hamon::move(j2);

		EXPECT_TRUE(j1.get_id() == id2);
		EXPECT_TRUE(j1.get_stop_source() == ssource2);
	}

	// sets x to a default constructed state
	{
		hamon::jthread j1([] {});
		hamon::jthread j2([] {});
		j1 = hamon::move(j2);

		EXPECT_TRUE(j2.get_id() == hamon::jthread::id());
		EXPECT_FALSE(j2.get_stop_source().stop_possible());
	}

	// joinable is false
	{
		hamon::jthread j1;
		hamon::jthread j2([] {});

		auto j2Id = j2.get_id();

		j1 = hamon::move(j2);

		EXPECT_TRUE(j1.get_id() == j2Id);
	}

	// LWG3788: self-assignment
	{
		hamon::jthread j([] {});
		auto oldId = j.get_id();
		j = hamon::move(j);

		EXPECT_TRUE(j.get_id() == oldId);
	}
}

}	// namespace assign_move_test

}	// namespace hamon_jthread_test
