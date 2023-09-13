/**
 *	@file	unit_test_algorithm_includes.cpp
 *
 *	@brief	includes のテスト
 */

#include <hamon/algorithm/includes.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace includes_test
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

GTEST_TEST(AlgorithmTest, IncludesTest)
{
	{
		HAMON_STATIC_CONSTEXPR int                  a[] {1,2,3,4,5,6};
		HAMON_STATIC_CONSTEXPR int                  b[] {0,1,3};
		HAMON_STATIC_CONSTEXPR hamon::array<int, 3> c  {{1,2,4}};
		HAMON_STATIC_CONSTEXPR int                  d[] {2,4,6};
		HAMON_STATIC_CONSTEXPR hamon::array<int, 3> e  {{3,5,7}};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b)));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c)));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c), pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(d), hamon::end(d)));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(e), hamon::end(e)));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a  {{10,20,30,40,50}};
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> b  {{10,20,30,40,50}};
		HAMON_STATIC_CONSTEXPR int                  c[] {10,15,20};
		HAMON_STATIC_CONSTEXPR hamon::array<int, 2> d  {{ 9,10}};
		HAMON_STATIC_CONSTEXPR int                  e[] {51};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b)));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c)));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c), pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(d), hamon::end(d)));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(e), hamon::end(e)));
	}
	{
		const hamon::vector<int>   a   {9,8,7,6,5};
		const int                  b[] {9,7,5};
		const hamon::array<int, 3> c {{10,9,8}};
		const hamon::vector<int>   d   {9,5,4};
		const std::list<int>       e   {8,7,6};
		EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), pred2()));
		EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c), pred2()));
		EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(d), hamon::end(d), pred2()));
		EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(e), hamon::end(e), pred2()));
	}
	{
		const std::list<int>       a   {90,80,70,60,50};
		const int                  b[] {90,70,50};
		const hamon::array<int, 3> c  {{91,90,88}};
		const hamon::vector<int>   d   {80,75,70};
		const std::list<int>       e   {80,70,50};
		EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), [](int x, int y){ return x > y; }));
		EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c), [](int x, int y){ return x > y; }));
		EXPECT_FALSE(hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(d), hamon::end(d), [](int x, int y){ return x > y; }));
		EXPECT_TRUE (hamon::includes(hamon::begin(a), hamon::end(a), hamon::begin(e), hamon::end(e), [](int x, int y){ return x > y; }));
	}
}

}	// namespace includes_test

}	// namespace hamon_algorithm_test
