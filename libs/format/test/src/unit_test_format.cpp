/**
 *	@file	unit_test_format.cpp
 *
 *	@brief	format のテスト
 */

#include <hamon/format.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>

GTEST_TEST(FormatTest, OverviewTest)
{
	{
		char c = 120;
		EXPECT_EQ(hamon::format("{:6}", 42),    "    42");
		EXPECT_EQ(hamon::format("{:6}", 'x'),   "x     ");
		EXPECT_EQ(hamon::format("{:*<6}", 'x'), "x*****");
		EXPECT_EQ(hamon::format("{:*>6}", 'x'), "*****x");
		EXPECT_EQ(hamon::format("{:*^6}", 'x'), "**x***");
		EXPECT_EQ(hamon::format("{:6d}", c),    "   120");
		EXPECT_EQ(hamon::format("{:6}", true),  "true  ");
	}
	{
		double inf = hamon::numeric_limits<double>::infinity();
		double nan = hamon::numeric_limits<double>::quiet_NaN();
		EXPECT_EQ(hamon::format("{0:},{0:+},{0:-},{0: }", 1),   "1,+1,1, 1");
		EXPECT_EQ(hamon::format("{0:},{0:+},{0:-},{0: }", -1),  "-1,-1,-1,-1");
		EXPECT_EQ(hamon::format("{0:},{0:+},{0:-},{0: }", inf), "inf,+inf,inf, inf");
		EXPECT_EQ(hamon::format("{0:},{0:+},{0:-},{0: }", nan), "nan,+nan,nan, nan");
	}
	{
		char c = 120;
		EXPECT_EQ(hamon::format("{:+06d}", c),   "+00120");
		EXPECT_EQ(hamon::format("{:#06x}", 0xa), "0x000a");
		EXPECT_EQ(hamon::format("{:<06}", -42),  "-42   ");
	}
	{
		EXPECT_EQ(hamon::format("{}", 42),                      "42");
		EXPECT_EQ(hamon::format("{0:b} {0:d} {0:o} {0:x}", 42), "101010 42 52 2a");
		EXPECT_EQ(hamon::format("{0:#x} {0:#X}", 42),           "0x2a 0X2A");
//		EXPECT_EQ(hamon::format("{:L}", 1234.5678),             "1,234.5678"); // (ロケールによる)
	}
	{
		EXPECT_EQ(hamon::format("0. {}", "hello"), "0. hello");
//		EXPECT_EQ(hamon::format("1. {:?}", "hello"), "1. \"hello\"");	// C++23
		EXPECT_EQ(hamon::format("2. {}", "hello\nworld"), "2. hello\nworld");
//		EXPECT_EQ(hamon::format("3. {:?}", "hello\nworld"), "3. \"hello\\nworld\"");	// C++23
	}
}
