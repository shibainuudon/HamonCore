/**
 *	@file	unit_test_stop_token_stop_token_overview.cpp
 *
 *	@brief	stop_tokenのテスト
 */

#include <hamon/stop_token.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace overview_test
{

GTEST_TEST(StopTokenTest, OverviewTest)
{
	hamon::stop_source ss;
	hamon::stop_token st = ss.get_token();
	EXPECT_FALSE(st.stop_requested());

	ss.request_stop();

	EXPECT_TRUE(st.stop_requested());
}

}	// namespace overview_test

}	// namespace hamon_stop_token_test
