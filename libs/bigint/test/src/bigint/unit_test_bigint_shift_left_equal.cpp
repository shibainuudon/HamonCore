/**
 *	@file	unit_test_bigint_shift_left_equal.cpp
 *
 *	@brief	operator<<=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, ShiftLeftEqualTest)
{
	{
		auto x = hamon::bigint{1};
		EXPECT_EQ(x, 0x01);

		x <<= 1;
		EXPECT_EQ(x, 0x02);

		x <<= 1;
		EXPECT_EQ(x, 0x04);

		x <<= 2;
		EXPECT_EQ(x, 0x10);

		x <<= 4;
		EXPECT_EQ(x, 0x100);

		x <<= 100;
		EXPECT_EQ(x, hamon::bigint{"0x1000000000000000000000000000"});
	}
	{
		auto x = hamon::bigint{0xff};
		EXPECT_EQ(x, 0xff);

		x <<= 4;
		EXPECT_EQ(x, 0xff0);

		x <<= 8;
		EXPECT_EQ(x, 0xff000);

		x <<= 123;
		EXPECT_EQ(x, hamon::bigint{"0x7f8000000000000000000000000000000000"});
	}
}
