/**
 *	@file	unit_test_cmath_isgreater.cpp
 *
 *	@brief	isgreater のテスト
 */

#include <hamon/cmath/isgreater.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace isgreater_test
{

static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreater(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsGreaterTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = hamon::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto min1 = hamon::numeric_limits<T1>::min();
	HAMON_CXX11_CONSTEXPR auto min2 = hamon::numeric_limits<T2>::min();
	HAMON_CXX11_CONSTEXPR auto max1 = hamon::numeric_limits<T1>::max();
	HAMON_CXX11_CONSTEXPR auto max2 = hamon::numeric_limits<T2>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(0.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreater(T1(1.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(0.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(1.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(0.0), inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(0.0), min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(0.0), max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(0.0), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreater(inf1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(inf1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreater(inf1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreater(inf1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(inf1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreater(min1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(min1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(min1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(min1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreater(max1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(max1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreater(max1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(max1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(nan1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(nan1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(nan1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(nan1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(nan1,    nan2));
}

template <typename T1, typename T2>
void IsGreaterTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(0), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreater(T1(1), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(0), T2(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreater(T1(1), T2(1)));
}

GTEST_TEST(CMathTest, IsGreaterTest)
{
//	IsGreaterTestFloat<float,       float>      ();
	IsGreaterTestFloat<float,       double>     ();
//	IsGreaterTestFloat<float,       long double>();
	IsGreaterTestFloat<double,      float>      ();
//	IsGreaterTestFloat<double,      double>     ();
	IsGreaterTestFloat<double,      long double>();
//	IsGreaterTestFloat<long double, float>      ();
	IsGreaterTestFloat<long double, double>     ();
//	IsGreaterTestFloat<long double, long double>();

	IsGreaterTestInteger<int, int>();
//	IsGreaterTestInteger<int, float>();
	IsGreaterTestInteger<int, double>();
//	IsGreaterTestInteger<int, long double>();
	IsGreaterTestInteger<float, int>();
//	IsGreaterTestInteger<double, int>();
	IsGreaterTestInteger<long double, int>();
}

}	// namespace isgreater_test

}	// namespace hamon_cmath_test
