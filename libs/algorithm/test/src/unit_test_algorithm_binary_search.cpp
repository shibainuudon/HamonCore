/**
 *	@file	unit_test_algorithm_binary_search.cpp
 *
 *	@brief	binary_search のテスト
 */

#include <hamon/algorithm/binary_search.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace binary_search_test
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

GTEST_TEST(AlgorithmTest, BinarySearchTest)
{
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 1,2,3,4,5 };
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 4));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 5));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 6));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 1,1,2,3,3,3,4,4,5 };
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 1, pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 2, pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 3, pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 4, pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 5, pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0, pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 6, pred1));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int,5> a {{ 3,1,4,6,5 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 4));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 6));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int,5> a {{ 5,4,3,2,1 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 1, pred2()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 2, pred2()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 3, pred2()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 4, pred2()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 5, pred2()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0, pred2()));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 6, pred2()));
	}
	{
		const std::vector<int> a { 1,2,3,4,5 };
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 1, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 2, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 3, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 4, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 5, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 6, [](int x, int y) { return x < y; }));
	}
	{
		const std::list<int> a { 5,3,3,2,0 };
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 2, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 3, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 5, [](int x, int y) { return x > y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 1, [](int x, int y) { return x > y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 4, [](int x, int y) { return x > y; }));
	}
	{
		const std::vector<int> a;
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 1));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 2));
	}
	{
		const std::list<int> a;
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 1, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 2, [](int x, int y) { return x < y; }));
	}
}

}	// namespace binary_search_test

}	// namespace hamon_algorithm_test
