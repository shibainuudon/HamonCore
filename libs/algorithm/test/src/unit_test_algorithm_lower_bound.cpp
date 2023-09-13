/**
 *	@file	unit_test_algorithm_lower_bound.cpp
 *
 *	@brief	lower_bound のテスト
 */

#include <hamon/algorithm/lower_bound.hpp>
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

namespace lower_bound_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int x, int y) const
	{
		return x < y;
	}
};

GTEST_TEST(AlgorithmTest, LowerBoundTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,2,3,4,5 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 3);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,1,2,2,2,3,3 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 2);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,1,2,2,2,3,3 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 3);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 5));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] { 1,3,5,6,7,9 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 7, pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 5> a {{ 3,1,4,6,5 }};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 4);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 3> a {{ 10,20,30 }};
		HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 10, pred2());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
	{
		const hamon::vector<int> a { 1,3,5,8,13,17,25 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 10);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));
	}
	{
		const hamon::vector<int> a { 1,3,5,8,13,17,25 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 1, [](int x, int y) { return x < y; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
	{
		const std::list<int> a { 5,1,25,13,17 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 10);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
	}
	{
		const hamon::vector<int> a;
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 0);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
	{
		const std::list<int> a;
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x < y; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
}

}	// namespace lower_bound_test

}	// namespace hamon_algorithm_test
