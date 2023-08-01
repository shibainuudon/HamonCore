/**
 *	@file	unit_test_bigint_div_equal.cpp
 *
 *	@brief	operator/=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, DivEqualTest)
{
	{
		hamon::bigint x{100};
		EXPECT_EQ(x, 100);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, 50);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, 25);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, 12);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, 6);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, 3);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, 1);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, 0);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, 0);
	}
	{
		hamon::bigint x(-256);
		EXPECT_EQ(x, -256);

		x /= hamon::bigint{2};
		EXPECT_EQ(x, -128);

		x /= -2;
		EXPECT_EQ(x, 64);

		x /= -4;
		EXPECT_EQ(x, -16);

		x /= hamon::bigint{4};
		EXPECT_EQ(x, -4);

		x /= hamon::bigint{5};
		EXPECT_EQ(x, 0);

		x /= -1;
		EXPECT_EQ(x, 0);
	}
	{
		hamon::bigint x{0xffff};
		EXPECT_EQ(x, 0xffff);

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
		x /= x;
		EXPECT_EQ(x, 1);
HAMON_WARNING_POP()
	}
}
