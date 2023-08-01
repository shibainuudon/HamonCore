/**
 *	@file	unit_test_bigint_and.cpp
 *
 *	@brief	operator&のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, AndTest)
{
	{
		auto x = hamon::bigint{0x35} & hamon::bigint{0xf0};
		EXPECT_EQ(x, 0x30);
	}
	{
		auto x = hamon::bigint{0x35} & hamon::bigint{0x0f};
		EXPECT_EQ(x, 0x05);
	}
	{
		auto x = hamon::bigint{0x0F} & hamon::bigint{0x12};
		EXPECT_EQ(x, 0x02);
	}
	{
		auto x = hamon::bigint{0x77} & hamon::bigint{0x20};
		EXPECT_EQ(x, 0x20);
	}
	{
		auto x = hamon::bigint{0x123456} & hamon::bigint{0xf00000};
		EXPECT_EQ(x, 0x100000);
	}
	{
		auto x = hamon::bigint{0x123456} & hamon::bigint{0x0f0000};
		EXPECT_EQ(x, 0x020000);
	}
	{
		auto x = hamon::bigint{0x123456} & hamon::bigint{0x00000f};
		EXPECT_EQ(x, 0x000006);
	}
	{
		auto x = hamon::bigint{0x123456} & hamon::bigint{0xf0f0f0};
		EXPECT_EQ(x, 0x103050);
	}
	{
		auto x = hamon::bigint{0x01} & hamon::bigint{"0x8000000000000000000000000000000"};
		EXPECT_EQ(x, 0);
	}
	{
		auto x =
			hamon::bigint{"0xF0FF00FFF000FFFF0000FFFFF00000FFF"} &
			hamon::bigint{"0x1234567890ABCDEF0123456789ABCDEF0"};
		EXPECT_EQ(x, hamon::bigint{"0x103400789000CDEF00004567800000EF0"});
	}
	{
		auto x = hamon::bigint{"0x1234000000000000000000000000000"} & hamon::bigint{0x123};
		EXPECT_EQ(x, 0);
	}
}
