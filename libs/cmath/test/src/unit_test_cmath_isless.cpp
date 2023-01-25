/**
 *	@file	unit_test_cmath_isless.cpp
 *
 *	@brief	isless のテスト
 */

#include <hamon/cmath/isless.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace isless_test
{

static_assert(std::is_same<bool, decltype(hamon::isless(0.0f, 0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0f, 0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0f, 0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0f, 0   ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0 , 0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0 , 0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0 , 0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0 , 0   ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0l, 0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0l, 0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0l, 0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0.0l, 0   ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0   , 0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0   , 0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0   , 0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isless(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsLessTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto min1 = std::numeric_limits<T1>::min();
	HAMON_CXX11_CONSTEXPR auto min2 = std::numeric_limits<T2>::min();
	HAMON_CXX11_CONSTEXPR auto max1 = std::numeric_limits<T1>::max();
	HAMON_CXX11_CONSTEXPR auto max2 = std::numeric_limits<T2>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(T1(0.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(T1(1.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isless(T1(0.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(T1(1.0), T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isless(T1(0.0), inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isless(T1(0.0), min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isless(T1(0.0), max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(T1(0.0), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(inf1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(inf1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(inf1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(inf1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(inf1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(min1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isless(min1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isless(min1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(min1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(max1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isless(max1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(max1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(max1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(nan1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(nan1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(nan1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(nan1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(nan1,    nan2));
}

template <typename T1, typename T2>
void IsLessTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(T1(0), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(T1(1), T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isless(T1(0), T2(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isless(T1(1), T2(1)));
}

GTEST_TEST(CMathTest, IsLessTest)
{
	IsLessTestFloat<float,       float>      ();
//	IsLessTestFloat<float,       double>     ();
	IsLessTestFloat<float,       long double>();
//	IsLessTestFloat<double,      float>      ();
	IsLessTestFloat<double,      double>     ();
//	IsLessTestFloat<double,      long double>();
	IsLessTestFloat<long double, float>      ();
//	IsLessTestFloat<long double, double>     ();
	IsLessTestFloat<long double, long double>();

//	IsLessTestInteger<int, int>();
	IsLessTestInteger<int, float>();
//	IsLessTestInteger<int, double>();
	IsLessTestInteger<int, long double>();
//	IsLessTestInteger<float, int>();
	IsLessTestInteger<double, int>();
//	IsLessTestInteger<long double, int>();
}

}	// namespace isless_test

}	// namespace hamon_cmath_test
