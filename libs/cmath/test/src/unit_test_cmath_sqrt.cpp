/**
 *	@file	unit_test_cmath_sqrt.cpp
 *
 *	@brief	sqrt のテスト
 */

#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace sqrt_test
{

static_assert(std::is_same<float,       decltype(hamon::sqrt(0.0f))>::value, "");
static_assert(std::is_same<float,       decltype(hamon::sqrtf(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::sqrt(0.0 ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::sqrt(0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::sqrt(0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::sqrtl(0.0l))>::value, "");

template <typename T>
void SqrtTestFloat(void)
{
	HAMON_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	HAMON_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::sqrt(T(  0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)hamon::sqrt(T(  0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::sqrt(T(  1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.50000000000, (double)hamon::sqrt(T(  2.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.41421356237, (double)hamon::sqrt(T(  2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.73205080757, (double)hamon::sqrt(T(  3.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.00000000000, (double)hamon::sqrt(T(100.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1000.00000000000, (double)hamon::sqrt(T(1000000.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::sqrt(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::sqrt(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::sqrt(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::sqrt(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::sqrt(+inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(-eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(-nan)));
}

template <typename T>
void SqrtTestSignedInt(void)
{
	HAMON_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, hamon::sqrt(T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, hamon::sqrt(T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.41421356237, hamon::sqrt(T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.73205080757, hamon::sqrt(T(  3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.00000000000, hamon::sqrt(T(100)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(T(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(T(-2))));
}

template <typename T>
void SqrtTestUnsignedInt(void)
{
	HAMON_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, hamon::sqrt(T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, hamon::sqrt(T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.41421356237, hamon::sqrt(T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.73205080757, hamon::sqrt(T(  3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.00000000000, hamon::sqrt(T(100)), error);
}

GTEST_TEST(CMathTest, SqrtTest)
{
	SqrtTestFloat<float>();
	SqrtTestFloat<double>();
	SqrtTestFloat<long double>();

//	SqrtTestSignedInt<int>();
	SqrtTestSignedInt<signed char>();
//	SqrtTestSignedInt<short>();
	SqrtTestSignedInt<long>();
//	SqrtTestSignedInt<long long>();

	SqrtTestUnsignedInt<unsigned int>();
//	SqrtTestUnsignedInt<unsigned char>();
	SqrtTestUnsignedInt<unsigned short>();
//	SqrtTestUnsignedInt<unsigned long>();
	SqrtTestUnsignedInt<unsigned long long>();
}

}	// namespace sqrt_test

}	// namespace hamon_cmath_test
