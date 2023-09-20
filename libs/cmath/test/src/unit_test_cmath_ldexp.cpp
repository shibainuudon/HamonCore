/**
 *	@file	unit_test_cmath_ldexp.cpp
 *
 *	@brief	ldexp のテスト
 */

#include <hamon/cmath/ldexp.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ldexp_test
{

static_assert(hamon::is_same<float,       decltype(hamon::ldexp(0.0f, 0))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::ldexpf(0.0f, 0))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::ldexp(0.0 , 0))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::ldexp(0   , 0))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::ldexp(0.0l, 0))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::ldexpl(0.0l, 0))>::value, "");

template <typename T>
void LdexpTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::ldexp(T( 1.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::ldexp(T( 1.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::ldexp(T( 1.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::ldexp(T( 1.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::ldexp(T( 1.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::ldexp(T( 1.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::ldexp(T( 1.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125, hamon::ldexp(T(-1.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,  hamon::ldexp(T(-1.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,   hamon::ldexp(T(-1.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,   hamon::ldexp(T(-1.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,   hamon::ldexp(T(-1.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,   hamon::ldexp(T(-1.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8.0,   hamon::ldexp(T(-1.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::ldexp(T( 2.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::ldexp(T( 2.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::ldexp(T( 2.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::ldexp(T( 2.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::ldexp(T( 2.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::ldexp(T( 2.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::ldexp(T( 2.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.25, hamon::ldexp(T(-2.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.5,  hamon::ldexp(T(-2.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1.0,  hamon::ldexp(T(-2.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2.0,  hamon::ldexp(T(-2.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4.0,  hamon::ldexp(T(-2.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8.0,  hamon::ldexp(T(-2.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16.0,  hamon::ldexp(T(-2.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0625, hamon::ldexp(T( 0.5), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125,  hamon::ldexp(T( 0.5), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,   hamon::ldexp(T( 0.5), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,    hamon::ldexp(T( 0.5),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,    hamon::ldexp(T( 0.5),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,    hamon::ldexp(T( 0.5),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,    hamon::ldexp(T( 0.5),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.0625, hamon::ldexp(T(-0.5), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125,  hamon::ldexp(T(-0.5), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,   hamon::ldexp(T(-0.5), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,    hamon::ldexp(T(-0.5),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,    hamon::ldexp(T(-0.5),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,    hamon::ldexp(T(-0.5),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,    hamon::ldexp(T(-0.5),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(+0.0), hamon::ldexp(T(+0.0), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-0.0), hamon::ldexp(T(-0.0), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,    hamon::ldexp(+inf, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf,    hamon::ldexp(-inf, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2.0),  hamon::ldexp(T(2.0), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3.0),  hamon::ldexp(T(3.0), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::ldexp(+nan, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::ldexp(-nan, 1)));
}

template <typename T>
void LdexpTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::ldexp(T( 1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::ldexp(T( 1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::ldexp(T( 1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::ldexp(T( 1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::ldexp(T( 1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::ldexp(T( 1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::ldexp(T( 1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125, hamon::ldexp(T(-1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,  hamon::ldexp(T(-1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,   hamon::ldexp(T(-1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,   hamon::ldexp(T(-1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,   hamon::ldexp(T(-1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,   hamon::ldexp(T(-1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8.0,   hamon::ldexp(T(-1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::ldexp(T( 2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::ldexp(T( 2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::ldexp(T( 2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::ldexp(T( 2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::ldexp(T( 2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::ldexp(T( 2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::ldexp(T( 2),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.25, hamon::ldexp(T(-2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.5,  hamon::ldexp(T(-2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1.0,  hamon::ldexp(T(-2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2.0,  hamon::ldexp(T(-2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4.0,  hamon::ldexp(T(-2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8.0,  hamon::ldexp(T(-2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16.0,  hamon::ldexp(T(-2),  3));
}

template <typename T>
void LdexpTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::ldexp(T( 0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::ldexp(T( 1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::ldexp(T( 1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::ldexp(T( 1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::ldexp(T( 1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::ldexp(T( 1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::ldexp(T( 1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::ldexp(T( 1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::ldexp(T( 2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::ldexp(T( 2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::ldexp(T( 2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::ldexp(T( 2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::ldexp(T( 2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::ldexp(T( 2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::ldexp(T( 2),  3));
}

GTEST_TEST(CMathTest, LdexpTest)
{
	LdexpTestFloat<float>();
	LdexpTestFloat<double>();
	LdexpTestFloat<long double>();

	LdexpTestSignedInt<int>();
//	LdexpTestSignedInt<signed char>();
	LdexpTestSignedInt<short>();
//	LdexpTestSignedInt<long>();
	LdexpTestSignedInt<long long>();

//	LdexpTestUnsignedInt<unsigned int>();
	LdexpTestUnsignedInt<unsigned char>();
//	LdexpTestUnsignedInt<unsigned short>();
	LdexpTestUnsignedInt<unsigned long>();
//	LdexpTestUnsignedInt<unsigned long long>();
}

}	// namespace ldexp_test

}	// namespace hamon_cmath_test
