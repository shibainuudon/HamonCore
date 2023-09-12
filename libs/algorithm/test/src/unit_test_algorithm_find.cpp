/**
 *	@file	unit_test_algorithm_find.cpp
 *
 *	@brief	find のテスト
 */

#include <hamon/algorithm/find.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace find_test
{

GTEST_TEST(AlgorithmTest, FindTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] {0,1,2};
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 0);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a));
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 1);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a) + 1);
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 2);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a) + 2);
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 3);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
		}
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<float, 8> a{{3, 4, 4, 5, 5, 5, 3, 6}};
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 3.0f);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a));
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 4.0f);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a) + 1);
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 5.0f);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a) + 3);
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 6.0f);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a) + 7);
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find(hamon::begin(a), hamon::end(a), 0.0f);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
		}
	}
	{
		int a[] {0,1,2};
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 0);
			EXPECT_TRUE(it == hamon::begin(a));
			*it = 10;
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 2);
			EXPECT_TRUE(it == hamon::begin(a) + 2);
			*it = 20;
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 3);
			EXPECT_TRUE(it == hamon::end(a));
		}
		EXPECT_EQ(10, a[0]);
		EXPECT_EQ( 1, a[1]);
		EXPECT_EQ(20, a[2]);
	}
	{
		const std::vector<int> a {7, 8, 9};
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 7);
			EXPECT_TRUE(it == hamon::begin(a));
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 8);
			EXPECT_TRUE(it == hamon::begin(a) + 1);
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 9);
			EXPECT_TRUE(it == hamon::begin(a) + 2);
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 10);
			EXPECT_TRUE(it == hamon::end(a));
		}
	}
	{
		const std::list<int> a {0,1,2};
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 0);
			EXPECT_TRUE(it == hamon::begin(a));
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 1);
			EXPECT_TRUE(it == ++hamon::begin(a));
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 2);
			EXPECT_TRUE(it == ++(++hamon::begin(a)));
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), -1);
			EXPECT_TRUE(it == hamon::end(a));
		}
	}
	{
		std::list<int> a {0,1,2};
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 1);
			EXPECT_TRUE(it == ++hamon::begin(a));
			*it = 30;
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 3);
			EXPECT_TRUE(it == hamon::end(a));
		}
		{
			auto it = a.begin();
			EXPECT_EQ( 0, *it++);
			EXPECT_EQ(30, *it++);
			EXPECT_EQ( 2, *it++);
		}
	}
}

}	// namespace find_test

}	// namespace hamon_algorithm_test
