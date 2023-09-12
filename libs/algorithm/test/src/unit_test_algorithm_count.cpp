/**
 *	@file	unit_test_algorithm_count.cpp
 *
 *	@brief	count のテスト
 */

#include <hamon/algorithm/count.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace count_test
{

GTEST_TEST(AlgorithmTest, CountTest)
{
	{
		HAMON_CONSTEXPR_OR_CONST int a[] {1, 3, 1, 2, 3, 1, 2, 2, 1};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(0, hamon::count(hamon::begin(a), hamon::end(a), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, hamon::count(hamon::begin(a), hamon::end(a), 1));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, hamon::count(hamon::begin(a), hamon::end(a), 2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::count(hamon::begin(a), hamon::end(a), 3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(0, hamon::count(hamon::begin(a), hamon::end(a), 4));
	}
	{
		HAMON_CONSTEXPR_OR_CONST hamon::array<int, 21> a{ { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6 } };
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(0, hamon::count(hamon::begin(a), hamon::end(a), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::count(hamon::begin(a), hamon::end(a), 1));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::count(hamon::begin(a), hamon::end(a), 2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, hamon::count(hamon::begin(a), hamon::end(a), 3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::count(hamon::begin(a), hamon::end(a), 4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, hamon::count(hamon::begin(a), hamon::end(a), 5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::count(hamon::begin(a), hamon::end(a), 6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(1, hamon::count(hamon::begin(a), hamon::end(a), 7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::count(hamon::begin(a), hamon::end(a), 8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, hamon::count(hamon::begin(a), hamon::end(a), 9));
	}
	{
		const std::vector<int> v{10, 20, 10, 30, 10, 20};
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v),  0));
		EXPECT_EQ(3, hamon::count(hamon::begin(v), hamon::end(v), 10));
		EXPECT_EQ(2, hamon::count(hamon::begin(v), hamon::end(v), 20));
		EXPECT_EQ(1, hamon::count(hamon::begin(v), hamon::end(v), 30));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 40));
	}
	{
		const std::vector<int> v;
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v),  0));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 10));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 20));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 30));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 40));
	}
	{
		const std::list<int> l{10, 20, 40, 40, 10};
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l),  0));
		EXPECT_EQ(2, hamon::count(hamon::begin(l), hamon::end(l), 10));
		EXPECT_EQ(1, hamon::count(hamon::begin(l), hamon::end(l), 20));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 30));
		EXPECT_EQ(2, hamon::count(hamon::begin(l), hamon::end(l), 40));
	}
	{
		const std::list<int> l;
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l),  0));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 10));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 20));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 30));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 40));
	}
}

}	// namespace count_test

}	// namespace hamon_algorithm_test
