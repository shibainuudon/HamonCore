/**
 *	@file	unit_test_algorithm_is_partitioned.cpp
 *
 *	@brief	is_partitioned のテスト
 */

#include <hamon/algorithm/is_partitioned.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace is_partitioned_test
{

HAMON_CONSTEXPR bool pred1(int x)
{
	return (x % 2) == 0;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int x) const
	{
		return x > 3;
	}
};

GTEST_TEST(AlgorithmTest, IsPartitionedTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,4,5,6,7,8,9};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {2,4,6,8,1,3,5,7,9};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {3,3,3};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {4,4,4};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{4,2,3,1,5}};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{4,2,3,1,5}};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 3> a {{1,2,3}};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		const hamon::vector<int> a {1,2,3};
		EXPECT_FALSE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		const hamon::vector<int> a {1,3,2};
		EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), [](int x) { return (x % 2) == 1; }));
	}
	{
		const hamon::vector<int> a {1,2,3};
		EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		const hamon::vector<int> a {1,3,2};
		EXPECT_FALSE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), [](int x) { return x > 2; }));
	}
	{
		const std::list<int> a {1,2,3};
		EXPECT_FALSE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		const std::list<int> a {1,3,2};
		EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), [](int x) { return (x % 2) == 1; }));
	}
	{
		const std::list<int> a {1,2,3};
		EXPECT_TRUE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		const std::list<int> a {1,3,2};
		EXPECT_FALSE(hamon::is_partitioned(hamon::begin(a), hamon::end(a), [](int x) { return x > 2; }));
	}
}

}	// namespace is_partitioned_test

}	// namespace hamon_algorithm_test
