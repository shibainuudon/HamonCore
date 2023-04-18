/**
 *	@file	unit_test_tuple_tuple_rel_op_tuple_like.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class... TTypes, tuple-like UTuple>
 *	constexpr bool operator==(const tuple<TTypes...>& t, const UTuple& u);
 *
 *	template<class... TTypes, tuple-like UTuple>
 *	constexpr common_comparison_category_t<synth-three-way-result<TTypes, Elems>...>
 *	operator<=>(const tuple<TTypes...>& t, const UTuple& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/array.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace rel_op_tuple_like_test
{

GTEST_TEST(TupleTest, RelOpTupleLikeTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int> t1{1, 2};
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> t2{1, 2};
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> t3{0, 2};
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> t4{2, 1};
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> t5{1, 1};
		HAMON_CXX11_CONSTEXPR hamon::array<int, 2> t6{1, 3};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 == t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 == t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 == t3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 == t4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 == t5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 == t6));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 != t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 != t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 != t3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 != t4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 != t5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 != t6));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 < t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 < t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 < t3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 < t4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 < t5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 < t6));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 > t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 > t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 > t3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 > t4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 > t5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 > t6));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 <= t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 <= t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 <= t3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 <= t4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 <= t5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 <= t6));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 >= t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 >= t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 >= t3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 >= t4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 >= t5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 >= t6));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(t1 <=> t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(t1 <=> t2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(t1 <=> t3));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(t1 <=> t4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(t1 <=> t5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(t1 <=> t6));
#endif
	}
}

}	// namespace rel_op_tuple_like_test

}	// namespace hamon_tuple_test
