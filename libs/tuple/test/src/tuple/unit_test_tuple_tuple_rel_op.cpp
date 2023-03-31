/**
 *	@file	unit_test_tuple_tuple_rel_op.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class... TTypes, class... UTypes>
 *	constexpr bool operator==(const tuple<TTypes...>& t, const tuple<UTypes...>& u);
 *
 *	template<class... TTypes, class... UTypes>
 *	constexpr common_comparison_category_t<synth-three-way-result<TTypes, UTypes>...>
 *	operator<=>(const tuple<TTypes...>& t, const tuple<UTypes...>& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace rel_op_test
{

GTEST_TEST(TupleTest, RelOpTest)
{
	{
		hamon::tuple<int, char, std::string> t1(1, 'a', "hello");
		hamon::tuple<int, char, const char*> t2(1, 'a', "hello");
		hamon::tuple<int, char, std::string> t3(1, 'a', "hellot");
		hamon::tuple<int, char, std::string> t4(0, 'a', "hello");

		EXPECT_TRUE( (t1 == t1));
		EXPECT_TRUE( (t1 == t2));
		EXPECT_TRUE(!(t1 == t3));
		EXPECT_TRUE(!(t1 == t4));

		EXPECT_TRUE(!(t1 != t1));
		EXPECT_TRUE(!(t1 != t2));
		EXPECT_TRUE( (t1 != t3));
		EXPECT_TRUE( (t1 != t4));

		EXPECT_TRUE(!(t1 < t1));
		EXPECT_TRUE(!(t1 < t2));
		EXPECT_TRUE( (t1 < t3));
		EXPECT_TRUE(!(t1 < t4));

		EXPECT_TRUE(!(t1 > t1));
		EXPECT_TRUE(!(t1 > t2));
		EXPECT_TRUE(!(t1 > t3));
		EXPECT_TRUE( (t1 > t4));

		EXPECT_TRUE( (t1 <= t1));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE( (t1 <= t3));
		EXPECT_TRUE(!(t1 <= t4));

		EXPECT_TRUE( (t1 >= t1));
		EXPECT_TRUE( (t1 >= t2));
		EXPECT_TRUE(!(t1 >= t3));
		EXPECT_TRUE( (t1 >= t4));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int> t1{1, 2};
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int> t2{1, 2};
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int> t3{0, 2};
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int> t4{2, 1};
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int> t5{1, 1};
		HAMON_CXX11_CONSTEXPR hamon::tuple<int, int> t6{1, 3};

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
	{
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t1{};
		HAMON_CXX11_CONSTEXPR hamon::tuple<> t2{};

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 == t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 == t2));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 != t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 != t2));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 < t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 < t2));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 > t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(t1 > t2));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 <= t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 <= t2));

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 >= t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (t1 >= t2));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(t1 <=> t1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(t1 <=> t2));
#endif
	}
}

}	// namespace rel_op_test

}	// namespace hamon_tuple_test
