/**
 *	@file	unit_test_bigint_sub_equal.cpp
 *
 *	@brief	operator-=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, SubEqualTest)
{
	hamon::bigint x = 9630;
	EXPECT_EQ(x, 9630);

	x -= 0;
	EXPECT_EQ(x, 9630);

	x -= 5248;
	EXPECT_EQ(x, 4382);

	x -= hamon::bigint{3758};
	EXPECT_EQ(x, 624);

	x -= 623;
	EXPECT_EQ(x, 1);

	x -= 2;
	EXPECT_EQ(x, -1);

	x -= hamon::bigint{12};
	EXPECT_EQ(x, -13);

	x -= -30;
	EXPECT_EQ(x, 17);

	x -= hamon::bigint(45);
	EXPECT_EQ(x, -28);

	x -= 0xffffffffffffffff;
	EXPECT_EQ(x.to_string(), "-18446744073709551643");

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
	x -= x;
	EXPECT_EQ(x, 0);
HAMON_WARNING_POP()

	x -= 3;
	EXPECT_EQ(x, -3);
}
