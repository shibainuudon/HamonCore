/**
 *	@file	unit_test_stop_token_stop_source_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace ctor_move_test
{

static_assert( hamon::is_move_constructible_v<hamon::stop_source>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::stop_source>, "");
static_assert(!hamon::is_trivially_move_constructible_v<hamon::stop_source>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::stop_source>, "");

GTEST_TEST(StopSourceTest, CtorMoveTest)
{
	{
		hamon::stop_source source;

		EXPECT_TRUE(source.stop_possible());
		EXPECT_FALSE(source.stop_requested());

		hamon::stop_source source2{ hamon::move(source) };

		EXPECT_FALSE(source.stop_possible());
		EXPECT_FALSE(source.stop_requested());

		EXPECT_TRUE(source2.stop_possible());
		EXPECT_FALSE(source2.stop_requested());

		source2.request_stop();

		EXPECT_FALSE(source.stop_possible());
		EXPECT_FALSE(source.stop_requested());

		EXPECT_TRUE(source2.stop_possible());
		EXPECT_TRUE(source2.stop_requested());
	}
}

}	// namespace ctor_move_test

}	// namespace hamon_stop_token_test
