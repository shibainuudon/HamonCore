/**
 *	@file	unit_test_stop_token_stop_token_stop_requested.cpp
 *
 *	@brief	stop_requested のテスト
 *
 *	bool stop_requested() const noexcept;
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/chrono.hpp>
#include <hamon/optional.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace stop_requested_test
{

static_assert(noexcept(hamon::declval<hamon::stop_token const&>().stop_requested()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::stop_token const&>().stop_requested()), bool>, "");

GTEST_TEST(StopTokenTest, StopRequestedTest)
{
	// no state
	{
		const hamon::stop_token st;
		EXPECT_FALSE(st.stop_requested());
	}

	// has state
	{
		hamon::stop_source ss;
		const auto st = ss.get_token();
		EXPECT_FALSE(st.stop_requested());

		ss.request_stop();
		EXPECT_TRUE(st.stop_requested());
	}

	// already requested before constructor
	{
		hamon::stop_source ss;
		ss.request_stop();
		const auto st = ss.get_token();
		EXPECT_TRUE(st.stop_requested());
	}

	// stop_token should share the state
	{
		hamon::optional<hamon::stop_source> ss{ hamon::in_place };
		ss->request_stop();
		const auto st = ss->get_token();

		ss.reset();
		EXPECT_TRUE(st.stop_requested());
	}

	// single stop_source, multiple stop_token
	{
		hamon::stop_source ss;
		const auto st1 = ss.get_token();
		const auto st2 = ss.get_token();
		EXPECT_FALSE(st1.stop_requested());
		EXPECT_FALSE(st2.stop_requested());

		ss.request_stop();
		EXPECT_TRUE(st1.stop_requested());
		EXPECT_TRUE(st2.stop_requested());
	}

	// multiple stop_source, multiple stop_token
	{
		hamon::stop_source ss1;
		hamon::stop_source ss2;

		const auto st1 = ss1.get_token();
		const auto st2 = ss2.get_token();
		EXPECT_FALSE(st1.stop_requested());
		EXPECT_FALSE(st2.stop_requested());

		ss1.request_stop();
		EXPECT_TRUE(st1.stop_requested());
		EXPECT_FALSE(st2.stop_requested());
	}

	// multiple threads
	{
		hamon::stop_source ss;
		const auto st = ss.get_token();
		EXPECT_FALSE(st.stop_requested());

		hamon::thread t([&]() { ss.request_stop(); });

		t.join();
		EXPECT_TRUE(st.stop_requested());
	}

	// maybe concurrent calls
	{
		hamon::stop_source ss;
		const auto st = ss.get_token();
		EXPECT_FALSE(st.stop_requested());

		hamon::thread t([&]() { ss.request_stop(); });

		while (!st.stop_requested())
		{
			// should eventually exit the loop
			hamon::this_thread::yield();
		}

		t.join();
	}

	// [thread.stoptoken.intro] A call to request_stop that returns true
	// synchronizes with a call to stop_requested on an associated stop_token
	// or stop_source object that returns true.
	{
		hamon::stop_source ss;
		const auto st = ss.get_token();
		EXPECT_FALSE(st.stop_requested());

		bool flag = false;

		hamon::thread t([&]() {
			using namespace hamon::chrono_literals;
			hamon::this_thread::sleep_for(1_ms);

			// happens-before request_stop
			flag = true;
			auto b = ss.request_stop();
			EXPECT_TRUE(b);
		});

		while (!st.stop_requested())
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
