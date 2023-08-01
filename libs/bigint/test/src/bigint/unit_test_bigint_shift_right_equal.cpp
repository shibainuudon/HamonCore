/**
 *	@file	unit_test_bigint_shift_right_equal.cpp
 *
 *	@brief	operator>>=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, ShiftRightEqualTest)
{
	{
		auto x = hamon::bigint{12345678};
		EXPECT_EQ(x, 12345678);

		x >>= 1;
		EXPECT_EQ(x, 6172839);

		x >>= 2;
		EXPECT_EQ(x, 1543209);

		x >>= 3;
		EXPECT_EQ(x, 192901);

		x >>= 10;
		EXPECT_EQ(x, 188);
	}
	{
		auto x = hamon::bigint{"0x1234567890123456789012345678901234567890"};

		x >>= 4;
		EXPECT_EQ(x, hamon::bigint{"0x123456789012345678901234567890123456789"});

		x >>= 0x10000000;
		EXPECT_EQ(x, 0);
	}
}
