﻿/**
 *	@file	unit_test_numeric_lcm.cpp
 *
 *	@brief	lcm のテスト
 */

#include <hamon/numeric/lcm.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(NumericTest, LcmTest)
{
#define HAMON_LCM_TEST(x, m, n)			\
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(x, hamon::lcm( m,  n));	\
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(x, hamon::lcm( m, -n));	\
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(x, hamon::lcm(-m,  n));	\
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(x, hamon::lcm(-m, -n))

	HAMON_LCM_TEST( 0, 0, 0);
	HAMON_LCM_TEST( 0, 0, 1);
	HAMON_LCM_TEST( 0, 0, 2);
	HAMON_LCM_TEST( 0, 0, 3);
	HAMON_LCM_TEST( 0, 0, 4);
	HAMON_LCM_TEST( 0, 0, 5);
	HAMON_LCM_TEST( 0, 0, 6);
	HAMON_LCM_TEST( 0, 0, 7);
	HAMON_LCM_TEST( 0, 0, 8);
	HAMON_LCM_TEST( 0, 0, 9);
	HAMON_LCM_TEST( 0, 0,10);

	HAMON_LCM_TEST( 0, 1, 0);
	HAMON_LCM_TEST( 1, 1, 1);
	HAMON_LCM_TEST( 2, 1, 2);
	HAMON_LCM_TEST( 3, 1, 3);
	HAMON_LCM_TEST( 4, 1, 4);
	HAMON_LCM_TEST( 5, 1, 5);
	HAMON_LCM_TEST( 6, 1, 6);
	HAMON_LCM_TEST( 7, 1, 7);
	HAMON_LCM_TEST( 8, 1, 8);
	HAMON_LCM_TEST( 9, 1, 9);
	HAMON_LCM_TEST(10, 1,10);
	
	HAMON_LCM_TEST( 0, 2, 0);
	HAMON_LCM_TEST( 2, 2, 1);
	HAMON_LCM_TEST( 2, 2, 2);
	HAMON_LCM_TEST( 6, 2, 3);
	HAMON_LCM_TEST( 4, 2, 4);
	HAMON_LCM_TEST(10, 2, 5);
	HAMON_LCM_TEST( 6, 2, 6);
	HAMON_LCM_TEST(14, 2, 7);
	HAMON_LCM_TEST( 8, 2, 8);
	HAMON_LCM_TEST(18, 2, 9);
	HAMON_LCM_TEST(10, 2,10);

	HAMON_LCM_TEST( 0, 3, 0);
	HAMON_LCM_TEST( 3, 3, 1);
	HAMON_LCM_TEST( 6, 3, 2);
	HAMON_LCM_TEST( 3, 3, 3);
	HAMON_LCM_TEST(12, 3, 4);
	HAMON_LCM_TEST(15, 3, 5);
	HAMON_LCM_TEST( 6, 3, 6);
	HAMON_LCM_TEST(21, 3, 7);
	HAMON_LCM_TEST(24, 3, 8);
	HAMON_LCM_TEST( 9, 3, 9);
	HAMON_LCM_TEST(30, 3,10);

	HAMON_LCM_TEST( 0, 4, 0);
	HAMON_LCM_TEST( 4, 4, 1);
	HAMON_LCM_TEST( 4, 4, 2);
	HAMON_LCM_TEST(12, 4, 3);
	HAMON_LCM_TEST( 4, 4, 4);
	HAMON_LCM_TEST(20, 4, 5);
	HAMON_LCM_TEST(12, 4, 6);
	HAMON_LCM_TEST(28, 4, 7);
	HAMON_LCM_TEST( 8, 4, 8);
	HAMON_LCM_TEST(36, 4, 9);
	HAMON_LCM_TEST(20, 4,10);

	HAMON_LCM_TEST( 0, 5, 0);
	HAMON_LCM_TEST( 5, 5, 1);
	HAMON_LCM_TEST(10, 5, 2);
	HAMON_LCM_TEST(15, 5, 3);
	HAMON_LCM_TEST(20, 5, 4);
	HAMON_LCM_TEST( 5, 5, 5);
	HAMON_LCM_TEST(30, 5, 6);
	HAMON_LCM_TEST(35, 5, 7);
	HAMON_LCM_TEST(40, 5, 8);
	HAMON_LCM_TEST(45, 5, 9);
	HAMON_LCM_TEST(10, 5,10);

	HAMON_LCM_TEST( 0, 6, 0);
	HAMON_LCM_TEST( 6, 6, 1);
	HAMON_LCM_TEST( 6, 6, 2);
	HAMON_LCM_TEST( 6, 6, 3);
	HAMON_LCM_TEST(12, 6, 4);
	HAMON_LCM_TEST(30, 6, 5);
	HAMON_LCM_TEST( 6, 6, 6);
	HAMON_LCM_TEST(42, 6, 7);
	HAMON_LCM_TEST(24, 6, 8);
	HAMON_LCM_TEST(18, 6, 9);
	HAMON_LCM_TEST(30, 6,10);

	HAMON_LCM_TEST( 0, 7, 0);
	HAMON_LCM_TEST( 7, 7, 1);
	HAMON_LCM_TEST(14, 7, 2);
	HAMON_LCM_TEST(21, 7, 3);
	HAMON_LCM_TEST(28, 7, 4);
	HAMON_LCM_TEST(35, 7, 5);
	HAMON_LCM_TEST(42, 7, 6);
	HAMON_LCM_TEST( 7, 7, 7);
	HAMON_LCM_TEST(56, 7, 8);
	HAMON_LCM_TEST(63, 7, 9);
	HAMON_LCM_TEST(70, 7,10);

	HAMON_LCM_TEST( 0, 8, 0);
	HAMON_LCM_TEST( 8, 8, 1);
	HAMON_LCM_TEST( 8, 8, 2);
	HAMON_LCM_TEST(24, 8, 3);
	HAMON_LCM_TEST( 8, 8, 4);
	HAMON_LCM_TEST(40, 8, 5);
	HAMON_LCM_TEST(24, 8, 6);
	HAMON_LCM_TEST(56, 8, 7);
	HAMON_LCM_TEST( 8, 8, 8);
	HAMON_LCM_TEST(72, 8, 9);
	HAMON_LCM_TEST(40, 8,10);

	HAMON_LCM_TEST( 0, 9, 0);
	HAMON_LCM_TEST( 9, 9, 1);
	HAMON_LCM_TEST(18, 9, 2);
	HAMON_LCM_TEST( 9, 9, 3);
	HAMON_LCM_TEST(36, 9, 4);
	HAMON_LCM_TEST(45, 9, 5);
	HAMON_LCM_TEST(18, 9, 6);
	HAMON_LCM_TEST(63, 9, 7);
	HAMON_LCM_TEST(72, 9, 8);
	HAMON_LCM_TEST( 9, 9, 9);
	HAMON_LCM_TEST(90, 9,10);

	HAMON_LCM_TEST(  0, 60,  0);
	HAMON_LCM_TEST( 60, 60,  1);
	HAMON_LCM_TEST( 60, 60,  2);
	HAMON_LCM_TEST( 60, 60,  3);
	HAMON_LCM_TEST( 60, 60,  4);
	HAMON_LCM_TEST( 60, 60,  5);
	HAMON_LCM_TEST( 60, 60,  6);
	HAMON_LCM_TEST(420, 60,  7);
	HAMON_LCM_TEST(120, 60,  8);
	HAMON_LCM_TEST(180, 60,  9);
	HAMON_LCM_TEST( 60, 60, 10);
	HAMON_LCM_TEST(660, 60, 11);
	HAMON_LCM_TEST( 60, 60, 12);
	HAMON_LCM_TEST(780, 60, 13);
	HAMON_LCM_TEST(420, 60, 14);
	HAMON_LCM_TEST( 60, 60, 15);

#undef HAMON_LCM_TEST
}
