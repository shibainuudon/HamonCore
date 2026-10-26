/**
 *	@file	unit_test_stop_token_stop_source_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	stop_source();
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::stop_source>, "");
static_assert(!hamon::is_nothrow_default_constructible_v<hamon::stop_source>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::stop_source>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::stop_source>, "");

GTEST_TEST(StopSourceTest, CtorDefaultTest)
{
	{
		hamon::stop_source ss;

		// [stopsource.cons]/2
		EXPECT_FALSE(ss.stop_requested());
		EXPECT_TRUE (ss.stop_possible());
	}
	{
		hamon::stop_source ss = {};	// implicit

		// [stopsource.cons]/2
		EXPECT_FALSE(ss.stop_requested());
		EXPECT_TRUE (ss.stop_possible());
	}
}

}	// namespace ctor_default_test

}	// namespace hamon_stop_token_test
