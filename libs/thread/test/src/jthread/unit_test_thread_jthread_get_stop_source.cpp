/**
 *	@file	unit_test_thread_jthread_get_stop_source.cpp
 *
 *	@brief	get_stop_source のテスト
 *
 *	stop_source get_stop_source() noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/stop_token.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace get_stop_source_test
{

static_assert(noexcept(hamon::declval<hamon::jthread&>().get_stop_source()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::jthread&>().get_stop_source()), hamon::stop_source>, "");

GTEST_TEST(JThreadTest, GetStopSourceTest)
{
	// Represents a thread
	{
		hamon::jthread jt([] {});
		hamon::stop_source result = jt.get_stop_source();
		EXPECT_TRUE(result.stop_possible());
	}

	// Does not represents a thread
	{
		hamon::jthread jt{};
		hamon::stop_source result = jt.get_stop_source();
		EXPECT_FALSE(result.stop_possible());
	}
}

}	// namespace get_stop_source_test

}	// namespace hamon_jthread_test
