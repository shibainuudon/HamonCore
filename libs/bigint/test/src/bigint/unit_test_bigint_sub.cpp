/**
 *	@file	unit_test_bigint_sub.cpp
 *
 *	@brief	operator-のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, SubTest)
{
	{
		auto x = hamon::bigint{0} - hamon::bigint{0};
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint{1} - hamon::bigint{0};
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint{5} - hamon::bigint{2};
		EXPECT_EQ(x, 3);
	}
	{
		auto x = hamon::bigint{1000} - hamon::bigint{1};
		EXPECT_EQ(x, 999);
	}
	{
		auto x = hamon::bigint{1000} - hamon::bigint{999};
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint{1000} - hamon::bigint{1000};
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint{1000} - hamon::bigint{1001};
		EXPECT_EQ(x, -1);
	}
	{
		auto x = hamon::bigint( 2) - hamon::bigint( 5);
		EXPECT_EQ(x, -3);
	}
	{
		auto x = hamon::bigint( 2) - (-5);
		EXPECT_EQ(x, 7);
	}
	{
		auto x = -2 - hamon::bigint( 5);
		EXPECT_EQ(x, -7);
	}
	{
		auto x = hamon::bigint(-2) - hamon::bigint(-5);
		EXPECT_EQ(x, 3);
	}
	{
		auto x = hamon::bigint{256} - hamon::bigint{1};
		EXPECT_EQ(x, 255);
	}
	{
		auto x = hamon::bigint{0x10000} - hamon::bigint{1};
		EXPECT_EQ(x, 0xffff);
	}
	{
		auto x = hamon::bigint{0x1000000} - hamon::bigint{1};
		EXPECT_EQ(x, 0xffffff);
	}
	{
		auto x = hamon::bigint{0x1000000} - hamon::bigint{0xffffff};
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint{"8427663852327746832635939785432364562824"} -
			     hamon::bigint{"7567723894568827633575594573939298395955"};
		EXPECT_EQ(x, hamon::bigint{"859939957758919199060345211493066166869"});
	}
	{
		auto x = hamon::bigint{"4831358420296681146974351689067644777329"} -
			     hamon::bigint{"8250655382930189933211483422173351786903"};
		EXPECT_EQ(x, hamon::bigint{"-3419296962633508786237131733105707009574"});
	}
	{
		auto x = hamon::bigint{"0x1000000000000000000000000000000000000000000000"} -
			     hamon::bigint{1};
		EXPECT_EQ(x, hamon::bigint{"0xfffffffffffffffffffffffffffffffffffffffffffff"});
	}
}
