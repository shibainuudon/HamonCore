/**
 *	@file	unit_test_stop_token_stop_token_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	stop_token() noexcept = default;
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::stop_token>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::stop_token>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::stop_token>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::stop_token>, "");

GTEST_TEST(StopTokenTest, CtorDefaultTest)
{
	{
		hamon::stop_token st;
		EXPECT_FALSE(st.stop_requested());
		EXPECT_FALSE(st.stop_possible());
	}
	{
		hamon::stop_token st = {};	// implicit
		EXPECT_FALSE(st.stop_requested());
		EXPECT_FALSE(st.stop_possible());
	}
}

}	// namespace ctor_default_test

}	// namespace hamon_stop_token_test
