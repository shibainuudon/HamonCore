/**
 *	@file	unit_test_cmath_scalbln.cpp
 *
 *	@brief	scalbln のテスト
 */

#include <hamon/cmath/scalbln.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace scalbln_test
{

static_assert(hamon::is_same<float,       decltype(hamon::scalbln(0.0f, 0L))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::scalblnf(0.0f, 0L))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::scalbln(0.0, 0L))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::scalbln(0, 0L))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::scalbln(0.0l, 0L))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::scalblnl(0.0l, 0L))>::value, "");

template <typename T>
void ScalblnTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::scalbln(T( 1.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::scalbln(T( 1.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::scalbln(T( 1.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::scalbln(T( 1.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::scalbln(T( 1.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::scalbln(T( 1.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::scalbln(T( 1.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125, hamon::scalbln(T(-1.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,  hamon::scalbln(T(-1.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,   hamon::scalbln(T(-1.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,   hamon::scalbln(T(-1.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,   hamon::scalbln(T(-1.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,   hamon::scalbln(T(-1.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8.0,   hamon::scalbln(T(-1.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::scalbln(T( 2.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::scalbln(T( 2.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::scalbln(T( 2.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::scalbln(T( 2.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::scalbln(T( 2.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::scalbln(T( 2.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::scalbln(T( 2.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.25, hamon::scalbln(T(-2.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.5,  hamon::scalbln(T(-2.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1.0,  hamon::scalbln(T(-2.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2.0,  hamon::scalbln(T(-2.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4.0,  hamon::scalbln(T(-2.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8.0,  hamon::scalbln(T(-2.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16.0,  hamon::scalbln(T(-2.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0625, hamon::scalbln(T( 0.5), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125,  hamon::scalbln(T( 0.5), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,   hamon::scalbln(T( 0.5), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,    hamon::scalbln(T( 0.5),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,    hamon::scalbln(T( 0.5),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,    hamon::scalbln(T( 0.5),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,    hamon::scalbln(T( 0.5),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.0625, hamon::scalbln(T(-0.5), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125,  hamon::scalbln(T(-0.5), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,   hamon::scalbln(T(-0.5), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,    hamon::scalbln(T(-0.5),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,    hamon::scalbln(T(-0.5),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,    hamon::scalbln(T(-0.5),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,    hamon::scalbln(T(-0.5),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(+0.0), hamon::scalbln(T(+0.0), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-0.0), hamon::scalbln(T(-0.0), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,    hamon::scalbln(+inf, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf,    hamon::scalbln(-inf, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2.0),  hamon::scalbln(T(2.0), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3.0),  hamon::scalbln(T(3.0), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::scalbln(+nan, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::scalbln(-nan, 1)));
}

template <typename T>
void ScalblnTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::scalbln(T( 1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::scalbln(T( 1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::scalbln(T( 1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::scalbln(T( 1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::scalbln(T( 1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::scalbln(T( 1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::scalbln(T( 1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125, hamon::scalbln(T(-1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,  hamon::scalbln(T(-1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,   hamon::scalbln(T(-1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,   hamon::scalbln(T(-1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,   hamon::scalbln(T(-1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,   hamon::scalbln(T(-1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8.0,   hamon::scalbln(T(-1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::scalbln(T( 2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::scalbln(T( 2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::scalbln(T( 2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::scalbln(T( 2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::scalbln(T( 2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::scalbln(T( 2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::scalbln(T( 2),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.25, hamon::scalbln(T(-2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.5,  hamon::scalbln(T(-2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1.0,  hamon::scalbln(T(-2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2.0,  hamon::scalbln(T(-2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4.0,  hamon::scalbln(T(-2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8.0,  hamon::scalbln(T(-2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16.0,  hamon::scalbln(T(-2),  3));
}

template <typename T>
void ScalblnTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbln(T( 0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::scalbln(T( 1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::scalbln(T( 1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::scalbln(T( 1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::scalbln(T( 1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::scalbln(T( 1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::scalbln(T( 1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::scalbln(T( 1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::scalbln(T( 2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::scalbln(T( 2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::scalbln(T( 2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::scalbln(T( 2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::scalbln(T( 2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::scalbln(T( 2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::scalbln(T( 2),  3));
}

GTEST_TEST(CMathTest, ScalblnTest)
{
	ScalblnTestFloat<float>();
	ScalblnTestFloat<double>();
	ScalblnTestFloat<long double>();

//	ScalblnTestSignedInt<int>();
	ScalblnTestSignedInt<signed char>();
//	ScalblnTestSignedInt<short>();
	ScalblnTestSignedInt<long>();
//	ScalblnTestSignedInt<long long>();

	ScalblnTestUnsignedInt<unsigned int>();
//	ScalblnTestUnsignedInt<unsigned char>();
	ScalblnTestUnsignedInt<unsigned short>();
//	ScalblnTestUnsignedInt<unsigned long>();
	ScalblnTestUnsignedInt<unsigned long long>();
}

}	// namespace scalbln_test

}	// namespace hamon_cmath_test
