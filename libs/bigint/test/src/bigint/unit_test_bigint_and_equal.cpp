/**
 *	@file	unit_test_bigint_and_equal.cpp
 *
 *	@brief	operator&=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, AndEqualTest)
{
	{
		auto x = hamon::bigint{0xffffffff};
		EXPECT_EQ(x, 0xffffffff);

		x &= hamon::bigint(0x80ff000f);
		EXPECT_EQ(x, 0x80ff000f);

		x &= hamon::bigint{0x0000ffff};
		EXPECT_EQ(x, 0x0000000f);

		x &= hamon::bigint(1);
		EXPECT_EQ(x, 0x00000001);
	}
	{
		auto x = hamon::bigint{0xffffffff};
		EXPECT_EQ(x, 0xffffffff);

		x &= hamon::bigint("0xFEDCBA9876543210000000000000000");
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint{0x12345678};
		EXPECT_EQ(x, 0x12345678);

		x &= hamon::bigint("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
		EXPECT_EQ(x, 0x12345678);

		x &= hamon::bigint("0x000000000000000000000000000FFFF");
		EXPECT_EQ(x, 0x5678);
	}
}
