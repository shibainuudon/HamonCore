/**
 *	@file	unit_test_bigint_xor_equal.cpp
 *
 *	@brief	operator^=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, XorEqualTest)
{
	{
		auto x = hamon::bigint{0};
		EXPECT_EQ(x, 0);

		x ^= hamon::bigint(1);
		EXPECT_EQ(x, 0x0001);

		x ^= hamon::bigint(1);
		EXPECT_EQ(x, 0x0000);

		x ^= hamon::bigint(0x1234);
		EXPECT_EQ(x, 0x1234);

		x ^= hamon::bigint(0xff00);
		EXPECT_EQ(x, 0xed34);
	}
}
