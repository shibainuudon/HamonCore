/**
 *	@file	unit_test_stop_token_stop_source_overview.cpp
 *
 *	@brief	stop_sourceのテスト
 */

#include <hamon/stop_token.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace overview_test
{

GTEST_TEST(StopSourceTest, OverviewTest)
{
	hamon::stop_source ss;
	hamon::stop_token st = ss.get_token();

	bool invoked = false;
	auto f = [&]{ invoked = true; };
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::stop_callback cb(st, f);
#else
	hamon::stop_callback<decltype(f)> cb(st, f);
#endif

	EXPECT_FALSE(st.stop_requested());
	EXPECT_FALSE(invoked);

	ss.request_stop();

	EXPECT_TRUE(st.stop_requested());
	EXPECT_TRUE(invoked);
}

}	// namespace overview_test

}	// namespace hamon_stop_token_test
