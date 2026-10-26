/**
 *	@file	unit_test_stop_token_stop_source_ctor_nostopstate_t.cpp
 *
 *	@brief	nostopstate_tを引数に取るコンストラクタのテスト
 *
 *	explicit stop_source(nostopstate_t) noexcept {}
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace ctor_nostopstate_t_test
{

static_assert( hamon::is_constructible_v<hamon::stop_source, hamon::nostopstate_t>, "");
static_assert( hamon::is_nothrow_constructible_v<hamon::stop_source, hamon::nostopstate_t>, "");
static_assert(!hamon::is_trivially_constructible_v<hamon::stop_source, hamon::nostopstate_t>, "");
static_assert(!hamon::is_implicitly_constructible_v<hamon::stop_source, hamon::nostopstate_t>, "");

GTEST_TEST(StopSourceTest, CtorNoStopStateTTest)
{
	hamon::stop_source ss(hamon::nostopstate);
	EXPECT_FALSE(ss.stop_requested());
	EXPECT_FALSE(ss.stop_possible());
}

}	// namespace ctor_nostopstate_t_test

}	// namespace hamon_stop_token_test
