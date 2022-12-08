/**
 *	@file	unit_test_cmath_frac.cpp
 *
 *	@brief	frac のテスト
 */

#include <hamon/cmath/frac.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace frac_test
{

static_assert(std::is_same<float,       decltype(hamon::frac(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::frac(0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::frac(0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::frac(0   ))>::value, "");

template <typename T>
void FracTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.8,    (double)hamon::frac(T(-1.2)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9,    (double)hamon::frac(T(-1.1)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,    (double)hamon::frac(T(-1.0)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1,    (double)hamon::frac(T(-0.9)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2,    (double)hamon::frac(T(-0.8)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5,    (double)hamon::frac(T(-0.5)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.8,    (double)hamon::frac(T(-0.2)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9,    (double)hamon::frac(T(-0.1)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,    (double)hamon::frac(T( 0.0)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1,    (double)hamon::frac(T( 0.1)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.123,  (double)hamon::frac(T( 0.123)),  error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2,    (double)hamon::frac(T( 0.2)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5,    (double)hamon::frac(T( 0.5)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.8,    (double)hamon::frac(T( 0.8)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9,    (double)hamon::frac(T( 0.9)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.99,   (double)hamon::frac(T( 0.99)),   error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.999,  (double)hamon::frac(T( 0.999)),  error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,    (double)hamon::frac(T( 1.0)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1,    (double)hamon::frac(T( 1.1)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2,    (double)hamon::frac(T( 1.2)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2525, (double)hamon::frac(T( 1.2525)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.8,    (double)hamon::frac(T( 1.8)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9,    (double)hamon::frac(T( 1.9)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,    (double)hamon::frac(T( 2.0)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1,    (double)hamon::frac(T( 2.1)),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2,    (double)hamon::frac(T( 2.2)),    error);

	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::frac(T( inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::frac(T(-inf)));

	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::frac(T( nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::frac(T(-nan))));
}

template <typename T>
void FracTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T(lowest)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T(max)));
}

template <typename T>
void FracTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::frac(T(max)));
}

GTEST_TEST(CMathTest, FracTest)
{
	FracTestFloat<float>();
	FracTestFloat<double>();
	FracTestFloat<long double>();

	FracTestSignedInt<int>();
	FracTestSignedInt<signed char>();
//	FracTestSignedInt<short>();
	FracTestSignedInt<long>();
//	FracTestSignedInt<long long>();

	FracTestUnsignedInt<unsigned int>();
//	FracTestUnsignedInt<unsigned char>();
	FracTestUnsignedInt<unsigned short>();
//	FracTestUnsignedInt<unsigned long>();
	FracTestUnsignedInt<unsigned long long>();
}

}	// namespace frac_test

}	// namespace hamon_cmath_test
