/**
 *	@file	unit_test_algorithm_is_unique.cpp
 *
 *	@brief	is_unique のテスト
 */

#include <hamon/algorithm/is_unique.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace is_unique_test
{

GTEST_TEST(AlgorithmTest, IsUniqueTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] { 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 };
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 2,5,3,1,2,4,2,1,4,3 };
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,1,2,2,2,3,3,4,4,5 };
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,2,3,4,5 };
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 15> a {{ 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 10> a {{ 2,5,3,1,2,4,2,1,4,3 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 10> a {{ 1,1,2,2,2,3,3,4,4,5 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{ 1,2,3,4,5 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a;
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1 };
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1, 1 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1, 2 };
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 1 };
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1, 1, 2 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 2 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 3, 4 };
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 3, 3 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 1, 2, 3, 1 };
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a), [](int x, int y){return x == y; }));
	}
	{
		std::list<float> a;
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::list<float> a { 1, 2, 3, 1, 2, 3 };
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::list<float> a { 1, 1, 2, 2, 3, 3 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::list<float> a { 1, 2, 3, 4, 3, 2, 1 };
		EXPECT_TRUE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::list<float> a { 1, 2, 3, 4, 4, 3, 2, 1 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::list<float> a { 3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,9,5,0,2,8,8 };
		EXPECT_FALSE(hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
}

}	// namespace is_unique_test

}	// namespace hamon_algorithm_test
