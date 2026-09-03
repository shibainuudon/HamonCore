/**
 *	@file	unit_test_cmath_asin.cpp
 *
 *	@brief	asin のテスト
 */

#include <hamon/cmath/asin.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>	// HAMON_CXX11_CONSTEXPR_EXPECT_NEAR
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace asin_test
{

static_assert(hamon::is_same<float,       decltype(hamon::asin(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::asin(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::asin(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::asin(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::asinf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::asinl(0.0l))>::value, "");

template <typename T>
void AsinTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-15;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267948966192313216916397514420985846996876,  (double)hamon::asin(T(-1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.84806207898148100805294433899841808007336621326311, (double)hamon::asin(T(-0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.52359877559829887307710723054658381403286156656252, (double)hamon::asin(T(-0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.25268025514207865348565743699371097225219373309684, (double)hamon::asin(T(-0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000000000000000000000000000000000000, (double)hamon::asin(T( 0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.25268025514207865348565743699371097225219373309684, (double)hamon::asin(T( 0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.52359877559829887307710723054658381403286156656252, (double)hamon::asin(T( 0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.84806207898148100805294433899841808007336621326311, (double)hamon::asin(T( 0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267948966192313216916397514420985846996876,  (double)hamon::asin(T( 1.00)), error);

	// If the argument is ±0, it is returned unmodified.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::asin(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::asin(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::asin(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::asin(T(-0.0))));

	// If |num| > 1, a domain error occurs and NaN is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T(+1.0) + eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T(-1.0) - eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(-inf)));

	// if the argument is NaN, NaN is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(-nan)));
}

template <typename T>
void AsinTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-30;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000000000000000000000000000000000000, hamon::asin(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267948966192313216916397514420985846996876, hamon::asin(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267948966192313216916397514420985846996876, hamon::asin(T(-1)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T( 2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T(-2))));
}

template <typename T>
void AsinTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-30;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000000000000000000000, hamon::asin(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5707963267948966192313216916397514420985846996876, hamon::asin(T( 1)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T( 2))));
}

GTEST_TEST(CMathTest, AsinTest)
{
	AsinTestFloat<float>();
	AsinTestFloat<double>();
	AsinTestFloat<long double>();

	AsinTestSignedInt<int>();
//	AsinTestSignedInt<signed char>();
	AsinTestSignedInt<short>();
//	AsinTestSignedInt<long>();
	AsinTestSignedInt<long long>();

	AsinTestUnsignedInt<unsigned int>();
	AsinTestUnsignedInt<unsigned char>();
//	AsinTestUnsignedInt<unsigned short>();
	AsinTestUnsignedInt<unsigned long>();
//	AsinTestUnsignedInt<unsigned long long>();
}

}	// namespace asin_test

}	// namespace hamon_cmath_test
