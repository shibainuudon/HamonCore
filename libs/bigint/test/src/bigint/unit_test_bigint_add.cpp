/**
 *	@file	unit_test_bigint_add.cpp
 *
 *	@brief	operator+のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, AddTest)
{
	{
		auto x = hamon::bigint{0} + hamon::bigint{0};
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint{1} + hamon::bigint{0};
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint{2} + hamon::bigint{3};
		EXPECT_EQ(x, 5);
	}
	{
		auto x = hamon::bigint{2} + (-3);
		EXPECT_EQ(x, -1);
	}
	{
		auto x = (-2) + hamon::bigint{3};
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint(-2) + hamon::bigint(-3);
		EXPECT_EQ(x, -5);
	}
	{
		auto x = hamon::bigint{1} + hamon::bigint{999};
		EXPECT_EQ(x, 1000);
	}
	{
		auto x = (-10) + hamon::bigint{1000};
		EXPECT_EQ(x, 990);
	}
	{
		auto x = hamon::bigint{255} + hamon::bigint{1};
		EXPECT_EQ(x, 256);
	}
	{
		auto x = hamon::bigint{256} + (-1);
		EXPECT_EQ(x, 255);
	}
	{
		auto x = hamon::bigint{255} + hamon::bigint{255};
		EXPECT_EQ(x, 510);
	}
	{
		auto x = hamon::bigint{255} + hamon::bigint{256};
		EXPECT_EQ(x, 511);
	}
	{
		auto x = hamon::bigint{0xffff} + hamon::bigint{1};
		EXPECT_EQ(x, 0x10000);
	}
	{
		auto x = hamon::bigint{1} + hamon::bigint{0xffffff};
		EXPECT_EQ(x, 0x1000000);
	}
	{
		auto x = hamon::bigint{0xffffffff} + hamon::bigint{0xffffffff};
		EXPECT_EQ(x, 0x1fffffffe);
	}
	{
		auto x = hamon::bigint{"3565257399734975859457283787877529836964"} +
			     hamon::bigint{"7966969762968552357477389456772596794377"};
		EXPECT_EQ(x, hamon::bigint{"11532227162703528216934673244650126631341"});
	}
	{
		auto x = hamon::bigint{"3565257399734975859457283787877529836964"} +
			     hamon::bigint{"-7966969762968552357477389456772596794377"};
		EXPECT_EQ(x, hamon::bigint{"-4401712363233576498020105668895066957413"});
	}
	{
		auto x = hamon::bigint{"9999999999999999999999999999999999999999999999999"} +
			     hamon::bigint{1};
		EXPECT_EQ(x, hamon::bigint{"10000000000000000000000000000000000000000000000000"});
	}
}
