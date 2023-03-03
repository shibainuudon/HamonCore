/**
 *	@file	unit_test_cmath_radians_to_degrees.cpp
 *
 *	@brief	radians_to_degrees のテスト
 */

#include <hamon/cmath/radians_to_degrees.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace radians_to_degrees_test
{

static_assert(hamon::is_same<float,       decltype(hamon::radians_to_degrees(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::radians_to_degrees(0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::radians_to_degrees(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::radians_to_degrees(0   ))>::value, "");

template <typename T>
void RadiansToDegreesTestFloat(void)
{
	HAMON_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto pi  = hamon::numbers::pi_fn<T>();
	
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(   0.0), hamon::radians_to_degrees(pi * T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  90.0), hamon::radians_to_degrees(pi * T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 180.0), hamon::radians_to_degrees(pi * T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 270.0), hamon::radians_to_degrees(pi * T( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 360.0), hamon::radians_to_degrees(pi * T( 2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 540.0), hamon::radians_to_degrees(pi * T( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 720.0), hamon::radians_to_degrees(pi * T( 4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( -90.0), hamon::radians_to_degrees(pi * T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-180.0), hamon::radians_to_degrees(pi * T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-270.0), hamon::radians_to_degrees(pi * T(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-360.0), hamon::radians_to_degrees(pi * T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-540.0), hamon::radians_to_degrees(pi * T(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-720.0), hamon::radians_to_degrees(pi * T(-4.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::radians_to_degrees(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::radians_to_degrees(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::radians_to_degrees(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::radians_to_degrees(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::radians_to_degrees(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::radians_to_degrees(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::radians_to_degrees(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::radians_to_degrees(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::radians_to_degrees(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::radians_to_degrees(-nan)));
}

template <typename T>
void RadiansToDegreesTestSignedInt(void)
{
	HAMON_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(   0.000000000000, hamon::radians_to_degrees(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  57.295779513082, hamon::radians_to_degrees(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 114.591559026164, hamon::radians_to_degrees(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 171.887338539246, hamon::radians_to_degrees(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 229.183118052329, hamon::radians_to_degrees(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 286.478897565411, hamon::radians_to_degrees(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 343.774677078493, hamon::radians_to_degrees(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 401.070456591576, hamon::radians_to_degrees(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 458.366236104658, hamon::radians_to_degrees(T( 8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 515.662015617740, hamon::radians_to_degrees(T( 9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(- 57.295779513082, hamon::radians_to_degrees(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-114.591559026164, hamon::radians_to_degrees(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-171.887338539246, hamon::radians_to_degrees(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-229.183118052329, hamon::radians_to_degrees(T(-4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-286.478897565411, hamon::radians_to_degrees(T(-5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-343.774677078493, hamon::radians_to_degrees(T(-6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-401.070456591576, hamon::radians_to_degrees(T(-7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-458.366236104658, hamon::radians_to_degrees(T(-8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-515.662015617740, hamon::radians_to_degrees(T(-9)), error);
}

template <typename T>
void RadiansToDegreesTestUnsignedInt(void)
{
	HAMON_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.000000000000, hamon::radians_to_degrees(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 57.295779513082, hamon::radians_to_degrees(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(114.591559026164, hamon::radians_to_degrees(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(171.887338539246, hamon::radians_to_degrees(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(229.183118052329, hamon::radians_to_degrees(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(286.478897565411, hamon::radians_to_degrees(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(343.774677078493, hamon::radians_to_degrees(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(401.070456591576, hamon::radians_to_degrees(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(458.366236104658, hamon::radians_to_degrees(T( 8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(515.662015617740, hamon::radians_to_degrees(T( 9)), error);
}

GTEST_TEST(CMathTest, RadiansToDegreesTest)
{
	RadiansToDegreesTestFloat<float>();
	RadiansToDegreesTestFloat<double>();
	RadiansToDegreesTestFloat<long double>();

//	RadiansToDegreesTestSignedInt<int>();
	RadiansToDegreesTestSignedInt<signed char>();
//	RadiansToDegreesTestSignedInt<short>();
	RadiansToDegreesTestSignedInt<long>();
//	RadiansToDegreesTestSignedInt<long long>();

	RadiansToDegreesTestUnsignedInt<unsigned int>();
//	RadiansToDegreesTestUnsignedInt<unsigned char>();
	RadiansToDegreesTestUnsignedInt<unsigned short>();
//	RadiansToDegreesTestUnsignedInt<unsigned long>();
	RadiansToDegreesTestUnsignedInt<unsigned long long>();
}

}	// namespace radians_to_degrees_test

}	// namespace hamon_cmath_test
