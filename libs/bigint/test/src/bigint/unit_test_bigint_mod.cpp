/**
 *	@file	unit_test_bigint_mod.cpp
 *
 *	@brief	operator%のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, ModTest)
{
	{
		auto x = hamon::bigint( 6) % hamon::bigint( 3);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint(-6) % hamon::bigint( 3);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint( 6) % hamon::bigint(-3);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint(-6) % hamon::bigint(-3);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint( 7) % hamon::bigint( 3);
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint(-7) % hamon::bigint( 3);
		EXPECT_EQ(x, -1);
	}
	{
		auto x = hamon::bigint( 7) % hamon::bigint(-3);
		EXPECT_EQ(x, 1);
	}
	{
		auto x = hamon::bigint(-7) % hamon::bigint(-3);
		EXPECT_EQ(x, -1);
	}
	{
		auto x = hamon::bigint{123} % hamon::bigint{4};
		EXPECT_EQ(x, 3);
	}
	{
		auto x = hamon::bigint{"517232794887556900325139264240"} %
			     hamon::bigint{"97854840192602714242"};
		EXPECT_EQ(x, hamon::bigint{"20300968082335090596"});
	}
	{
		auto x = hamon::bigint{"8480533256755492072837759593696251541964"} %
			     hamon::bigint{"80317560221046790777589885826979837"};
		EXPECT_EQ(x, hamon::bigint{"43025695824575004376318882931492645"});
	}
}
