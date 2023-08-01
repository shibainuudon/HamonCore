/**
 *	@file	unit_test_bigint_or.cpp
 *
 *	@brief	operator|のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, OrTest)
{
	{
		auto x = hamon::bigint{0x0F} | hamon::bigint{0x35};
		EXPECT_EQ(x, 0x3F);
	}
	{
		auto x = hamon::bigint{0x35} | hamon::bigint{0xf0};
		EXPECT_EQ(x, 0xF5);
	}
	{
		auto x = hamon::bigint{0x0F} | hamon::bigint{0x12};
		EXPECT_EQ(x, 0x1F);
	}
	{
		auto x = hamon::bigint{0x77} | hamon::bigint{0x20};
		EXPECT_EQ(x, 0x77);
	}
	{
		auto x = hamon::bigint{0x01} | hamon::bigint{"0x8000000000000000000000000000000"};
		EXPECT_EQ(x, hamon::bigint{"0x8000000000000000000000000000001"});
	}
	{
		auto x = hamon::bigint{"0x1234000000000000000000000000000"} | hamon::bigint{0x123};
		EXPECT_EQ(x, hamon::bigint{"0x1234000000000000000000000000123"});
	}
}
