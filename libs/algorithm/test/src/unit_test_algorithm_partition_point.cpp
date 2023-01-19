/**
 *	@file	unit_test_algorithm_partition_point.cpp
 *
 *	@brief	partition_point のテスト
 */

#include <hamon/algorithm/partition_point.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace partition_point_test
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

GTEST_TEST(AlgorithmTest, PartitionPointTest)
{
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 4,2,3,1,5};
		HAMON_CXX14_CONSTEXPR auto ret = hamon::partition_point(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 5,7,3,1 };
		HAMON_CXX14_CONSTEXPR auto ret = hamon::partition_point(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::begin(a));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 8,2,0,4,2 };
		HAMON_CXX14_CONSTEXPR auto ret = hamon::partition_point(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR const std::array<int, 5> a {{ 5,3,4,1,2 }};
		HAMON_CXX17_CONSTEXPR auto ret = hamon::partition_point(hamon::begin(a), hamon::end(a), pred2());
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
	}
	{
		const std::vector<int> a { 5,3,1,4,2 };
		auto ret = hamon::partition_point(hamon::begin(a), hamon::end(a), [](int x){ return (x % 2) == 1; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
	}
	{
		const std::list<int> a { 1,5,3,2,4 };
		auto ret = hamon::partition_point(hamon::begin(a), hamon::end(a), [](int x){ return x < 2; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
	}
	{
		const std::vector<int> a;
		auto ret = hamon::partition_point(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
	{
		const std::list<int> a;
		auto ret = hamon::partition_point(hamon::begin(a), hamon::end(a), pred2());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
}

}	// namespace partition_point_test

}	// namespace hamon_algorithm_test
