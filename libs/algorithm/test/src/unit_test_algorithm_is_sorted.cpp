/**
 *	@file	unit_test_algorithm_is_sorted.cpp
 *
 *	@brief	is_sorted のテスト
 */

#include <hamon/algorithm/is_sorted.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace is_sorted_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int x, int y) const
	{
		return x > y;
	}
};

GTEST_TEST(AlgorithmTest, IsSortedTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {5,4,3,2,1};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,3,4,5};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {3,1,4,2,5};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {1};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{1,2,3,5,4}};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{1,1,3,4,2}};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 6> a {{3,5,6,8,10,13}};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 6> a {{13,10,8,6,4,1}};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a), pred2()));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 1> a {{3}};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		const std::vector<int> a {3,4,5};
		EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		const std::vector<int> a {3,3,4,4,5,5};
		EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a), [] (int x, int y) { return x < y; }));
	}
	{
		const std::vector<int> a {3,3,4,4,5,5};
		EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a), [] (int x, int y) { return x > y; }));
	}
	{
		const std::vector<int> a;
		EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		const std::list<int> a {5,5,4,4,3,3};
		EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
	}
	{
		const std::list<int> a {5,5,4,4,3,3};
		EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a), [] (int x, int y) { return x < y; }));
	}
	{
		const std::list<int> a {5,5,4,4,3,3};
		EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a), [] (int x, int y) { return x > y; }));
	}
	{
		const std::list<int> a;
		EXPECT_TRUE(hamon::is_sorted(hamon::begin(a), hamon::end(a), pred1));
	}
}

}	// namespace is_sorted_test

}	// namespace hamon_algorithm_test
