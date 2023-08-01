/**
 *	@file	unit_test_bigint_shift_left.cpp
 *
 *	@brief	operator<<のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, ShiftLeftTest)
{
	{
		auto x = hamon::bigint{0x1234} << 1;
		EXPECT_EQ(x, 0x2468ULL);
	}
	{
		auto x = hamon::bigint{0x1234} << 31;
		EXPECT_EQ(x, 0x91a00000000ULL);
	}
	{
		auto x = hamon::bigint{0x1234} << 32;
		EXPECT_EQ(x, 0x123400000000ULL);
	}
	{
		auto x = hamon::bigint{0x1234} << 33;
		EXPECT_EQ(x, 0x246800000000ULL);
	}
	{
		auto x = hamon::bigint{0x1234} << 34;
		EXPECT_EQ(x, 0x48d000000000ULL);
	}
	{
		auto x = hamon::bigint{0x1234} << 40;
		EXPECT_EQ(x, 0x12340000000000ULL);
	}
	{
		auto x = hamon::bigint{0x1234} << 41;
		EXPECT_EQ(x, 0x24680000000000ULL);
	}
	{
		auto x = hamon::bigint{0x1234} << 64;
		EXPECT_EQ(x, hamon::bigint{"0x12340000000000000000"});
	}
	{
		auto x = hamon::bigint{0x1234} << 65;
		EXPECT_EQ(x, hamon::bigint{"0x24680000000000000000"});
	}
	{
		auto x = hamon::bigint{0x1234} << 128;
		EXPECT_EQ(x, hamon::bigint{"0x123400000000000000000000000000000000"});
	}
	{
		auto x = hamon::bigint{0x1234} << 255;
		EXPECT_EQ(x, hamon::bigint{"0x91A0000000000000000000000000000000000000000000000000000000000000000"});
	}
}
