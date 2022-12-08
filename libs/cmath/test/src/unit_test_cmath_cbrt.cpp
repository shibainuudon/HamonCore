/**
 *	@file	unit_test_cmath_cbrt.cpp
 *
 *	@brief	cbrt のテスト
 */

#include <hamon/cmath/cbrt.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace cbrt_test
{

static_assert(std::is_same<float,       decltype(hamon::cbrt(0.0f))>::value, "");
static_assert(std::is_same<float,       decltype(hamon::cbrtf(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::cbrt(0.0 ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::cbrt(0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::cbrt(0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::cbrtl(0.0l))>::value, "");

template <typename T>
double cbrt_error();

template <>
inline HAMON_CXX11_CONSTEXPR double cbrt_error<float>()
{
	return 0.00001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double cbrt_error<double>()
{
	return 0.0000000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double cbrt_error<long double>()
{
	return 0.0000000000001;
}

template <typename T>
void CbrtTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = cbrt_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)hamon::cbrt(T(   0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.5, (double)hamon::cbrt(T(   0.125)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, (double)hamon::cbrt(T(   1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5, (double)hamon::cbrt(T(   3.375)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0, (double)hamon::cbrt(T(   8.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0, (double)hamon::cbrt(T(  27.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4.0, (double)hamon::cbrt(T(  64.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5.0, (double)hamon::cbrt(T( 125.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.0, (double)hamon::cbrt(T( 216.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 7.0, (double)hamon::cbrt(T( 343.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 8.0, (double)hamon::cbrt(T( 512.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 9.0, (double)hamon::cbrt(T( 729.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.5, (double)hamon::cbrt(T(  -0.125)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0, (double)hamon::cbrt(T(  -1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5, (double)hamon::cbrt(T(  -3.375)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0, (double)hamon::cbrt(T(  -8.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.0, (double)hamon::cbrt(T( -27.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-4.0, (double)hamon::cbrt(T( -64.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-5.0, (double)hamon::cbrt(T(-125.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-6.0, (double)hamon::cbrt(T(-216.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-7.0, (double)hamon::cbrt(T(-343.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-8.0, (double)hamon::cbrt(T(-512.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-9.0, (double)hamon::cbrt(T(-729.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(+0.0), hamon::cbrt(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-0.0), hamon::cbrt(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf,    hamon::cbrt(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf,    hamon::cbrt(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cbrt(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cbrt(-nan)));
}

template <typename T>
void CbrtTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000000000000000000, hamon::cbrt(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0000000000000000000000000000000, hamon::cbrt(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.2599210498948731647672106072782, hamon::cbrt(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4422495703074083823216383107801, hamon::cbrt(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5874010519681994747517056392723, hamon::cbrt(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7099759466766969893531088725439, hamon::cbrt(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.8171205928321396588912117563273, hamon::cbrt(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.9129311827723891011991168395488, hamon::cbrt(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0000000000000000000000000000000, hamon::cbrt(T( 8)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0000000000000000000000000000000, hamon::cbrt(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.2599210498948731647672106072782, hamon::cbrt(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4422495703074083823216383107801, hamon::cbrt(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5874010519681994747517056392723, hamon::cbrt(T(-4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.7099759466766969893531088725439, hamon::cbrt(T(-5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.8171205928321396588912117563273, hamon::cbrt(T(-6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.9129311827723891011991168395488, hamon::cbrt(T(-7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0000000000000000000000000000000, hamon::cbrt(T(-8)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::cbrt(T(0)));
}

template <typename T>
void CbrtTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000000000000000000, hamon::cbrt(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0000000000000000000000000000000, hamon::cbrt(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.2599210498948731647672106072782, hamon::cbrt(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4422495703074083823216383107801, hamon::cbrt(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5874010519681994747517056392723, hamon::cbrt(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7099759466766969893531088725439, hamon::cbrt(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.8171205928321396588912117563273, hamon::cbrt(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.9129311827723891011991168395488, hamon::cbrt(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0000000000000000000000000000000, hamon::cbrt(T( 8)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::cbrt(T(0)));
}

GTEST_TEST(CMathTest, CbrtTest)
{
	CbrtTestFloat<float>();
	CbrtTestFloat<double>();
	CbrtTestFloat<long double>();

	CbrtTestSignedInt<int>();
	CbrtTestSignedInt<signed char>();
//	CbrtTestSignedInt<short>();
	CbrtTestSignedInt<long>();
//	CbrtTestSignedInt<long long>();

	CbrtTestUnsignedInt<unsigned int>();
//	CbrtTestUnsignedInt<unsigned char>();
	CbrtTestUnsignedInt<unsigned short>();
//	CbrtTestUnsignedInt<unsigned long>();
	CbrtTestUnsignedInt<unsigned long long>();
}

}	// namespace cbrt_test

}	// namespace hamon_cmath_test
