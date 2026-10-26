/**
 *	@file	unit_test_stop_token_stop_source_stop_requested.cpp
 *
 *	@brief	stop_requestedのテスト
 *
 *	bool stop_requested() const noexcept;
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/chrono.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace stop_requested_test
{

static_assert(noexcept(hamon::declval<hamon::stop_source const&>().stop_requested()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::stop_source const&>().stop_requested()), bool>, "");

GTEST_TEST(StopSourceTest, StopRequestedTest)
{
	// no state
	{
		const hamon::stop_source ss{ hamon::nostopstate };
		EXPECT_FALSE(ss.stop_requested());
	}

	// has state
	{
		hamon::stop_source ss;
		EXPECT_FALSE(ss.stop_requested());

		ss.request_stop();
		EXPECT_TRUE(ss.stop_requested());
	}

	// request from another instance with same state
	{
		hamon::stop_source ss1;
		auto ss2 = ss1;
		ss2.request_stop();
		EXPECT_TRUE(ss1.stop_requested());
	}

	// request from another instance with different state
	{
		hamon::stop_source ss1;
		hamon::stop_source ss2;

		ss2.request_stop();
		EXPECT_FALSE(ss1.stop_requested());
	}

	// multiple threads
	{
		hamon::stop_source ss;

		hamon::thread t([&]() { ss.request_stop(); });

		t.join();
		EXPECT_TRUE(ss.stop_requested());
	}

	// [thread.stopsource.intro] A call to request_stop that returns true
	// synchronizes with a call to stop_requested on an associated stop_source
	// or stop_source object that returns true.
	{
		hamon::stop_source ss;

		bool flag = false;

		hamon::thread t([&]() {
			using namespace hamon::chrono_literals;
			hamon::this_thread::sleep_for(1_ms);

			// happens-before request_stop
			flag = true;
			auto b = ss.request_stop();
			EXPECT_TRUE(b);
		});

		while (!ss.stop_requested())
		{
			hamon::this_thread::yield();
		}

		// write should be visible to the current thread
		EXPECT_TRUE(flag == true);

		t.join();
	}
}

}	// namespace stop_requested_test

}	// namespace hamon_stop_token_test
