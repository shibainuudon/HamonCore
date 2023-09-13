/**
 *	@file	unit_test_algorithm_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 */

#include <hamon/algorithm/equal_range.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace equal_range_test
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

GTEST_TEST(AlgorithmTest, EqualRangeTest)
{
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 1,2,2,3,3,3,4,4,5,5,5 };
		{
			HAMON_CXX14_CONSTEXPR auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 1);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 0));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 1));
		}
		{
			HAMON_CXX14_CONSTEXPR auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 3, pred1);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 3));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 6));
		}
		{
			HAMON_CXX14_CONSTEXPR auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 5);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 8));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 11));
		}
		{
			HAMON_CXX14_CONSTEXPR auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 0);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 0));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 0));
		}
		{
			HAMON_CXX14_CONSTEXPR auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 10);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == hamon::end(a));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == hamon::end(a));
		}
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 9> a {{ 5,5,4,2,2,2,1,0,0 }};
		{
			HAMON_CXX14_CONSTEXPR auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 2, pred2());
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 3));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 6));
		}
		{
			HAMON_CXX14_CONSTEXPR auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), -1, pred2());
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == hamon::end(a));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == hamon::end(a));
		}
		{
			HAMON_CXX14_CONSTEXPR auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 6, pred2());
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == hamon::begin(a));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == hamon::begin(a));
		}
	}
	{
		// ソートされていなくても区分化されていれば良い
		const hamon::vector<int> a { 2,1,2,3,3,4,7,5,5 };
		{
			auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 3);
			EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 3));
			EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 5));
		}
	}
	{
		const std::list<int> a { 8, 6, 6, 7, 5, 5, 5, 3, 4, 2, 2 };
		{
			auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 5, [] (int x, int y) { return x > y; });
			EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 4));
			EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 7));
		}
	}
	{
		const hamon::vector<int> a;
		{
			auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 0);
			EXPECT_TRUE(ret.first  == hamon::begin(a));
			EXPECT_TRUE(ret.second == hamon::end(a));
		}
	}
	{
		const std::list<int> a;
		{
			auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 0, pred1);
			EXPECT_TRUE(ret.first  == hamon::begin(a));
			EXPECT_TRUE(ret.second == hamon::end(a));
		}
	}
}

}	// namespace equal_range_test

}	// namespace hamon_algorithm_test
