/**
 *	@file	unit_test_cmath_lgamma.cpp
 *
 *	@brief	lgamma のテスト
 */

#include <hamon/cmath/lgamma.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace lgamma_test
{

static_assert(hamon::is_same<float,       decltype(hamon::lgamma(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::lgammaf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lgamma(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lgamma(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lgamma(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lgammal(0.0l))>::value, "");

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
	return 0.000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 0.000000001;
}

template <typename T>
void LgammaTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57236494292470008707, (double)hamon::lgamma(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.12078223763524522235, (double)hamon::lgamma(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.28468287047291915963, (double)hamon::lgamma(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.69314718055994530942, (double)hamon::lgamma(T( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.79175946922805500081, (double)hamon::lgamma(T( 4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.17805383034794561965, (double)hamon::lgamma(T( 5.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.26551212348464539649, (double)hamon::lgamma(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86004701537648101451, (double)hamon::lgamma(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.05624371649767405067, (double)hamon::lgamma(T(-2.5)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(hamon::lgamma(T( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(hamon::lgamma(T( 2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan (hamon::lgamma(nan)));
}

template <typename T>
void LgammaTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.69314718055994530942, (double)hamon::lgamma(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.79175946922805500081, (double)hamon::lgamma(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.17805383034794561965, (double)hamon::lgamma(T( 5)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(T( 0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(hamon::lgamma(T( 1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(hamon::lgamma(T( 2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(T(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(T(-2))));
}

template <typename T>
void LgammaTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.69314718055994530942, (double)hamon::lgamma(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.79175946922805500081, (double)hamon::lgamma(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.17805383034794561965, (double)hamon::lgamma(T( 5)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf (hamon::lgamma(T( 0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(hamon::lgamma(T( 1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(hamon::lgamma(T( 2))));
}

GTEST_TEST(CMathTest, LgammaTest)
{
	LgammaTestFloat<float>();
	LgammaTestFloat<double>();
	LgammaTestFloat<long double>();

	LgammaTestSignedInt<int>();
//	LgammaTestSignedInt<signed char>();
	LgammaTestSignedInt<short>();
//	LgammaTestSignedInt<long>();
	LgammaTestSignedInt<long long>();

//	LgammaTestUnsignedInt<unsigned int>();
	LgammaTestUnsignedInt<unsigned char>();
//	LgammaTestUnsignedInt<unsigned short>();
	LgammaTestUnsignedInt<unsigned long>();
//	LgammaTestUnsignedInt<unsigned long long>();
}

}	// namespace lgamma_test

}	// namespace hamon_cmath_test
