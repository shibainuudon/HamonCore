﻿/**
 *	@file	unit_test_algorithm_fill.cpp
 *
 *	@brief	fill のテスト
 */

#include <hamon/algorithm/fill.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace fill_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool FillTestArray()
{
	{
		int a[3]{};
		hamon::fill(std::begin(a), std::end(a), 42);
		VERIFY(42 == a[0]);
		VERIFY(42 == a[1]);
		VERIFY(42 == a[2]);
	}
	{
		int a[5]{};
		hamon::fill(a, a + 4, 1);
		VERIFY(1 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(1 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(0 == a[4]);
	}

	return true;
}

inline HAMON_CXX17_CONSTEXPR bool FillTestStdArray()
{
	{
		std::array<int, 4> a{ { 1, 2, 3, 4 } };
		hamon::fill(std::begin(a), std::end(a), -1);
		VERIFY(-1 == a[0]);
		VERIFY(-1 == a[1]);
		VERIFY(-1 == a[2]);
		VERIFY(-1 == a[3]);
	}

	return true;
}

GTEST_TEST(AlgorithmTest, FillTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FillTestArray());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(FillTestStdArray());

	{
		std::vector<int> a(5);
		hamon::fill(std::begin(a), std::end(a), 3);
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(3, a[4]);
	}
	{
		std::vector<int> a;
		hamon::fill(std::begin(a), std::end(a), 3);
		EXPECT_TRUE(a.empty());
	}
	{
		std::list<int> a(3);
		hamon::fill(std::begin(a), std::end(a), 4);
		auto it = a.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::list<int> a;
		hamon::fill(std::begin(a), std::end(a), 0);
		EXPECT_TRUE(a.empty());
	}
}

#undef VERIFY

}	// namespace fill_test

}	// namespace hamon_algorithm_test