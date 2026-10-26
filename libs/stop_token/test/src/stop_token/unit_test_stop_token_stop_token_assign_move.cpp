/**
 *	@file	unit_test_stop_token_stop_token_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace assign_move_test
{

static_assert( hamon::is_move_assignable_v<hamon::stop_token>, "");
static_assert( hamon::is_nothrow_move_assignable_v<hamon::stop_token>, "");
static_assert(!hamon::is_trivially_move_assignable_v<hamon::stop_token>, "");

GTEST_TEST(StopTokenTest, AssignMoveTest)
{
	hamon::stop_token st1;

	hamon::stop_source source;
	auto st2 = source.get_token();

	EXPECT_TRUE(st1 != st2);

	source.request_stop();

	EXPECT_FALSE(st1.stop_requested());
	EXPECT_TRUE(st2.stop_requested());

	auto& ref = st1 = hamon::move(st2);
	static_assert(hamon::is_same_v<decltype(ref), hamon::stop_token&>, "");
	EXPECT_TRUE(&ref == &st1);

	EXPECT_TRUE(st1 != st2);
	EXPECT_TRUE(st1.stop_requested());
	EXPECT_FALSE(st2.stop_requested());
}

}	// namespace assign_move_test

}	// namespace hamon_stop_token_test
