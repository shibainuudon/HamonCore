/**
 *	@file	unit_test_bigint_add_equal.cpp
 *
 *	@brief	operator+=のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, AddEqualTest)
{
	hamon::bigint x{};
	EXPECT_EQ(x, 0);

	x += 0;
	EXPECT_EQ(x, 0);

	x += 1;
	EXPECT_EQ(x, 1);

	x += -2;
	EXPECT_EQ(x, -1);

	x += 12345;
	EXPECT_EQ(x, 12344);

	x += hamon::bigint{656};
	EXPECT_EQ(x, 13000);

	x += hamon::bigint{123456789};
	EXPECT_EQ(x, 123469789);

	x += x;
	EXPECT_EQ(x, 246939578);

	x += 0xffffffffffffffff;
	EXPECT_EQ(x.to_string(), "18446744073956491193");

	x += -x;
	EXPECT_EQ(x, 0);
}
