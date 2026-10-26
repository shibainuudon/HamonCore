/**
 *	@file	unit_test_stop_token_never_stop_token.cpp
 *
 *	@brief	never_stop_token のテスト
 */

#include <hamon/stop_token/never_stop_token.hpp>
#include <hamon/stop_token/unstoppable_token.hpp>
#include <hamon/stop_token/stoppable_token.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace never_stop_token_test
{

static_assert(hamon::is_default_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_nothrow_default_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_trivially_default_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_implicitly_default_constructible_v<hamon::never_stop_token>, "");

static_assert(hamon::is_copy_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_nothrow_copy_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_trivially_copy_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_implicitly_copy_constructible_v<hamon::never_stop_token>, "");

static_assert(hamon::is_move_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_nothrow_move_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_trivially_move_constructible_v<hamon::never_stop_token>, "");
static_assert(hamon::is_implicitly_move_constructible_v<hamon::never_stop_token>, "");

// [stoptoken.never]
static_assert(hamon::unstoppable_token<hamon::never_stop_token>, "");
static_assert(hamon::stoppable_token<hamon::never_stop_token>, "");

GTEST_TEST(StopTokenTest, NeverStopTokenTest)
{
	hamon::never_stop_token st1;
	EXPECT_FALSE(st1.stop_requested());
	EXPECT_FALSE(st1.stop_possible());

	hamon::never_stop_token st2;
	EXPECT_TRUE (st1 == st2);
	EXPECT_FALSE(st1 != st2);
}

}	// namespace never_stop_token_test

}	// namespace hamon_stop_token_test
