/**
 *	@file	unit_test_cmath_fdim.cpp
 *
 *	@brief	fdim のテスト
 */

#include <hamon/cmath/fdim.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fdim_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fdim(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::fdimf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fdim(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fdim(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fdim(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fdim(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fdim(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fdim(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fdim(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fdim(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fdim(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fdim(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fdiml(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fdim(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fdim(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fdim(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fdim(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fdim(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FdimTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = hamon::numeric_limits<T2>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 0.0), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.5, hamon::fdim(T1( 0.5), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-0.5), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::fdim(T1( 1.0), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-1.0), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5, hamon::fdim(T1( 2.5), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-2.5), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.0, hamon::fdim(T1( 4.0), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-4.0), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 0.0), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.5, hamon::fdim(T1( 1.0), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-1.0), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.0, hamon::fdim(T1( 2.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-2.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3.5, hamon::fdim(T1( 4.0), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-4.0), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.5, hamon::fdim(T1( 0.0), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::fdim(T1( 0.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-0.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5, hamon::fdim(T1( 1.0), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-1.0), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3.0, hamon::fdim(T1( 2.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-2.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.5, hamon::fdim(T1( 4.0), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-4.0), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 0.0), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 0.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-0.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 1.0), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-1.0), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::fdim(T1( 2.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-2.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5, hamon::fdim(T1( 4.0), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-4.0), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5, hamon::fdim(T1( 0.0), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.0, hamon::fdim(T1( 0.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::fdim(T1(-0.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5, hamon::fdim(T1( 1.0), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.5, hamon::fdim(T1(-1.0), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.0, hamon::fdim(T1( 2.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-2.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5.5, hamon::fdim(T1( 4.0), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-4.0), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 0.0), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 0.5), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-0.5), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 1.0), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-1.0), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1( 2.5), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-2.5), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.5, hamon::fdim(T1( 4.0), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-4.0), T2( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3.5, hamon::fdim(T1( 0.0), T2(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.0, hamon::fdim(T1( 0.5), T2(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3.0, hamon::fdim(T1(-0.5), T2(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.5, hamon::fdim(T1( 1.0), T2(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5, hamon::fdim(T1(-1.0), T2(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6.0, hamon::fdim(T1( 2.5), T2(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::fdim(T1(-2.5), T2(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7.5, hamon::fdim(T1( 4.0), T2(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::fdim(T1(-4.0), T2(-3.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf1, hamon::fdim( inf1, T2(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0,  hamon::fdim(-inf1, T2(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0,  hamon::fdim(T1(20.0),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf2, hamon::fdim(T1(20.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0,  hamon::fdim( inf1,  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf1, hamon::fdim( inf1, -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0,  hamon::fdim(-inf1,  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0,  hamon::fdim(-inf1, -inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim( nan1,    T2(2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(-nan1,    T2(3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim( nan1,    inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(-nan1,    inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim( nan1,   -inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(-nan1,   -inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(T1(4.0),  nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(T1(5.0), -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim( inf1,    nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim( inf1,   -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(-inf1,    nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(-inf1,   -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim( nan1,    nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(-nan1,    nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim( nan1,   -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fdim(-nan1,   -nan2)));
}

template <typename T1, typename T2>
void FdimTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  0), T2(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fdim(T1(  1), T2(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fdim(T1(  2), T2(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::fdim(T1( 10), T2(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -1), T2(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -2), T2(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(-10), T2(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  0), T2(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  1), T2(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fdim(T1(  2), T2(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::fdim(T1( 10), T2(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -1), T2(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -2), T2(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(-10), T2(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fdim(T1(  0), T2( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fdim(T1(  1), T2( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::fdim(T1(  2), T2( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::fdim(T1( 10), T2( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -1), T2( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -2), T2( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(-10), T2( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  0), T2(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  1), T2(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  2), T2(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::fdim(T1( 10), T2(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -1), T2(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -2), T2(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(-10), T2(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fdim(T1(  0), T2( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::fdim(T1(  1), T2( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::fdim(T1(  2), T2( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::fdim(T1( 10), T2( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fdim(T1( -1), T2( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -2), T2( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(-10), T2( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  0), T2( 10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  1), T2( 10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(  2), T2( 10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( 10), T2( 10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -1), T2( 10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1( -2), T2( 10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(-10), T2( 10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::fdim(T1(  0), T2(-10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::fdim(T1(  1), T2(-10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::fdim(T1(  2), T2(-10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::fdim(T1( 10), T2(-10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9, hamon::fdim(T1( -1), T2(-10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8, hamon::fdim(T1( -2), T2(-10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fdim(T1(-10), T2(-10)));
}

GTEST_TEST(CMathTest, FdimTest)
{
	FdimTestFloat<float,       float>      ();
//	FdimTestFloat<float,       double>     ();
	FdimTestFloat<float,       long double>();
//	FdimTestFloat<double,      float>      ();
	FdimTestFloat<double,      double>     ();
//	FdimTestFloat<double,      long double>();
	FdimTestFloat<long double, float>      ();
//	FdimTestFloat<long double, double>     ();
	FdimTestFloat<long double, long double>();

	FdimTestInteger<int,         int>();
	FdimTestInteger<int,         float>();
//	FdimTestInteger<int,         double>();
	FdimTestInteger<int,         long double>();
//	FdimTestInteger<float,       int>();
	FdimTestInteger<double,      int>();
	FdimTestInteger<long double, int>();
}

}	// namespace fdim_test

}	// namespace hamon_cmath_test
