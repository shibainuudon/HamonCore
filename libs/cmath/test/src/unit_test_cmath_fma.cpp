/**
 *	@file	unit_test_cmath_fma.cpp
 *
 *	@brief	fma のテスト
 */

#include <hamon/cmath/fma.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fma_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fma(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0f, 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0f, 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0f, 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0f, 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0f, 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0f, 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0f, 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0f, 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0f, 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0f, 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0f, 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0f, 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0f, 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0f, 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0f, 0   , 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0 , 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0 , 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0 , 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0 , 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0 , 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0 , 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0 , 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0.0 , 0   , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0.0l, 0   , 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0   , 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0   , 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0   , 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0   , 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0   , 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0   , 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fma(0   , 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fma(0   , 0   , 0   ))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::fmaf(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmal(0.0l, 0.0l, 0.0l))>::value, "");

template <typename T1, typename T2, typename T3>
void FmaTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2, T3>;

	HAMON_CXX11_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf3 = std::numeric_limits<T3>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf4 = std::numeric_limits<R>::infinity();
	HAMON_CXX11_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan3 = std::numeric_limits<T3>::quiet_NaN();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::fma(T1( 0.0), T2( 0.0), T3( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fma(T1( 0.0), T2( 0.0), T3( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fma(T1( 0.0), T2( 0.0), T3(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fma(T1( 0.0), T2( 2.5), T3( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fma(T1( 0.0), T2( 2.5), T3(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fma(T1( 0.0), T2(-2.5), T3( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fma(T1( 0.0), T2(-2.5), T3(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.0, hamon::fma(T1( 1.0), T2( 2.5), T3( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0, hamon::fma(T1( 1.0), T2( 2.5), T3(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0, hamon::fma(T1( 1.0), T2(-2.5), T3( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3.0, hamon::fma(T1( 1.0), T2(-2.5), T3(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-6.0, hamon::fma(T1(-3.0), T2( 2.5), T3( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-9.0, hamon::fma(T1(-3.0), T2( 2.5), T3(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9.0, hamon::fma(T1(-3.0), T2(-2.5), T3( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6.0, hamon::fma(T1(-3.0), T2(-2.5), T3(-1.5)));

	//If x is zero and y is infinite or if x is infinite and y is zero, and z is not a NaN, then NaN is returned and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(+0.0), +inf2, T3( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(-0.0), +inf2, T3( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(+0.0), -inf2, T3( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(-0.0), -inf2, T3( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(+inf1, T2(+0.0), T3( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(+inf1, T2(-0.0), T3( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(-inf1, T2(+0.0), T3( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(-inf1, T2(-0.0), T3( 1.0))));

	//If x is zero and y is infinite or if x is infinite and y is zero, and z is a NaN, then NaN is returned and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(+0.0), +inf2, nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(-0.0), +inf2, nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(+0.0), -inf2, nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(-0.0), -inf2, nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(+inf1, T2(+0.0), nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(+inf1, T2(-0.0), nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(-inf1, T2(+0.0), nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(-inf1, T2(-0.0), nan3)));

	//If x*y is an exact infinity and z is an infinity with the opposite sign, NaN is returned and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(+1.0), +inf2, -inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(-1.0), +inf2, +inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(+1.0), -inf2, +inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(-1.0), -inf2, -inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(+inf1, T2(+1.0), -inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(+inf1, T2(-1.0), +inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(-inf1, T2(+1.0), +inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(-inf1, T2(-1.0), -inf3)));

	// x*yがinfかつzがinfでも符号が同じならNaNにならない
	// (計算途中でinfが発生するのでconstexprにはできない)
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::fma(T1(+1.0), +inf2, +inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::fma(T1(-1.0), +inf2, -inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::fma(T1(+1.0), -inf2, -inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::fma(T1(-1.0), -inf2, +inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::fma(+inf1, T2(+1.0), +inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::fma(+inf1, T2(-1.0), -inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::fma(-inf1, T2(+1.0), -inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::fma(-inf1, T2(-1.0), +inf3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf4, hamon::fma(T1(+1.0), +inf2, +inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf4, hamon::fma(T1(-1.0), +inf2, -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf4, hamon::fma(T1(+1.0), -inf2, -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf4, hamon::fma(T1(-1.0), -inf2, +inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf4, hamon::fma(+inf1, T2(+1.0), +inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf4, hamon::fma(+inf1, T2(-1.0), -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf4, hamon::fma(-inf1, T2(+1.0), -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf4, hamon::fma(-inf1, T2(-1.0), +inf3));

	//If x or y are NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(nan1,    T2(1.0), T3(1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(1.0), nan2,    T3(1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(nan1,    nan2,    T3(1.0))));

	//If z is NaN, and x*y aren't 0*Inf or Inf*0, then NaN is returned (without FE_INVALID)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fma(T1(1.0), T2(1.0), nan3)));
}

template <typename T1, typename T2, typename T3>
void FmaTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.0, hamon::fma(T1( 0), T2( 0), T3(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0, hamon::fma(T1( 0), T2( 0), T3(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2.0, hamon::fma(T1( 0), T2( 0), T3( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  3.0, hamon::fma(T1( 0), T2( 3), T3(  3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4.0, hamon::fma(T1( 0), T2( 3), T3( -4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  5.0, hamon::fma(T1( 0), T2(-3), T3(  5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -6.0, hamon::fma(T1( 0), T2(-3), T3( -6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 10.0, hamon::fma(T1( 1), T2( 3), T3(  7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -5.0, hamon::fma(T1( 1), T2( 3), T3( -8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  6.0, hamon::fma(T1( 1), T2(-3), T3(  9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-13.0, hamon::fma(T1( 1), T2(-3), T3(-10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1.0, hamon::fma(T1(-4), T2( 3), T3( 11)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-24.0, hamon::fma(T1(-4), T2( 3), T3(-12)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 25.0, hamon::fma(T1(-4), T2(-3), T3( 13)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2.0, hamon::fma(T1(-4), T2(-3), T3(-14)));
}

GTEST_TEST(CMathTest, FmaTest)
{
	FmaTestFloat<float,       float,       float>      ();
//	FmaTestFloat<float,       float,       double>     ();
	FmaTestFloat<float,       float,       long double>();
//	FmaTestFloat<float,       double,      float>      ();
	FmaTestFloat<float,       double,      double>     ();
//	FmaTestFloat<float,       double,      long double>();
	FmaTestFloat<float,       long double, float>      ();
//	FmaTestFloat<float,       long double, double>     ();
	FmaTestFloat<float,       long double, long double>();
//	FmaTestFloat<double,      float,       float>      ();
	FmaTestFloat<double,      float,       double>     ();
//	FmaTestFloat<double,      float,       long double>();
	FmaTestFloat<double,      double,      float>      ();
//	FmaTestFloat<double,      double,      double>     ();
	FmaTestFloat<double,      double,      long double>();
//	FmaTestFloat<double,      long double, float>      ();
	FmaTestFloat<double,      long double, double>     ();
//	FmaTestFloat<double,      long double, long double>();
	FmaTestFloat<long double, float,       float>      ();
//	FmaTestFloat<long double, float,       double>     ();
	FmaTestFloat<long double, float,       long double>();
//	FmaTestFloat<long double, double,      float>      ();
	FmaTestFloat<long double, double,      double>     ();
//	FmaTestFloat<long double, double,      long double>();
	FmaTestFloat<long double, long double, float>      ();
//	FmaTestFloat<long double, long double, double>     ();
	FmaTestFloat<long double, long double, long double>();

	FmaTestInteger<int,         int,         int>();
//	FmaTestInteger<int,         int,         float>();
	FmaTestInteger<int,         int,         double>();
//	FmaTestInteger<int,         int,         long double>();
	FmaTestInteger<int,         float,       int>();
//	FmaTestInteger<int,         float,       float>();
	FmaTestInteger<int,         float,       double>();
//	FmaTestInteger<int,         float,       long double>();
	FmaTestInteger<int,         double,      int>();
//	FmaTestInteger<int,         double,      float>();
	FmaTestInteger<int,         double,      double>();
//	FmaTestInteger<int,         double,      long double>();
	FmaTestInteger<int,         long double, int>();
//	FmaTestInteger<int,         long double, float>();
	FmaTestInteger<int,         long double, double>();
//	FmaTestInteger<int,         long double, long double>();
	FmaTestInteger<float,       int,         int>();
//	FmaTestInteger<float,       int,         float>();
	FmaTestInteger<float,       int,         double>();
//	FmaTestInteger<float,       int,         long double>();
	FmaTestInteger<float,       float,       int>();
//	FmaTestInteger<float,       double,      int>();
	FmaTestInteger<float,       long double, int>();
//	FmaTestInteger<double,      int,         int>();
	FmaTestInteger<double,      int,         float>();
//	FmaTestInteger<double,      int,         double>();
	FmaTestInteger<double,      int,         long double>();
//	FmaTestInteger<double,      float,       int>();
	FmaTestInteger<double,      double,      int>();
//	FmaTestInteger<double,      long double, int>();
	FmaTestInteger<long double, int,         int>();
//	FmaTestInteger<long double, int,         float>();
	FmaTestInteger<long double, int,         double>();
//	FmaTestInteger<long double, int,         long double>();
	FmaTestInteger<long double, float,       int>();
//	FmaTestInteger<long double, double,      int>();
	FmaTestInteger<long double, long double, int>();
}

}	// namespace fma_test

}	// namespace hamon_cmath_test
