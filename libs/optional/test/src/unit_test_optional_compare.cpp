/**
 *	@file	unit_test_optional_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T, class U> constexpr bool operator==(const optional<T>& x, const optional<U>& y);
 *
 *	template<class T, class U> constexpr bool operator!=(const optional<T>& x, const optional<U>& y);
 *
 *	template<class T, class U> constexpr bool operator<(const optional<T>& x, const optional<U>& y);
 *
 *	template<class T, class U> constexpr bool operator>(const optional<T>& x, const optional<U>& y);
 *
 *	template<class T, class U> constexpr bool operator<=(const optional<T>& x, const optional<U>& y);
 *
 *	template<class T, class U> constexpr bool operator>=(const optional<T>& x, const optional<U>& y);
 *
 *	template<class T, three_way_comparable_with<T> U>
 *	constexpr compare_three_way_result_t<T, U>
 *	operator<=>(const optional<T>& x, const optional<U>& y);
 */

#include <hamon/optional.hpp>
#include <hamon/compare.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace compare_test
{

GTEST_TEST(OptionalTest, CompareTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 == o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 != o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 <  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 >  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 <= o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 >= o2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1 = 42;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 == o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 != o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 <  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 >  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 <= o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 >= o2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2 = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 == o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 != o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 <  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 >  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 <= o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 >= o2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1 = 43;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2 = 43;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 == o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 != o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 <  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 >  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 <= o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 >= o2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1 = 44;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2 = 43;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 == o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 != o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 <  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 >  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 <= o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 >= o2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1 = 43;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2 = 45;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 == o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 != o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 <  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 >  o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (o1 <= o2);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(o1 >= o2);
	}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(o1 <=> o2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1 = 42;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(o1 <=> o2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2 = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(o1 <=> o2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1 = 43;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2 = 43;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(o1 <=> o2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1 = 44;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2 = 43;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(o1 <=> o2));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::optional<int>  o1 = 43;
		HAMON_CXX11_CONSTEXPR hamon::optional<long> o2 = 45;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(o1 <=> o2));
	}
#endif
}

}	// namespace compare_test

}	// namespace hamon_optional_test
