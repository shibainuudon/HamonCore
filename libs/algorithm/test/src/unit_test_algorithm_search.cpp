/**
 *	@file	unit_test_algorithm_search.cpp
 *
 *	@brief	search のテスト
 */

#include <hamon/algorithm/search.hpp>
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

namespace search_test
{

GTEST_TEST(AlgorithmTest, SearchTest)
{
	{
		HAMON_STATIC_CONSTEXPR const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		HAMON_STATIC_CONSTEXPR const int b[] = { 1,2,3,4 };

		HAMON_CXX14_CONSTEXPR const auto it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 0));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		HAMON_STATIC_CONSTEXPR const int b[] = { 1,2,4 };

		HAMON_CXX14_CONSTEXPR const auto it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		HAMON_STATIC_CONSTEXPR const hamon::array<int, 3> b = {{ 1,2,3 }};

		HAMON_CXX14_CONSTEXPR const auto it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::next(hamon::begin(a), 0));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		HAMON_STATIC_CONSTEXPR const hamon::array<int, 3> b = {{ 1,2,3 }};
		
		HAMON_CXX14_CONSTEXPR const auto it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::begin(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a));
	}
	{
		const hamon::vector<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 2,3 };

		auto const it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			[](int x, int y){return x == y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
	}
	{
		const std::list<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 3,4 };

		auto const it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 2));
	}
	{
		const hamon::array<int, 10> a = {{ 1,2,3,4,1,2,3,1,2,1 }};
		const std::list<int> b = { 3,1,2 };

		auto const it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			[](int x, int y){return x == y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 6));
	}
	{
		const std::list<int> a {1,2,3};
		const hamon::vector<int> b;

		auto const it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(it == hamon::begin(a));
	}
	{
		const std::list<int> a;
		const hamon::vector<int> b {1,2,3};

		auto const it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const std::list<int> a;
		const hamon::vector<int> b;

		auto const it = hamon::search(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(it == hamon::begin(a));
	}
}

}	// namespace search_test

}	// namespace hamon_algorithm_test
