/**
 *	@file	unit_test_cmath_isgreaterequal.cpp
 *
 *	@brief	isgreaterequal のテスト
 */

#include <hamon/cmath/isgreaterequal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace isgreaterequal_test
{

static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isgreaterequal(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsGreaterEqualTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto min1 = std::numeric_limits<T1>::min();
	HAMON_CXX11_CONSTEXPR auto min2 = std::numeric_limits<T2>::min();
	HAMON_CXX11_CONSTEXPR auto max1 = std::numeric_limits<T1>::max();
	HAMON_CXX11_CONSTEXPR auto max2 = std::numeric_limits<T2>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(T1(0.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(T1(1.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(T1(0.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(T1(1.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(T1(0.0), inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(T1(0.0), min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(T1(0.0), max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(T1(0.0), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(inf1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(inf1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(inf1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(inf1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(inf1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(min1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(min1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(min1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(min1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(max1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(max1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(max1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(max1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(nan1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(nan1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(nan1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(nan1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(nan1,    nan2));
}

template <typename T1, typename T2>
void IsGreaterEqualTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(T1(0), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(T1(1), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isgreaterequal(T1(0), T2(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isgreaterequal(T1(1), T2(1)));
}

GTEST_TEST(CMathTest, IsGreaterEqualTest)
{
	IsGreaterEqualTestFloat<float,       float>      ();
//	IsGreaterEqualTestFloat<float,       double>     ();
	IsGreaterEqualTestFloat<float,       long double>();
//	IsGreaterEqualTestFloat<double,      float>      ();
	IsGreaterEqualTestFloat<double,      double>     ();
//	IsGreaterEqualTestFloat<double,      long double>();
	IsGreaterEqualTestFloat<long double, float>      ();
//	IsGreaterEqualTestFloat<long double, double>     ();
	IsGreaterEqualTestFloat<long double, long double>();

//	IsGreaterEqualTestInteger<int, int>();
	IsGreaterEqualTestInteger<int, float>();
//	IsGreaterEqualTestInteger<int, double>();
	IsGreaterEqualTestInteger<int, long double>();
//	IsGreaterEqualTestInteger<float, int>();
	IsGreaterEqualTestInteger<double, int>();
//	IsGreaterEqualTestInteger<long double, int>();
}

}	// namespace isgreaterequal_test

}	// namespace hamon_cmath_test
