/**
 *	@file	unit_test_bigint_div.cpp
 *
 *	@brief	operator/のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, DivTest)
{
	{
		auto x = hamon::bigint( 6) / hamon::bigint( 1);
		EXPECT_EQ(x, 6);
	}
	{
		auto x = hamon::bigint( 6) / hamon::bigint( 2);
		EXPECT_EQ(x, 3);
	}
	{
		auto x = hamon::bigint( 6) / hamon::bigint( 3);
		EXPECT_EQ(x, 2);
	}
	{
		auto x = hamon::bigint( 6) / hamon::bigint(-3);
		EXPECT_EQ(x, -2);
	}
	{
		auto x = hamon::bigint(-6) / hamon::bigint( 3);
		EXPECT_EQ(x, -2);
	}
	{
		auto x = hamon::bigint(-6) / hamon::bigint(-3);
		EXPECT_EQ(x, 2);
	}
	{
		auto x = hamon::bigint( 6) / hamon::bigint( 4);
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint( 6) / hamon::bigint( 6);
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint( 6) / hamon::bigint( 7);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint{0x10000} / hamon::bigint{2};
		EXPECT_EQ(x, 0x8000);
	}
	{
		auto x = hamon::bigint{0xffff} / hamon::bigint{2};
		EXPECT_EQ(x, 0x7fff);
	}
	{
		auto x = hamon::bigint{999999} / hamon::bigint{7777};
		EXPECT_EQ(x, 128);
	}
	{
		auto x = hamon::bigint{999999999} / hamon::bigint{999999};
		EXPECT_EQ(x, 1000);
	}
	{
		auto x = hamon::bigint{"8634445089577309591046007474873433396354"} /
			-hamon::bigint{"9509431914"};
		EXPECT_EQ(x, hamon::bigint{"-907987476819249835058654742987"});
	}
	{
		auto x = -hamon::bigint{"1310755439459119173246996027623904894831"} /
			hamon::bigint{"84526411745918709879"};
		EXPECT_EQ(x, hamon::bigint{"-15507051729572655735"});
	}
	{
		auto x = -hamon::bigint{"38533568648101411188584683464222001686976831106787"} /
			-hamon::bigint{"504164348379621718380998627378"};
		EXPECT_EQ(x, hamon::bigint{"76430570253425985552"});
	}
}
