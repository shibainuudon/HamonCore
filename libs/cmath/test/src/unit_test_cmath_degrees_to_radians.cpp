/**
 *	@file	unit_test_cmath_degrees_to_radians.cpp
 *
 *	@brief	degrees_to_radians のテスト
 */

#include <hamon/cmath/degrees_to_radians.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace degrees_to_radians_test
{

static_assert(hamon::is_same<float,       decltype(hamon::degrees_to_radians(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::degrees_to_radians(0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::degrees_to_radians(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::degrees_to_radians(0   ))>::value, "");

template <typename T>
void DegreesToRadiansTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR double error = 0.000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::degrees_to_radians(T(   0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0087266462599, (double)hamon::degrees_to_radians(T(   0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0174532925199, (double)hamon::degrees_to_radians(T(   1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0261799387799, (double)hamon::degrees_to_radians(T(   1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, (double)hamon::degrees_to_radians(T(  45.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, (double)hamon::degrees_to_radians(T(  90.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.1415926535898, (double)hamon::degrees_to_radians(T( 180.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.2831853071796, (double)hamon::degrees_to_radians(T( 360.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(12.5663706143591, (double)hamon::degrees_to_radians(T( 720.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.7853981633974, (double)hamon::degrees_to_radians(T( -45.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267949, (double)hamon::degrees_to_radians(T( -90.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.1415926535898, (double)hamon::degrees_to_radians(T(-180.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-6.2831853071796, (double)hamon::degrees_to_radians(T(-360.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::degrees_to_radians(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::degrees_to_radians(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::degrees_to_radians(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::degrees_to_radians(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::degrees_to_radians(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::degrees_to_radians(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::degrees_to_radians(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::degrees_to_radians(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::degrees_to_radians(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::degrees_to_radians(-nan)));
}

template <typename T>
void DegreesToRadiansTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, hamon::degrees_to_radians(T(   0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0174532925199, hamon::degrees_to_radians(T(   1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0349065850398, hamon::degrees_to_radians(T(   2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0523598775598, hamon::degrees_to_radians(T(   3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, hamon::degrees_to_radians(T(  45)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, hamon::degrees_to_radians(T(  90)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.0174532925199, hamon::degrees_to_radians(T(  -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.0349065850398, hamon::degrees_to_radians(T(  -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.0523598775598, hamon::degrees_to_radians(T(  -3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.7853981633974, hamon::degrees_to_radians(T( -45)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267949, hamon::degrees_to_radians(T( -90)), error);
}

template <typename T>
void DegreesToRadiansTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, hamon::degrees_to_radians(T(   0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0174532925199, hamon::degrees_to_radians(T(   1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0349065850398, hamon::degrees_to_radians(T(   2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0523598775598, hamon::degrees_to_radians(T(   3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, hamon::degrees_to_radians(T(  45)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, hamon::degrees_to_radians(T(  90)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.1415926535898, hamon::degrees_to_radians(T( 180)), error);
}

GTEST_TEST(CMathTest, DegreesToRadiansTest)
{
	DegreesToRadiansTestFloat<float>();
	DegreesToRadiansTestFloat<double>();
	DegreesToRadiansTestFloat<long double>();

	DegreesToRadiansTestSignedInt<int>();
	DegreesToRadiansTestSignedInt<signed char>();
//	DegreesToRadiansTestSignedInt<short>();
	DegreesToRadiansTestSignedInt<long>();
//	DegreesToRadiansTestSignedInt<long long>();

	DegreesToRadiansTestUnsignedInt<unsigned int>();
//	DegreesToRadiansTestUnsignedInt<unsigned char>();
	DegreesToRadiansTestUnsignedInt<unsigned short>();
//	DegreesToRadiansTestUnsignedInt<unsigned long>();
	DegreesToRadiansTestUnsignedInt<unsigned long long>();
}

}	// namespace degrees_to_radians_test

}	// namespace hamon_cmath_test
