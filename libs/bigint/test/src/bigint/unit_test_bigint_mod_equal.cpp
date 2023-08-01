/**
 *	@file	unit_test_bigint_mod_equal.cpp
 *
 *	@brief	operator%=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, ModEqualTest)
{
	{
		auto x = hamon::bigint{12345};
		EXPECT_EQ(x, 12345);

		x %= hamon::bigint(678);
		EXPECT_EQ(x, 141);

		x %= hamon::bigint{13};
		EXPECT_EQ(x, 11);

		x %= hamon::bigint(20);
		EXPECT_EQ(x, 11);

		x %= hamon::bigint{11};
		EXPECT_EQ(x, 0);

		x %= hamon::bigint(1);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint(-51);
		EXPECT_EQ(x, -51);

		x %= hamon::bigint{13};
		EXPECT_EQ(x, -12);

		x %= -7;
		EXPECT_EQ(x, -5);

		x %= hamon::bigint{5};
		EXPECT_EQ(x, 0);
	}
	{
		hamon::bigint x{0xffff};
		EXPECT_EQ(x, 0xffff);

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
		x %= x;
		EXPECT_EQ(x, 0);
HAMON_WARNING_POP()
	}
}
