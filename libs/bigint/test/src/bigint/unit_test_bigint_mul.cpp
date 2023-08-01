/**
 *	@file	unit_test_bigint_mul.cpp
 *
 *	@brief	operator*のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, MulTest)
{
	{
		auto x = hamon::bigint(2) * hamon::bigint(3);
		EXPECT_EQ(x, 6);
	}
	{
		auto x = hamon::bigint(2) * -3;
		EXPECT_EQ(x, -6);
	}
	{
		auto x = -2 * hamon::bigint(3);
		EXPECT_EQ(x, -6);
	}
	{
		auto x = hamon::bigint(-2) * hamon::bigint(-3);
		EXPECT_EQ(x, 6);
	}
	{
		auto x = hamon::bigint(-3) * hamon::bigint( 0);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint( 3) * hamon::bigint( 0);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint( 0) * hamon::bigint( 256);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint( 0) * hamon::bigint(-256);
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint{3} * hamon::bigint{4} * hamon::bigint{5};
		EXPECT_EQ(x, 60);
	}
	{
		auto x = hamon::bigint{123} * hamon::bigint{0};
		EXPECT_EQ(x, 0);
	}
	{
		auto x = hamon::bigint{4824} * hamon::bigint{31};
		EXPECT_EQ(x, 149544);
	}
	{
		auto x = hamon::bigint{"49380"} *
			hamon::bigint{"315921325115052764877243681807"};
		EXPECT_EQ(x, hamon::bigint{"15600195034181305529638293007629660"});
	}
	{
		auto x = hamon::bigint{"36968175473499613142"} *
			hamon::bigint{"190512936091683569991370045758"};
		EXPECT_EQ(x, hamon::bigint{"7042915651408975798024456175730948594979838151636"});
	}
	{
		auto x = -hamon::bigint{"36968175473499613142"} *
			hamon::bigint{"190512936091683569991370045758"};
		EXPECT_EQ(x, hamon::bigint{"-7042915651408975798024456175730948594979838151636"});
	}
	{
		auto x = hamon::bigint{"36968175473499613142"} *
			-hamon::bigint{"190512936091683569991370045758"};
		EXPECT_EQ(x, hamon::bigint{"-7042915651408975798024456175730948594979838151636"});
	}
}
