/**
 *	@file	unit_test_cmath_remainder.cpp
 *
 *	@brief	remainder のテスト
 */

#include <hamon/cmath/remainder.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace remainder_test
{

static_assert(hamon::is_same<float,       decltype(hamon::remainder(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::remainderf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remainder(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remainder(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remainder(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remainder(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remainder(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remainder(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remainder(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remainder(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remainder(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remainder(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remainderl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remainder(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remainder(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remainder(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remainder(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remainder(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void RemainderTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = hamon::numeric_limits<T2>::infinity();

	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.5), hamon::remainder(T1( 5.5), T2( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.5), hamon::remainder(T1(-5.5), T2( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.5), hamon::remainder(T1( 5.5), T2(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.5), hamon::remainder(T1(-5.5), T2(-3.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.5), hamon::remainder(T1( 5.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.5), hamon::remainder(T1(-5.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.5), hamon::remainder(T1( 5.5), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.5), hamon::remainder(T1(-5.5), T2(-2.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::remainder(T1( 6.0), T2( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.0), hamon::remainder(T1(-6.0), T2( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::remainder(T1( 6.0), T2(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.0), hamon::remainder(T1(-6.0), T2(-3.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1.0), hamon::remainder(T1( 6.0), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1.0), hamon::remainder(T1(-6.0), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1.0), hamon::remainder(T1( 6.0), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1.0), hamon::remainder(T1(-6.0), T2(-2.5)));

	//If x is ±∞ and y is not NaN, NaN is returned and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder( inf1, T2( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(-inf1, T2( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder( inf1, T2(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(-inf1, T2(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder( inf1, T2( 0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(-inf1, T2( 0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder( inf1, inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(-inf1, inf2)));

	//If y is ±0 and x is not NaN, NaN is returned and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(T1( 1.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(T1( 1.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(T1(-2.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(T1(-2.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(T1( 0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(T1( 0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(inf1,     T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(inf1,     T2(-0.0))));

	//If either argument is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(nan1, T2(1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(nan1, T2(0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(T1(1.0), nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(inf1, nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remainder(nan1, nan2)));
}

template <typename T1, typename T2>
void RemainderTestInteger(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1), hamon::remainder(T1( 5), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::remainder(T1(-5), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1), hamon::remainder(T1( 5), T2(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::remainder(T1(-5), T2(-3)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::remainder(T1( 5), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1), hamon::remainder(T1(-5), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::remainder(T1( 5), T2(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1), hamon::remainder(T1(-5), T2(-2)));
}

GTEST_TEST(CMathTest, RemainderTest)
{
	RemainderTestFloat<float,       float>      ();
//	RemainderTestFloat<float,       double>     ();
	RemainderTestFloat<float,       long double>();
//	RemainderTestFloat<double,      float>      ();
	RemainderTestFloat<double,      double>     ();
//	RemainderTestFloat<double,      long double>();
	RemainderTestFloat<long double, float>      ();
//	RemainderTestFloat<long double, double>     ();
	RemainderTestFloat<long double, long double>();

//	RemainderTestInteger<int,         int>();
	RemainderTestInteger<int,         float>();
//	RemainderTestInteger<int,         double>();
	RemainderTestInteger<int,         long double>();
//	RemainderTestInteger<float,       int>();
	RemainderTestInteger<double,      int>();
//	RemainderTestInteger<long double, int>();
}

}	// namespace remainder_test

}	// namespace hamon_cmath_test
