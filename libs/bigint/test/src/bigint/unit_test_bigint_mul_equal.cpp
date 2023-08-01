/**
 *	@file	unit_test_bigint_mul_equal.cpp
 *
 *	@brief	operator*=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, MulEqualTest)
{
	{
		hamon::bigint x{1};
		EXPECT_EQ(x, 1);

		x *= hamon::bigint{2};
		EXPECT_EQ(x, 2);

		x *= hamon::bigint{2};
		EXPECT_EQ(x, 4);

		x *= hamon::bigint{12345};
		EXPECT_EQ(x, 49380);

		x *= -1;
		EXPECT_EQ(x, -49380);

		x *= 0;
		EXPECT_EQ(x, 0);
	}
	{
		hamon::bigint x{2};
		EXPECT_EQ(x, 2);

		x *= x;
		EXPECT_EQ(x, 4);

		x *= x;
		EXPECT_EQ(x, 16);

		x *= x;
		EXPECT_EQ(x, 256);

		x *= -x;
		EXPECT_EQ(x, -65536);

		x *= x;
		EXPECT_EQ(x, 4294967296);

		x *= -x;
		EXPECT_EQ(x.to_string(), "-18446744073709551616");

		x *= x;
		EXPECT_EQ(x.to_string(), "340282366920938463463374607431768211456");
	}
}
