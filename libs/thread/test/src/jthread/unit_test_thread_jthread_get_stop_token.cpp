/**
 *	@file	unit_test_thread_jthread_get_stop_token.cpp
 *
 *	@brief	get_stop_token のテスト
 *
 *	stop_token get_stop_token() const noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/stop_token.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/as_const.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace get_stop_token_test
{

static_assert(noexcept(hamon::declval<hamon::jthread const&>().get_stop_token()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::jthread const&>().get_stop_token()), hamon::stop_token>, "");

GTEST_TEST(JThreadTest, GetStopTokenTest)
{
	// Represents a thread
	{
		hamon::jthread jt([] {});
		auto ss = jt.get_stop_source();
		hamon::stop_token st = hamon::as_const(jt).get_stop_token();

		EXPECT_TRUE(st.stop_possible());
		EXPECT_FALSE(st.stop_requested());
		ss.request_stop();
		EXPECT_TRUE(st.stop_requested());
	}

	// Does not represent a thread
	{
		const hamon::jthread jt{};
		hamon::stop_token st = jt.get_stop_token();

		EXPECT_FALSE(st.stop_possible());
	}
}

}	// namespace get_stop_token_test

}	// namespace hamon_jthread_test
