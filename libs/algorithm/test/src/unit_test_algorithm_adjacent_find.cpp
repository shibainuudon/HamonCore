/**
 *	@file	unit_test_algorithm_adjacent_find.cpp
 *
 *	@brief	adjacent_find のテスト
 */

#include <hamon/algorithm/adjacent_find.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace adjacent_find_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int x, int y) const
	{
		return x >= y;
	}
};

GTEST_TEST(AlgorithmTest, AdjacentFindTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,4,3,3,1,2,2 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::adjacent_find(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 2));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 3> a {{ 1,1,1 }};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::adjacent_find(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 0));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,4,3,5,3,1,2 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::adjacent_find(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 9> a {{ 9,8,5,3,2,1,3,4,5 }};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::adjacent_find(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 5));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,2,3,4,3,2,5 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::adjacent_find(hamon::begin(a), hamon::end(a), pred2());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 3));
	}
	{
		const hamon::vector<int> a;
		auto const it = hamon::adjacent_find(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const hamon::vector<int> a {1,1,2,2,3,3};
		auto const it = hamon::adjacent_find(hamon::begin(a), hamon::end(a), [](int x, int y) { return x != y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
	}
	{
		const hamon::list<int> a;
		auto const it = hamon::adjacent_find(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const hamon::list<int> a {1,2,2,3,7,7,5,4,3};
		auto const it = hamon::adjacent_find(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 5));
	}
}

}	// namespace adjacent_find_test

}	// namespace hamon_algorithm_test
