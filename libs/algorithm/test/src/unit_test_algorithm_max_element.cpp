/**
 *	@file	unit_test_algorithm_max_element.cpp
 *
 *	@brief	max_element のテスト
 */

#include <hamon/algorithm/max_element.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace max_element_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x > y;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int x, int y) const
	{
		return hamon::abs(x) < hamon::abs(y);
	}
};

GTEST_TEST(AlgorithmTest, MaxElementTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a[] { 3, 1, -4, 1, 5, -9 };

		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::max_element(hamon::begin(a), hamon::end(a));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::max_element(hamon::begin(a), hamon::end(a), pred1);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 5));
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::max_element(hamon::begin(a), hamon::end(a), pred2());
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 5));
		}
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 8> a {{ 2, -6, 5, -3, -5, 8, 9, 7 }};

		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::max_element(hamon::begin(a), hamon::end(a));
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 6));
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::max_element(hamon::begin(a), hamon::end(a), pred1);
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
		}
		{
			HAMON_CXX14_CONSTEXPR_OR_CONST auto ret = hamon::max_element(hamon::begin(a), hamon::end(a), pred2());
			HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 6));
		}
	}
	{
		const hamon::vector<int> a { 9, 3, 2, 3, 8, 4, 6 };

		{
			auto ret = hamon::max_element(hamon::begin(a), hamon::end(a));
			EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
		}
		{
			auto ret = hamon::max_element(hamon::begin(a), hamon::end(a), pred1);
			EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		}
		{
			auto ret = hamon::max_element(hamon::begin(a), hamon::end(a), [](int x, int y){return x > y; });
			EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		}
	}
	{
		const std::list<int> a { 1, -5, 7, 3, 7, -5 };

		{
			auto ret = hamon::max_element(hamon::begin(a), hamon::end(a));
			EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		}
		{
			auto ret = hamon::max_element(hamon::begin(a), hamon::end(a), pred2());
			EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		}
		{
			auto ret = hamon::max_element(hamon::begin(a), hamon::end(a), [](int x, int y){return x > y; });
			EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
		}
	}
}

}	// namespace max_element_test

}	// namespace hamon_algorithm_test
