/**
 *	@file	unit_test_algorithm_search_n.cpp
 *
 *	@brief	search_n のテスト
 */

#include <hamon/algorithm/search_n.hpp>
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

namespace search_n_test
{

GTEST_TEST(AlgorithmTest, SearchNTest)
{
	{
		HAMON_STATIC_CONSTEXPR const int a[] = { 1,2,3,2,1,3,3,2,3,3,1 };
		HAMON_CXX14_CONSTEXPR const auto it =
			hamon::search_n(hamon::begin(a), hamon::end(a), 0, 3);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a));
	}
	{
		HAMON_STATIC_CONSTEXPR const std::array<int, 11> a = {{ 1,2,3,2,1,3,3,2,3,3,1 }};
		HAMON_CXX17_CONSTEXPR const auto it =
			hamon::search_n(hamon::begin(a), hamon::end(a), 1, 3);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 2));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] = { 1,2,3,2,1,3,3,2,3,3,1 };
		HAMON_CXX14_CONSTEXPR const auto it =
			hamon::search_n(hamon::begin(a), hamon::end(a), 2, 3);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 5));
	}
	{
		HAMON_STATIC_CONSTEXPR const std::array<int, 11> a = {{ 1,2,3,2,1,3,3,2,3,3,1 }};
		HAMON_CXX17_CONSTEXPR const auto it =
			hamon::search_n(hamon::begin(a), hamon::end(a), 3, 3);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const std::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 1, 2);
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
	}
	{
		const std::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, 2);
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 3));
	}
	{
		const std::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, 2);
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 6));
	}
	{
		const std::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, 2, [](int x, int y) { return x <= y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 3));
	}
	{
		const std::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, 2, [](int x, int y) { return x >= y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
	}
	{
		const std::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 0, 5);
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 0));
	}
	{
		const std::vector<int> a;
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, 3);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const std::list<int> a;
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, 3);
		EXPECT_TRUE(it == hamon::begin(a));
	}
}

}	// namespace search_n_test

}	// namespace hamon_algorithm_test
