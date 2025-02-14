/**
 *	@file	unit_test_cmath_tgamma.cpp
 *
 *	@brief	tgamma のテスト
 */

#include <hamon/cmath/tgamma.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace tgamma_test
{

static_assert(hamon::is_same<float,       decltype(hamon::tgamma(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::tgammaf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::tgamma(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::tgamma(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::tgamma(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::tgammal(0.0l))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 0.00001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 0.000000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 0.000000000001;
}

template <typename T>
void TgammaTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.77245385090551602729, (double)hamon::tgamma(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000000000000, (double)hamon::tgamma(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.88622692545275801365, (double)hamon::tgamma(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000000000000, (double)hamon::tgamma(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.32934038817913702047, (double)hamon::tgamma(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.00000000000000000000, (double)hamon::tgamma(T( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.32335097044784255118, (double)hamon::tgamma(T( 3.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.00000000000000000000, (double)hamon::tgamma(T( 4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(11.63172839656744892914, (double)hamon::tgamma(T( 4.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(24.00000000000000000000, (double)hamon::tgamma(T( 5.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.54490770181103205459, (double)hamon::tgamma(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.36327180120735470306, (double)hamon::tgamma(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.94530872048294188123, (double)hamon::tgamma(T(-2.5)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf(hamon::tgamma(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf(hamon::tgamma(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-4.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-5.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf(hamon::tgamma(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(-nan)));
}

template <typename T>
void TgammaTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::tgamma(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::tgamma(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::tgamma(T( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::tgamma(T( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::tgamma(T( 5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf(hamon::tgamma(T( 0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-3))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-4))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tgamma(T(-5))));
}

template <typename T>
void TgammaTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1, hamon::tgamma(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1, hamon::tgamma(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  2, hamon::tgamma(T( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  6, hamon::tgamma(T( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 24, hamon::tgamma(T( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(120, hamon::tgamma(T( 6)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf(hamon::tgamma(T( 0))));
}

GTEST_TEST(CMathTest, TgammaTest)
{
	TgammaTestFloat<float>();
	TgammaTestFloat<double>();
	TgammaTestFloat<long double>();

//	TgammaTestSignedInt<int>();
	TgammaTestSignedInt<signed char>();
//	TgammaTestSignedInt<short>();
	TgammaTestSignedInt<long>();
//	TgammaTestSignedInt<long long>();

	TgammaTestUnsignedInt<unsigned int>();
//	TgammaTestUnsignedInt<unsigned char>();
	TgammaTestUnsignedInt<unsigned short>();
//	TgammaTestUnsignedInt<unsigned long>();
	TgammaTestUnsignedInt<unsigned long long>();
}

}	// namespace tgamma_test

}	// namespace hamon_cmath_test
