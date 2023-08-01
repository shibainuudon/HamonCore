/**
 *	@file	unit_test_bigint_shift_right.cpp
 *
 *	@brief	operator>>のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, ShiftRightTest)
{
	{
		auto x = hamon::bigint{0x1234} >> 1;
		EXPECT_EQ(x, 0x91a);
	}
	{
		auto x = hamon::bigint{0xffff} >> 1;
		EXPECT_EQ(x, 0x7fff);
	}
	{
		auto x = hamon::bigint{0xffffff} >> 2;
		EXPECT_EQ(x, 0x3fffff);
	}
	{
		auto x = hamon::bigint{"0x123400000000000000000000000000000000"} >> 128;
		EXPECT_EQ(x, 0x1234);
	}
	{
		auto x = hamon::bigint{"0x123400000000000000000000000000000000"} >> 129;
		EXPECT_EQ(x, 0x91a);
	}
	{
		auto x = hamon::bigint{"0x12340000000000000000000000000000000000000000000000000000000000000000"} >> 255;
		EXPECT_EQ(x, 0x2468);
	}
	{
		auto x = hamon::bigint{"0x12340000000000000000000000000000000000000000000000000000000000000000"} >> 256;
		EXPECT_EQ(x, 0x1234);
	}
}
