/**
 *	@file	unit_test_stop_token_stop_source_get_token.cpp
 *
 *	@brief	get_tokenのテスト
 *
 *	stop_token get_token() const noexcept;
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace get_token_test
{

static_assert(noexcept(hamon::declval<hamon::stop_source const&>().get_token()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::stop_source const&>().get_token()), hamon::stop_token>, "");

GTEST_TEST(StopSourceTest, GetTokenTest)
{
	hamon::stop_source ss1;
	hamon::stop_source ss2(hamon::nostopstate);

	hamon::stop_token st1 = ss1.get_token();
	hamon::stop_token st2 = ss2.get_token();

	EXPECT_TRUE (st1.stop_possible());
	EXPECT_FALSE(st2.stop_possible());
}

}	// namespace get_token_test

}	// namespace hamon_stop_token_test
