/**
 *	@file	unit_test_stop_token_stop_token_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace ctor_copy_test
{

static_assert( hamon::is_copy_constructible_v<hamon::stop_token>, "");
static_assert( hamon::is_nothrow_copy_constructible_v<hamon::stop_token>, "");
static_assert(!hamon::is_trivially_copy_constructible_v<hamon::stop_token>, "");
static_assert( hamon::is_implicitly_copy_constructible_v<hamon::stop_token>, "");

GTEST_TEST(StopTokenTest, CtorCopyTest)
{
	hamon::stop_source ss;
	hamon::stop_token st1 = ss.get_token();

	EXPECT_FALSE(st1.stop_requested());
	EXPECT_TRUE (st1.stop_possible());

	hamon::stop_token st2{st1};

	EXPECT_FALSE(st1.stop_requested());
	EXPECT_TRUE (st1.stop_possible());
	EXPECT_FALSE(st2.stop_requested());
	EXPECT_TRUE (st2.stop_possible());

	ss.request_stop();

	EXPECT_TRUE (st1.stop_requested());
	EXPECT_TRUE (st1.stop_possible());
	EXPECT_TRUE (st2.stop_requested());
	EXPECT_TRUE (st2.stop_possible());
}

}	// namespace ctor_copy_test

}	// namespace hamon_stop_token_test
