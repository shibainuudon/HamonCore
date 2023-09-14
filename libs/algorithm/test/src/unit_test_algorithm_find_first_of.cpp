/**
 *	@file	unit_test_algorithm_find_first_of.cpp
 *
 *	@brief	find_first_of のテスト
 */

#include <hamon/algorithm/find_first_of.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace find_first_of_test
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

GTEST_TEST(AlgorithmTest, FindFirstOfTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1, 3, 7, 4, 2 };
		HAMON_STATIC_CONSTEXPR int b[] { 2, 4, 6, 8 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(it, hamon::next(hamon::begin(a), 3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, *it);
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1, 3, 7, 4, 2 };
		HAMON_STATIC_CONSTEXPR int b[] { 2, 4, 6, 8 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(it, hamon::next(hamon::begin(a), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(1, *it);
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1, 3, 7, 4, 2 };
		HAMON_STATIC_CONSTEXPR int b[] { 2, 4, 6, 8 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), pred2());
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(it, hamon::next(hamon::begin(a), 1));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, *it);
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1, 3, 7, 4, 2 };
		HAMON_STATIC_CONSTEXPR hamon::array<int, 2> b {{ 6, 8 }};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(it, hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{ 1, 3, 5, 7, 9 }};
		HAMON_STATIC_CONSTEXPR int b[] { 3, 1 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(it, hamon::next(hamon::begin(a), 0));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(1, *it);
	}
	{
		const hamon::vector<int> a { 1, 3, 7, 4, 2 };
		const hamon::list<int> b { 2, 4, 6, 8 };
		auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_EQ(it, hamon::next(hamon::begin(a), 3));
		EXPECT_EQ(4, *it);
	}
	{
		const hamon::list<int> a { 1, 3, 7, 4, 2 };
		const int b[] { 2, 4, 6, 8 };
		auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), pred1);
		EXPECT_EQ(it, hamon::next(hamon::begin(a), 0));
		EXPECT_EQ(1, *it);
	}
	{
		const int a[] { 1, 3, 7, 4, 2 };
		const hamon::vector<int> b { 2, 4, 6, 8 };
		auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), pred2());
		EXPECT_EQ(it, hamon::next(hamon::begin(a), 1));
		EXPECT_EQ(3, *it);
	}
	{
		const hamon::list<int> a {1,2,3,4,5,6,7};
		const hamon::list<int> b {5};
		auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), [](int x, int y) { return x > y; });
		EXPECT_EQ(it, hamon::next(hamon::begin(a), 5));
		EXPECT_EQ(6, *it);
	}
	{
		const hamon::list<int> a { 1, 3, 7, 4, 2 };
		const hamon::vector<int> b;
		auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_EQ(it, hamon::end(a));
	}
	{
		const hamon::vector<int> a;
		const hamon::list<int> b { 2, 4, 6, 8 };
		auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_EQ(it, hamon::end(a));
	}
	{
		const hamon::list<int> a;
		const hamon::list<int> b;
		auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_EQ(it, hamon::end(a));
	}
	{
		const hamon::list<int> a;
		const hamon::list<int> b;
		auto it = hamon::find_first_of(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), [](int , int ){ return true; });
		EXPECT_EQ(it, hamon::end(a));
	}
}

}	// namespace find_first_of_test

}	// namespace hamon_algorithm_test
