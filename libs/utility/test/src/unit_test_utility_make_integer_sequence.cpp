﻿/**
 *	@file	unit_test_utility_make_integer_sequence.cpp
 *
 *	@brief	make_integer_sequence のテスト
 */

#include <hamon/utility/make_integer_sequence.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace make_integer_sequence_test
{

void MakeIntegerSequenceTestSub(void)
{
}

void MakeIntegerSequenceTestSub(int a)
{
	EXPECT_EQ(0, a);
}

void MakeIntegerSequenceTestSub(
	int a,
	int b,
	int c,
	int d,
	int e,
	int f,
	int g,
	int h,
	int i,
	int j)
{
	EXPECT_EQ(0, a);
	EXPECT_EQ(1, b);
	EXPECT_EQ(2, c);
	EXPECT_EQ(3, d);
	EXPECT_EQ(4, e);
	EXPECT_EQ(5, f);
	EXPECT_EQ(6, g);
	EXPECT_EQ(7, h);
	EXPECT_EQ(8, i);
	EXPECT_EQ(9, j);
}

template <typename T, T ... Seq>
void MakeIntegerSequenceTest(hamon::integer_sequence<T, Seq ...>)
{
	MakeIntegerSequenceTestSub(Seq...);
}

GTEST_TEST(UtilityTest, MakeIntegerSequenceTest)
{
	{
		using seq = hamon::make_integer_sequence<int, 0>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 0);
		MakeIntegerSequenceTest(seq());
	}
	{
		using seq = hamon::make_integer_sequence<int, 1>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 1);
		MakeIntegerSequenceTest(seq());
	}
	{
		using seq = hamon::make_integer_sequence<int, 10>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 10);
		MakeIntegerSequenceTest(seq());
	}
	{
		using seq = hamon::make_integer_sequence<int, 100>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 100);
	}
}

}	// namespace make_integer_sequence_test

}	// namespace hamon_utility_test
