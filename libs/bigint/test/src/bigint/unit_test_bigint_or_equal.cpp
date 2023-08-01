/**
 *	@file	unit_test_bigint_or_equal.cpp
 *
 *	@brief	operator|=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, OrEqualTest)
{
	{
		auto x = hamon::bigint{0};
		EXPECT_EQ(x, 0);

		x |= hamon::bigint(1);
		EXPECT_EQ(x, 0x0001);

		x |= hamon::bigint(0x8000);
		EXPECT_EQ(x, 0x8001);

		x |= hamon::bigint{"0xFEDCBA9876543210000000000000000"};
		EXPECT_EQ(x, hamon::bigint{"0xFEDCBA9876543210000000000008001"});
	}
}
