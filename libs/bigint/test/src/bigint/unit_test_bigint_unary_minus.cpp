/**
 *	@file	unit_test_bigint_unary_minus.cpp
 *
 *	@brief	operator- のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, UnaryMinusTest)
{
	EXPECT_TRUE(-hamon::bigint{0} == 0);
	EXPECT_TRUE(-hamon::bigint{1} == -1);
	EXPECT_TRUE(-hamon::bigint{2} == -2);
	EXPECT_TRUE(-hamon::bigint(-1) == 1);
	EXPECT_TRUE(-hamon::bigint(-2) == 2);
	EXPECT_TRUE(-hamon::bigint{"12345678901234567890"} == hamon::bigint{"-12345678901234567890"});
	EXPECT_TRUE(-hamon::bigint{"-12345678901234567890"} == hamon::bigint{"12345678901234567890"});
}
