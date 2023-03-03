/**
 *	@file	unit_test_cmath_islessequal.cpp
 *
 *	@brief	islessequal のテスト
 */

#include <hamon/cmath/islessequal.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace islessequal_test
{

static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessequal(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsLessEqualTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto min1 = std::numeric_limits<T1>::min();
	HAMON_CXX11_CONSTEXPR auto min2 = std::numeric_limits<T2>::min();
	HAMON_CXX11_CONSTEXPR auto max1 = std::numeric_limits<T1>::max();
	HAMON_CXX11_CONSTEXPR auto max2 = std::numeric_limits<T2>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(0.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(T1(1.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(0.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(1.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(0.0), inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(0.0), min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(0.0), max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(T1(0.0), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(inf1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(inf1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(inf1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(inf1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(inf1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(min1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(min1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(min1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(min1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(max1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(max1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(max1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(max1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(nan1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(nan1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(nan1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(nan1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(nan1,    nan2));
}

template <typename T1, typename T2>
void IsLessEqualTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(0), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessequal(T1(1), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(0), T2(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessequal(T1(1), T2(1)));
}

GTEST_TEST(CMathTest, IsLessEqualTest)
{
//	IsLessEqualTestFloat<float,       float>      ();
	IsLessEqualTestFloat<float,       double>     ();
//	IsLessEqualTestFloat<float,       long double>();
	IsLessEqualTestFloat<double,      float>      ();
//	IsLessEqualTestFloat<double,      double>     ();
	IsLessEqualTestFloat<double,      long double>();
//	IsLessEqualTestFloat<long double, float>      ();
	IsLessEqualTestFloat<long double, double>     ();
//	IsLessEqualTestFloat<long double, long double>();

	IsLessEqualTestInteger<int, int>();
//	IsLessEqualTestInteger<int, float>();
	IsLessEqualTestInteger<int, double>();
//	IsLessEqualTestInteger<int, long double>();
	IsLessEqualTestInteger<float, int>();
//	IsLessEqualTestInteger<double, int>();
	IsLessEqualTestInteger<long double, int>();
}

}	// namespace islessequal_test

}	// namespace hamon_cmath_test
