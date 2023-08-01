/**
 *	@file	unit_test_bigint_decrement.cpp
 *
 *	@brief	operator--のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, DecrementTest)
{
	{
		hamon::bigint x1 = 2;
		EXPECT_EQ(x1, 2);

		auto x2 = --x1;
		EXPECT_EQ(x1, 1);
		EXPECT_EQ(x2, 1);

		auto x3 = --x1;
		EXPECT_EQ(x1, 0);
		EXPECT_EQ(x3, 0);

		auto x4 = --x1;
		EXPECT_EQ(x1, -1);
		EXPECT_EQ(x4, -1);

		auto x5 = --x1;
		EXPECT_EQ(x1, -2);
		EXPECT_EQ(x5, -2);
	}
	{
		hamon::bigint x1{"1000000000000000000000"};

		auto x2 = --x1;
		EXPECT_EQ(x1, hamon::bigint{"999999999999999999999"});
		EXPECT_EQ(x2, hamon::bigint{"999999999999999999999"});

		auto x3 = --x1;
		EXPECT_EQ(x1, hamon::bigint{"999999999999999999998"});
		EXPECT_EQ(x3, hamon::bigint{"999999999999999999998"});
	}

	{
		hamon::bigint x1 = 2;
		EXPECT_EQ(x1, 2);

		auto x2 = x1--;
		EXPECT_EQ(x1, 1);
		EXPECT_EQ(x2, 2);

		auto x3 = x1--;
		EXPECT_EQ(x1, 0);
		EXPECT_EQ(x3, 1);

		auto x4 = x1--;
		EXPECT_EQ(x1, -1);
		EXPECT_EQ(x4, 0);

		auto x5 = x1--;
		EXPECT_EQ(x1, -2);
		EXPECT_EQ(x5, -1);
	}
	{
		hamon::bigint x1{"1000000000000000000000"};

		auto x2 = x1--;
		EXPECT_EQ(x1, hamon::bigint{"999999999999999999999"});
		EXPECT_EQ(x2, hamon::bigint{"1000000000000000000000"});

		auto x3 = x1--;
		EXPECT_EQ(x1, hamon::bigint{"999999999999999999998"});
		EXPECT_EQ(x3, hamon::bigint{"999999999999999999999"});
	}
}
