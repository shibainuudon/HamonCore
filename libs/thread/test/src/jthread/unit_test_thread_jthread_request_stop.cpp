/**
 *	@file	unit_test_thread_jthread_request_stop.cpp
 *
 *	@brief	request_stop のテスト
 *
 *	bool request_stop() noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace request_stop_test
{

static_assert(noexcept(hamon::declval<hamon::jthread&>().request_stop()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::jthread&>().request_stop()), bool>, "");

GTEST_TEST(JThreadTest, RequestStopTest)
{
	// Represents a thread
	{
		hamon::jthread jt([] {});
		auto st = jt.get_stop_token();
		EXPECT_FALSE(st.stop_requested());
		bool result = jt.request_stop();
		EXPECT_TRUE(result);
		EXPECT_TRUE(st.stop_requested());
	}

	// Does not represent a thread
	{
		hamon::jthread jt{};
		bool result = jt.request_stop();
		EXPECT_FALSE(result);
	}
}

}	// namespace request_stop_test

}	// namespace hamon_jthread_test
