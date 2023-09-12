/**
 *	@file	unit_test_algorithm_is_sorted_until.cpp
 *
 *	@brief	is_sorted_until のテスト
 */

#include <hamon/algorithm/is_sorted_until.hpp>
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

namespace is_sorted_until_test
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

GTEST_TEST(AlgorithmTest, IsSortedUntilTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,4,5};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), pred2());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {5,4,3,2,1};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), pred2());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {1,2,3,3,4,5};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {3,1,4,2,5};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] {1};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{1,2,3,5,4}};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 4));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{1,1,3,4,2}};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 4));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 6> a {{3,5,6,8,10,13}};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 6> a {{13,10,8,6,4,1}};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), pred2());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 1> a {{3}};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const std::vector<int> a {3,4,5};
		auto const it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const std::vector<int> a {3,3,4,4,5,5};
		auto const it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), [] (int x, int y) { return x < y; });
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const std::vector<int> a {3,3,4,4,5,5};
		auto const it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), [] (int x, int y) { return x > y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 2));
	}
	{
		const std::vector<int> a;
		auto const it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const std::list<int> a {5,5,4,4,3,3};
		auto const it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 2));
	}
	{
		const std::list<int> a {5,5,4,4,3,3};
		auto const it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), [] (int x, int y) { return x < y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 2));
	}
	{
		const std::list<int> a {5,5,4,4,3,3};
		auto const it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), [] (int x, int y) { return x > y; });
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const std::list<int> a;
		auto const it = hamon::is_sorted_until(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(it == hamon::end(a));
	}
}

}	// namespace is_sorted_until_test

}	// namespace hamon_algorithm_test
