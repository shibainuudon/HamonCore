/**
 *	@file	unit_test_algorithm_sort.cpp
 *
 *	@brief	sort のテスト
 */

#include <hamon/algorithm/sort.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace hamon_algorithm_test
{

namespace sort_test
{

GTEST_TEST(AlgorithmTest, SortTest)
{
	{
		int a[] { 3, 1, 4 };
		hamon::sort(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(4, a[2]);
	}
	{
		int a[] { 3, 1, 4 };
		hamon::sort(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
	}
	{
		hamon::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		hamon::sort(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(9, a[5]);
	}
	{
		hamon::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		hamon::sort(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(1, a[5]);
	}
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		hamon::sort(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
	}
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		hamon::sort(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(1, a[4]);
	}
	{
		std::vector<int> a;
		hamon::sort(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace sort_test

}	// namespace hamon_algorithm_test
