﻿/**
 *	@file	unit_test_utility_integer_sequence.cpp
 *
 *	@brief	integer_sequence のテスト
 */

#include <hamon/utility/integer_sequence.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace integer_sequence_test
{

void IntegerSequenceTestSub()
{
}

void IntegerSequenceTestSub(int a)
{
	EXPECT_EQ(20, a);
}

void IntegerSequenceTestSub(int a, int b, int c, int d, int e, int f)
{
	EXPECT_EQ(1, a);
	EXPECT_EQ(1, b);
	EXPECT_EQ(2, c);
	EXPECT_EQ(3, d);
	EXPECT_EQ(5, e);
	EXPECT_EQ(8, f);
}

template <typename T, T ... Seq>
void IntegerSequenceTest(hamon::integer_sequence<T, Seq ...>)
{
	IntegerSequenceTestSub(Seq...);
}

GTEST_TEST(UtilityTest, IntegerSequenceTest)
{
	{
		using seq = hamon::integer_sequence<int>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 0);
		IntegerSequenceTest(seq());
	}
	{
		using seq = hamon::integer_sequence<int, 20>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 1);
		IntegerSequenceTest(seq());
	}
	{
		using seq = hamon::integer_sequence<int, 1, 1, 2, 3, 5, 8>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 6);
		IntegerSequenceTest(seq());
	}
}

}	// namespace integer_sequence_test

}	// namespace hamon_utility_test
