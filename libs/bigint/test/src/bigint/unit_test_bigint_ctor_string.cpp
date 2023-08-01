/**
 *	@file	unit_test_bigint_ctor_string.cpp
 *
 *	@brief	文字列を引数に取るコンストラクタのテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>

GTEST_TEST(BigIntTest, CtorStringTest)
{
	{
		hamon::bigint x{""};
		EXPECT_EQ(x, 0);
	}
	{
		hamon::bigint x{"0"};
		EXPECT_EQ(x, 0);
	}
	{
		hamon::bigint x{"+0"};
		EXPECT_EQ(x, +0);
	}
	{
		hamon::bigint x{"-0"};
		EXPECT_EQ(x, -0);
	}
	{
		hamon::bigint x{"1"};
		EXPECT_EQ(x, 1);
	}
	{
		hamon::bigint x{"+1"};
		EXPECT_EQ(x, +1);
	}
	{
		hamon::bigint x{"-1"};
		EXPECT_EQ(x, -1);
	}
	{
		hamon::bigint x{"123"};
		EXPECT_EQ(x, 123);
	}
	{
		hamon::bigint x{"+123"};
		EXPECT_EQ(x, +123);
	}
	{
		hamon::bigint x{"-123"};
		EXPECT_EQ(x, -123);
	}
	{
		hamon::bigint x{"987654321"};
		EXPECT_EQ(x, 987654321);
	}
	{
		hamon::bigint x{"+987654321"};
		EXPECT_EQ(x, +987654321);
	}
	{
		hamon::bigint x{"-987654321"};
		EXPECT_EQ(x, -987654321);
	}

	// binary
	{
		hamon::bigint x{"0b1111011"};
//		EXPECT_EQ(x, 0b1111011);
		EXPECT_EQ(x, 123);
	}
	{
		hamon::bigint x{"-0B1111011"};
//		EXPECT_EQ(x, -0B1111011);
		EXPECT_EQ(x, -123);
	}

	// hex
	{
		hamon::bigint x{"0x0123456789ABCDEF"};
		EXPECT_EQ(x, 0x0123456789ABCDEF);
		EXPECT_EQ(x, 81985529216486895);
	}
	{
		hamon::bigint x{"0Xffffffff"};
		EXPECT_EQ(x, 0Xffffffff);
		EXPECT_EQ(x, 4294967295);
	}
	{
		hamon::bigint x{"-0x007f"};
		EXPECT_EQ(x, -0x007f);
		EXPECT_EQ(x, -127);
	}

	// oct
	{
		hamon::bigint x {"02322"};
		EXPECT_EQ(x, 02322);
		EXPECT_EQ(x, 1234);
	}
	{
		hamon::bigint x {"-02322"};
		EXPECT_EQ(x, -02322);
		EXPECT_EQ(x, -1234);
	}
}
