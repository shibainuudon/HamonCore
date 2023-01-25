/**
 *	@file	unit_test_cmath_isunordered.cpp
 *
 *	@brief	isunordered のテスト
 */

#include <hamon/cmath/isunordered.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <type_traits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace isunordered_test
{

static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0f, 0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0f, 0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0f, 0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0f, 0   ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0 , 0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0 , 0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0 , 0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0 , 0   ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0l, 0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0l, 0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0l, 0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0.0l, 0   ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0   , 0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0   , 0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0   , 0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isunordered(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void IsUnorderedTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto min1 = std::numeric_limits<T1>::min();
	HAMON_CXX11_CONSTEXPR auto min2 = std::numeric_limits<T2>::min();
	HAMON_CXX11_CONSTEXPR auto max1 = std::numeric_limits<T1>::max();
	HAMON_CXX11_CONSTEXPR auto max2 = std::numeric_limits<T2>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(T1(0.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(T1(0.0), inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(T1(0.0), min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(T1(0.0), max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(T1(0.0), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(inf1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(inf1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(inf1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(inf1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(inf1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(min1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(min1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(min1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(min1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(min1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(max1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(max1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(max1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(max1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(max1,    nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(nan1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(nan1,    inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(nan1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(nan1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isunordered(nan1,    nan2));
}

template <typename T1, typename T2>
void IsUnorderedTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR auto min1    = std::numeric_limits<T1>::min();
	HAMON_CXX11_CONSTEXPR auto min2    = std::numeric_limits<T2>::min();
	HAMON_CXX11_CONSTEXPR auto max1    = std::numeric_limits<T1>::max();
	HAMON_CXX11_CONSTEXPR auto max2    = std::numeric_limits<T2>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(T1(0),   T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(T1(0),   min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(T1(0),   max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(min1,    T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(min1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(min1,    max2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(max1,    T2(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(max1,    min2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isunordered(max1,    max2));
}

GTEST_TEST(CMathTest, IsUnorderedTest)
{
	IsUnorderedTestFloat<float,       float>      ();
//	IsUnorderedTestFloat<float,       double>     ();
	IsUnorderedTestFloat<float,       long double>();
//	IsUnorderedTestFloat<double,      float>      ();
	IsUnorderedTestFloat<double,      double>     ();
//	IsUnorderedTestFloat<double,      long double>();
	IsUnorderedTestFloat<long double, float>      ();
//	IsUnorderedTestFloat<long double, double>     ();
	IsUnorderedTestFloat<long double, long double>();

//	IsUnorderedTestInteger<int, int>();
	IsUnorderedTestInteger<int, float>();
//	IsUnorderedTestInteger<int, double>();
	IsUnorderedTestInteger<int, long double>();
//	IsUnorderedTestInteger<float, int>();
	IsUnorderedTestInteger<double, int>();
//	IsUnorderedTestInteger<long double, int>();
}

}	// namespace isunordered_test

}	// namespace hamon_cmath_test
