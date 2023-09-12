/**
 *	@file	unit_test_algorithm_inplace_merge.cpp
 *
 *	@brief	inplace_merge のテスト
 */

#include <hamon/algorithm/inplace_merge.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace hamon_algorithm_test
{

namespace inplace_merge_test
{

GTEST_TEST(AlgorithmTest, InplaceMergeTest)
{
	{
		int a[] { 1,4,5,  2,3,6 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 3, hamon::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(6, a[5]);
	}
	{
		int a[] { 5,4,1,  6,3,2 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 3, hamon::end(a), hamon::greater<>());

		EXPECT_EQ(6, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(1, a[5]);
	}
	{
		int a[] { 1, 2, 3 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a), hamon::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
	}
	{
		int a[] { 3, 2, 1 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a), hamon::end(a), hamon::greater<>());

		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(1, a[2]);
	}
	{
		hamon::array<int, 10> a {{ 1,2,5,7,  2,2,3,3,5,6 }};

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 4, hamon::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(3, a[5]);
		EXPECT_EQ(5, a[6]);
		EXPECT_EQ(5, a[7]);
		EXPECT_EQ(6, a[8]);
		EXPECT_EQ(7, a[9]);
	}
	{
		hamon::array<int, 10> a {{ 7,5,2,1,  6,5,3,3,2,2 }};

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 4, hamon::end(a), hamon::greater<>());

		EXPECT_EQ(7, a[0]);
		EXPECT_EQ(6, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(5, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(3, a[5]);
		EXPECT_EQ(2, a[6]);
		EXPECT_EQ(2, a[7]);
		EXPECT_EQ(2, a[8]);
		EXPECT_EQ(1, a[9]);
	}
	{
		hamon::array<int, 2> a {{ 3, 1 }};

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 1, hamon::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
	}
	{
		hamon::array<int, 2> a {{ 1, 3 }};

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 1, hamon::end(a), hamon::greater<>());

		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(1, a[1]);
	}
	{
		std::vector<int> a { 1,2,4,5,6,  3 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 5, hamon::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(6, a[5]);
	}
	{
		std::vector<int> a { 6,5,4,2,1,  3 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 5, hamon::end(a), hamon::greater<>());

		EXPECT_EQ(6, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(1, a[5]);
	}
	{
		std::vector<int> a;

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a), hamon::end(a));

		EXPECT_TRUE(a.empty());
	}
}

}	// namespace inplace_merge_test

}	// namespace hamon_algorithm_test
