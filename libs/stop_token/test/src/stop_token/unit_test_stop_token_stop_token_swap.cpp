/**
 *	@file	unit_test_stop_token_stop_token_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(stop_token&) noexcept;
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace swap_test
{

GTEST_TEST(StopTokenTest, SwapTest)
{
	hamon::stop_source ss;
	hamon::stop_token st1 = ss.get_token();
	hamon::stop_token st2;

	EXPECT_TRUE (st1.stop_possible());
	EXPECT_FALSE(st2.stop_possible());

	static_assert(noexcept(st1.swap(st2)), "");
	static_assert(hamon::is_same_v<decltype(st1.swap(st2)), void>, "");

	st1.swap(st2);

	EXPECT_FALSE(st1.stop_possible());
	EXPECT_TRUE (st2.stop_possible());
}

}	// namespace swap_test

}	// namespace hamon_stop_token_test
