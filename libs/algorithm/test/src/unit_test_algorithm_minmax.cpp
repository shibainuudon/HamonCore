/**
 *	@file	unit_test_algorithm_minmax.cpp
 *
 *	@brief	minmax のテスト
 */

#include <hamon/algorithm/minmax.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/cmath/abs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace minmax_test
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

GTEST_TEST(AlgorithmTest, MinmaxTest)
{
	{
		HAMON_CXX14_STATIC_CONSTEXPR int a = 2;
		HAMON_CXX14_STATIC_CONSTEXPR int b = 3;
		HAMON_CXX14_STATIC_CONSTEXPR auto ret = hamon::minmax(a, b);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, ret.first);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, ret.second);
	}
	{
		HAMON_CXX14_STATIC_CONSTEXPR int a = 4;
		HAMON_CXX14_STATIC_CONSTEXPR int b = 3;
		HAMON_CXX14_STATIC_CONSTEXPR auto ret = hamon::minmax(a, b);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, ret.first);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, ret.second);
	}
	{
		HAMON_CXX14_STATIC_CONSTEXPR int a = 2;
		HAMON_CXX14_STATIC_CONSTEXPR int b = 3;
		HAMON_CXX14_STATIC_CONSTEXPR auto ret = hamon::minmax(a, b, pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, ret.first);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, ret.second);
	}
	{
		HAMON_CXX14_STATIC_CONSTEXPR int a = 2;
		HAMON_CXX14_STATIC_CONSTEXPR int b = -3;
		HAMON_CXX14_STATIC_CONSTEXPR auto ret = hamon::minmax(a, b);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(-3, ret.first);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 2, ret.second);
	}
	{
		HAMON_CXX14_STATIC_CONSTEXPR int a = 2;
		HAMON_CXX14_STATIC_CONSTEXPR int b = -3;
		HAMON_CXX14_STATIC_CONSTEXPR auto ret = hamon::minmax(a, b, pred2());
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 2, ret.first);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(-3, ret.second);
	}

	{
		auto ret = hamon::minmax({1, 2, 3});
		EXPECT_EQ( 1, ret.first);
		EXPECT_EQ( 3, ret.second);
	}
	{
		auto ret = hamon::minmax({4, -2, 3});
		EXPECT_EQ(-2, ret.first);
		EXPECT_EQ( 4, ret.second);
	}
	{
		auto ret = hamon::minmax({1, 2, 3}, [](int x, int y) { return x > y; });
		EXPECT_EQ( 3, ret.first);
		EXPECT_EQ( 1, ret.second);
	}
	{
		auto ret = hamon::minmax({1, 4, 2, 0, 3}, [](int x, int y) { return x > y; });
		EXPECT_EQ( 4, ret.first);
		EXPECT_EQ( 0, ret.second);
	}
}

}	// namespace minmax_test

}	// namespace hamon_algorithm_test
