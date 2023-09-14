/**
 *	@file	unit_test_algorithm_stable_partition.cpp
 *
 *	@brief	stable_partition のテスト
 */

#include <hamon/algorithm/stable_partition.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_algorithm_test
{

namespace stable_partition_test
{

HAMON_CONSTEXPR bool pred1(int x)
{
	return (x % 2) == 0;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int x) const
	{
		return x > 2;
	}
};

GTEST_TEST(AlgorithmTest, StablePartitionTest)
{
	{
		int a[] {1,2,3,4,5};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(5, a[4]);
	}
	{
		int a[] {1,3,5,7};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(7, a[3]);
	}
	{
		int a[] {2,4,6};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::end(a));
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(6, a[2]);
	}
	{
		hamon::array<int, 5> a {{1,2,3,4,5}};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred2());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
	}
	{
		hamon::vector<int> a {1,2,3,4,5};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), [](int x) { return (x % 2) == 1; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(4, a[4]);
	}
	{
		hamon::list<int> a {1,2,3,4,5};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), [](int x) { return x < 3; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		auto it = a.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		hamon::vector<int> a;
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
	{
		hamon::list<int> a;
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred2());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
}

}	// namespace stable_partition_test

}	// namespace hamon_algorithm_test
