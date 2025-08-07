/**
 *	@file	unit_test_format_format.cpp
 *
 *	@brief	format のテスト
 */

#include <hamon/format/format.hpp>
#include <gtest/gtest.h>

GTEST_TEST(FormatTest, FormatTest)
{
	auto s = hamon::format("The answer is {}.", 42);
	EXPECT_EQ("The answer is 42.", s);
}
