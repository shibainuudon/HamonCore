/**
 *	@file	unit_test_stop_token_stop_token_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace ctor_move_test
{

static_assert( hamon::is_move_constructible_v<hamon::stop_token>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::stop_token>, "");
static_assert(!hamon::is_trivially_move_constructible_v<hamon::stop_token>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::stop_token>, "");

GTEST_TEST(StopTokenTest, CtorMoveTest)
{
	hamon::stop_source ss;
	hamon::stop_token st1 = ss.get_token();

	EXPECT_FALSE(st1.stop_requested());
	EXPECT_TRUE (st1.stop_possible());

	hamon::stop_token st2{hamon::move(st1)};

	EXPECT_FALSE(st1.stop_requested());
	EXPECT_FALSE(st1.stop_possible());
	EXPECT_FALSE(st2.stop_requested());
	EXPECT_TRUE (st2.stop_possible());

	ss.request_stop();

	EXPECT_FALSE(st1.stop_requested());
	EXPECT_FALSE(st1.stop_possible());
	EXPECT_TRUE (st2.stop_requested());
	EXPECT_TRUE (st2.stop_possible());
}

}	// namespace ctor_move_test

}	// namespace hamon_stop_token_test
