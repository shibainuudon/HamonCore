﻿/**
 *	@file	unit_test_cstring_memcmp.cpp
 *
 *	@brief	memcmpのテスト
 */

#include <hamon/cstring/memcmp.hpp>
#include <gtest/gtest.h>

GTEST_TEST(CStringTest, MemCmpTest)
{
	const int a1[] = { 0, 1, 2, 3 };
	const int a2[] = { 0, 1, 2, 3 };
	const int a3[] = { 1, 1, 2, 3 };
	const int a4[] = { 0, 1, 2, 0 };
	const int a5[] = { 0, 1, 2, 3, 4 };

	EXPECT_TRUE (hamon::memcmp(a1, a1, sizeof(a1)) == 0);
	EXPECT_TRUE (hamon::memcmp(a1, a2, sizeof(a1)) == 0);
	EXPECT_FALSE(hamon::memcmp(a1, a3, sizeof(a1)) > 0);
	EXPECT_FALSE(hamon::memcmp(a1, a4, sizeof(a1)) < 0);
	EXPECT_TRUE (hamon::memcmp(a1, a5, sizeof(a1)) == 0);
}
