/**
 *	@file	unit_test_cstring_memmove.cpp
 *
 *	@brief	memmoveのテスト
 */

#include <hamon/cstring/memmove.hpp>
#include <gtest/gtest.h>

GTEST_TEST(CStringTest, MemMoveTest)
{
	int a1[] = { 0, 1, 2, 3, 4, 5, };

	auto p = hamon::memmove(&a1[0], &a1[2], sizeof(int) * 3);

	EXPECT_EQ(2, a1[0]);
	EXPECT_EQ(3, a1[1]);
	EXPECT_EQ(4, a1[2]);
	EXPECT_EQ(3, a1[3]);
	EXPECT_EQ(4, a1[4]);
	EXPECT_EQ(5, a1[5]);

	EXPECT_EQ(p, a1);
}
