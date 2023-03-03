/**
 *	@file	unit_test_cmath_islessgreater.cpp
 *
 *	@brief	islessgreater のテスト
 */

#include <hamon/cmath/islessgreater.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace islessgreater_test
{

static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::islessgreater(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsLessGreaterTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto min1 = std::numeric_limits<T1>::min();
	HAMON_CXX11_CONSTEXPR auto min2 = std::numeric_limits<T2>::min();
	HAMON_CXX11_CONSTEXPR auto max1 = std::numeric_limits<T1>::max();
	HAMON_CXX11_CONSTEXPR auto max2 = std::numeric_limits<T2>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(T1(0.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(T1(1.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(T1(0.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(T1(1.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(T1(0.0), inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(T1(0.0), min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(T1(0.0), max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(T1(0.0), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(inf1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(inf1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(inf1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(inf1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(inf1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(min1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(min1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(min1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(min1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(max1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(max1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(max1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(max1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(nan1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(nan1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(nan1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(nan1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(nan1,    nan2));
}

template <typename T1, typename T2>
void IsLessGreaterTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(T1(0), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(T1(1), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::islessgreater(T1(0), T2(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::islessgreater(T1(1), T2(1)));
}

GTEST_TEST(CMathTest, IsLessGreaterTest)
{
	IsLessGreaterTestFloat<float,       float>      ();
//	IsLessGreaterTestFloat<float,       double>     ();
	IsLessGreaterTestFloat<float,       long double>();
//	IsLessGreaterTestFloat<double,      float>      ();
	IsLessGreaterTestFloat<double,      double>     ();
//	IsLessGreaterTestFloat<double,      long double>();
	IsLessGreaterTestFloat<long double, float>      ();
//	IsLessGreaterTestFloat<long double, double>     ();
	IsLessGreaterTestFloat<long double, long double>();

//	IsLessGreaterTestInteger<int, int>();
	IsLessGreaterTestInteger<int, float>();
//	IsLessGreaterTestInteger<int, double>();
	IsLessGreaterTestInteger<int, long double>();
//	IsLessGreaterTestInteger<float, int>();
	IsLessGreaterTestInteger<double, int>();
//	IsLessGreaterTestInteger<long double, int>();
}

}	// namespace islessgreater_test

}	// namespace hamon_cmath_test
