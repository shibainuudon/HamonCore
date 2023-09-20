/**
 *	@file	unit_test_cmath_scalbn.cpp
 *
 *	@brief	scalbn のテスト
 */

#include <hamon/cmath/scalbn.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace scalbn_test
{

static_assert(hamon::is_same<float,       decltype(hamon::scalbn(0.0f, 0))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::scalbnf(0.0f, 0))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::scalbn(0.0, 0))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::scalbn(0, 0))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::scalbn(0.0l, 0))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::scalbnl(0.0l, 0))>::value, "");

template <typename T>
void ScalbnTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::scalbn(T( 1.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::scalbn(T( 1.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::scalbn(T( 1.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::scalbn(T( 1.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::scalbn(T( 1.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::scalbn(T( 1.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::scalbn(T( 1.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125, hamon::scalbn(T(-1.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,  hamon::scalbn(T(-1.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,   hamon::scalbn(T(-1.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,   hamon::scalbn(T(-1.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,   hamon::scalbn(T(-1.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,   hamon::scalbn(T(-1.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8.0,   hamon::scalbn(T(-1.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::scalbn(T( 2.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::scalbn(T( 2.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::scalbn(T( 2.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::scalbn(T( 2.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::scalbn(T( 2.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::scalbn(T( 2.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::scalbn(T( 2.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.25, hamon::scalbn(T(-2.0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.5,  hamon::scalbn(T(-2.0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1.0,  hamon::scalbn(T(-2.0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2.0,  hamon::scalbn(T(-2.0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4.0,  hamon::scalbn(T(-2.0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8.0,  hamon::scalbn(T(-2.0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16.0,  hamon::scalbn(T(-2.0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0625, hamon::scalbn(T( 0.5), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125,  hamon::scalbn(T( 0.5), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,   hamon::scalbn(T( 0.5), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,    hamon::scalbn(T( 0.5),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,    hamon::scalbn(T( 0.5),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,    hamon::scalbn(T( 0.5),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,    hamon::scalbn(T( 0.5),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.0625, hamon::scalbn(T(-0.5), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125,  hamon::scalbn(T(-0.5), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,   hamon::scalbn(T(-0.5), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,    hamon::scalbn(T(-0.5),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,    hamon::scalbn(T(-0.5),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,    hamon::scalbn(T(-0.5),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,    hamon::scalbn(T(-0.5),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(+0.0), hamon::scalbn(T(+0.0), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-0.0), hamon::scalbn(T(-0.0), 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,    hamon::scalbn(+inf, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf,    hamon::scalbn(-inf, 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2.0),  hamon::scalbn(T(2.0), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3.0),  hamon::scalbn(T(3.0), 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::scalbn(+nan, 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::scalbn(-nan, 1)));
}

template <typename T>
void ScalbnTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::scalbn(T( 1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::scalbn(T( 1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::scalbn(T( 1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::scalbn(T( 1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::scalbn(T( 1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::scalbn(T( 1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::scalbn(T( 1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.125, hamon::scalbn(T(-1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.25,  hamon::scalbn(T(-1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5,   hamon::scalbn(T(-1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0,   hamon::scalbn(T(-1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0,   hamon::scalbn(T(-1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.0,   hamon::scalbn(T(-1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-8.0,   hamon::scalbn(T(-1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::scalbn(T( 2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::scalbn(T( 2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::scalbn(T( 2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::scalbn(T( 2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::scalbn(T( 2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::scalbn(T( 2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::scalbn(T( 2),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.25, hamon::scalbn(T(-2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -0.5,  hamon::scalbn(T(-2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1.0,  hamon::scalbn(T(-2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2.0,  hamon::scalbn(T(-2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -4.0,  hamon::scalbn(T(-2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8.0,  hamon::scalbn(T(-2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16.0,  hamon::scalbn(T(-2),  3));
}

template <typename T>
void ScalbnTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0,   hamon::scalbn(T( 0),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.125, hamon::scalbn(T( 1), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.25,  hamon::scalbn(T( 1), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5,   hamon::scalbn(T( 1), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0,   hamon::scalbn(T( 1),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0,   hamon::scalbn(T( 1),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0,   hamon::scalbn(T( 1),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8.0,   hamon::scalbn(T( 1),  3));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.25, hamon::scalbn(T( 2), -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0.5,  hamon::scalbn(T( 2), -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1.0,  hamon::scalbn(T( 2), -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2.0,  hamon::scalbn(T( 2),  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  4.0,  hamon::scalbn(T( 2),  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  8.0,  hamon::scalbn(T( 2),  2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 16.0,  hamon::scalbn(T( 2),  3));
}

GTEST_TEST(CMathTest, ScalbnTest)
{
	ScalbnTestFloat<float>();
	ScalbnTestFloat<double>();
	ScalbnTestFloat<long double>();

	ScalbnTestSignedInt<int>();
//	ScalbnTestSignedInt<signed char>();
	ScalbnTestSignedInt<short>();
//	ScalbnTestSignedInt<long>();
	ScalbnTestSignedInt<long long>();

//	ScalbnTestUnsignedInt<unsigned int>();
	ScalbnTestUnsignedInt<unsigned char>();
//	ScalbnTestUnsignedInt<unsigned short>();
	ScalbnTestUnsignedInt<unsigned long>();
//	ScalbnTestUnsignedInt<unsigned long long>();
}

}	// namespace scalbn_test

}	// namespace hamon_cmath_test
