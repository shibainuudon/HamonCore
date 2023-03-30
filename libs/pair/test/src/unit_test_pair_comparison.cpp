/**
 *	@file	unit_test_pair_comparison.cpp
 *
 *	@brief	比較演算子のテスト
 * 
 *	template<class T1, class T2, class U1, class U2>
 *	constexpr bool operator==(const pair<T1, T2>& x, const pair<U1, U2>& y);
 *	
 *	template<class T1, class T2, class U1, class U2>
 *	constexpr common_comparison_category_t<
 *		synth-three-way-result<T1, U1>,
 *		synth-three-way-result<T2, U2>>
 *	operator<=>(const pair<T1, T2>& x, const pair<U1, U2>& y);
 */

#include <hamon/pair.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace comparison_test
{

GTEST_TEST(PairTest, ComparisonTest)
{
	HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p1{1, 2};
	HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p2{1, 2};
	HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p3{0, 2};
	HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p4{2, 1};
	HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p5{1, 1};
	HAMON_CXX11_CONSTEXPR hamon::pair<int, int> p6{1, 3};

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 == p1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 == p2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 == p3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 == p4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 == p5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 == p6));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 != p1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 != p2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 != p3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 != p4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 != p5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 != p6));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 < p1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 < p2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 < p3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 < p4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 < p5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 < p6));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 > p1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 > p2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 > p3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 > p4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 > p5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 > p6));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 <= p1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 <= p2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 <= p3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 <= p4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 <= p5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 <= p6));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 >= p1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 >= p2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 >= p3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 >= p4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (p1 >= p5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(p1 >= p6));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(p1 <=> p1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(p1 <=> p2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(p1 <=> p3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(p1 <=> p4));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(p1 <=> p5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(p1 <=> p6));
#endif
}

}	// namespace comparison_test

}	// namespace hamon_pair_test
