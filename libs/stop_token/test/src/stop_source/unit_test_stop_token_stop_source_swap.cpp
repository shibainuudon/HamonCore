/**
 *	@file	unit_test_stop_token_stop_source_swap.cpp
 *
 *	@brief	swapのテスト
 *
 *	void swap(stop_source&) noexcept;
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace swap_test
{

GTEST_TEST(StopSourceTest, SwapTest)
{
	hamon::stop_source ss1;
	hamon::stop_source ss2(hamon::nostopstate);

	EXPECT_TRUE (ss1.stop_possible());
	EXPECT_FALSE(ss2.stop_possible());

	static_assert(noexcept(ss1.swap(ss2)), "");
	static_assert(hamon::is_same_v<decltype(ss1.swap(ss2)), void>, "");

	ss1.swap(ss2);

	EXPECT_FALSE(ss1.stop_possible());
	EXPECT_TRUE (ss2.stop_possible());
}

}	// namespace swap_test

}	// namespace hamon_stop_token_test
