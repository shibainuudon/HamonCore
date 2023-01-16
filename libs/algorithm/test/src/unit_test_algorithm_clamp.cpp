/**
 *	@file	unit_test_algorithm_clamp.cpp
 *
 *	@brief	clamp のテスト
 */

#include <hamon/algorithm/clamp.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace clamp_test
{

HAMON_CXX11_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	template <typename T>
	HAMON_CXX11_CONSTEXPR bool operator()(T x, T y) const
	{
		return x > y;
	}
};

GTEST_TEST(AlgorithmTest, AdjacentFindTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::clamp(0, 1, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::clamp(1, 1, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::clamp(2, 1, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::clamp(3, 1, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::clamp(4, 1, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::clamp(5, 1, 5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::clamp(6, 1, 5));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::clamp(-2.5, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::clamp(-2.0, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::clamp(-1.5, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0, hamon::clamp(-1.0, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::clamp(-0.5, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::clamp( 0.0, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::clamp( 0.5, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::clamp( 1.0, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::clamp( 1.5, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0, hamon::clamp( 2.0, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::clamp( 2.5, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::clamp( 3.0, -1.5, 2.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::clamp( 3.5, -1.5, 2.5));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::clamp(0, 1, 5, pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::clamp(1, 1, 5, pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, hamon::clamp(2, 1, 5, pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::clamp(3, 1, 5, pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::clamp(4, 1, 5, pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::clamp(5, 1, 5, pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::clamp(6, 1, 5, pred1));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::clamp(-2.5, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::clamp(-2.0, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::clamp(-1.5, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0, hamon::clamp(-1.0, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::clamp(-0.5, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::clamp( 0.0, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::clamp( 0.5, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::clamp( 1.0, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::clamp( 1.5, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0, hamon::clamp( 2.0, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::clamp( 2.5, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::clamp( 3.0, 2.5, -1.5, pred2()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::clamp( 3.5, 2.5, -1.5, pred2()));
}

}	// namespace clamp_test

}	// namespace hamon_algorithm_test
