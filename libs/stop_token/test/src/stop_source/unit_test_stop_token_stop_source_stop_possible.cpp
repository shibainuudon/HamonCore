/**
 *	@file	unit_test_stop_token_stop_source_stop_possible.cpp
 *
 *	@brief	stop_possibleのテスト
 *
 *	bool stop_possible() const noexcept;
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace stop_possible_test
{

static_assert(noexcept(hamon::declval<hamon::stop_source const&>().stop_possible()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::stop_source const&>().stop_possible()), bool>, "");

GTEST_TEST(StopSourceTest, StopPossibleTest)
{
	hamon::stop_source ss1;
	hamon::stop_source ss2(hamon::nostopstate);

	EXPECT_TRUE (ss1.stop_possible());
	EXPECT_FALSE(ss2.stop_possible());
}

}	// namespace stop_possible_test

}	// namespace hamon_stop_token_test
