/**
 *	@file	unit_test_bigint_xor.cpp
 *
 *	@brief	operator^のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, XorTest)
{
	{
		auto x = hamon::bigint{0xFA} ^ hamon::bigint{0x47};
		EXPECT_EQ(x, 0xBD);
	}
	{
		auto x = hamon::bigint{0x35} ^ hamon::bigint{0xf0};
		EXPECT_EQ(x, 0xC5);
	}
	{
		auto x = hamon::bigint{0x73} ^ hamon::bigint{0x20};
		EXPECT_EQ(x, 0x53);
	}
	{
		auto x =
			hamon::bigint{"0x123456789ABCDEF0123456789ABCDEF"} ^
			hamon::bigint{"0xFFFF0000FFFFF00000FF00F0F0FFF00"};
		EXPECT_EQ(x, hamon::bigint{"0x0edcb567865432ef012cb56886a432ef"});
	}
	{
		auto x =
			hamon::bigint{"0x123456789ABCDEF0123456789ABCDEF"} ^
			hamon::bigint{"0x123456789ABCDEF0123456789ABCDEF"};
		EXPECT_EQ(x, 0);
	}
}
