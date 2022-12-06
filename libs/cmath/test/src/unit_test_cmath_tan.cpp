﻿/**
 *	@file	unit_test_cmath_tan.cpp
 *
 *	@brief	tan のテスト
 */

#include <hamon/cmath/tan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace tan_test
{

static_assert(std::is_same<float,       decltype(hamon::tan(0.0f))>::value, "");
static_assert(std::is_same<float,       decltype(hamon::tanf(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::tan(0.0 ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::tan(0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::tan(0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::tanl(0.0l))>::value, "");

template <typename T>
void TanTestFloat(double error)
{
	HAMON_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	EXPECT_NEAR( 0.00000000000, (double)hamon::tan(T( 0.0)), error);
	EXPECT_NEAR( 0.10033467208, (double)hamon::tan(T( 0.1)), error);
	EXPECT_NEAR( 0.20271003550, (double)hamon::tan(T( 0.2)), error);
	EXPECT_NEAR( 0.30933624961, (double)hamon::tan(T( 0.3)), error);
	EXPECT_NEAR( 0.54630248984, (double)hamon::tan(T( 0.5)), error);
	EXPECT_NEAR( 1.02963855705, (double)hamon::tan(T( 0.8)), error);
	EXPECT_NEAR( 1.55740772465, (double)hamon::tan(T( 1.0)), error);
	EXPECT_NEAR( 14.1014199472, (double)hamon::tan(T( 1.5)), error);
	EXPECT_NEAR(-34.2325327356, (double)hamon::tan(T( 1.6)), error);
	EXPECT_NEAR(-7.69660213946, (double)hamon::tan(T( 1.7)), error);
	EXPECT_NEAR(-4.28626167463, (double)hamon::tan(T( 1.8)), error);
	EXPECT_NEAR(-2.92709751468, (double)hamon::tan(T( 1.9)), error);
	EXPECT_NEAR(-2.18503986326, (double)hamon::tan(T( 2.0)), error);
	EXPECT_NEAR(-0.74702229723, (double)hamon::tan(T( 2.5)), error);
	EXPECT_NEAR(-0.14254654307, (double)hamon::tan(T( 3.0)), error);
	EXPECT_NEAR( 0.37458564015, (double)hamon::tan(T( 3.5)), error);
	EXPECT_NEAR(-0.10033467208, (double)hamon::tan(T(-0.1)), error);
	EXPECT_NEAR(-0.20271003550, (double)hamon::tan(T(-0.2)), error);
	EXPECT_NEAR(-0.30933624961, (double)hamon::tan(T(-0.3)), error);
	EXPECT_NEAR(-0.54630248984, (double)hamon::tan(T(-0.5)), error);
	EXPECT_NEAR(-1.02963855705, (double)hamon::tan(T(-0.8)), error);
	EXPECT_NEAR(-1.55740772465, (double)hamon::tan(T(-1.0)), error);
	EXPECT_NEAR(-14.1014199472, (double)hamon::tan(T(-1.5)), error);
	EXPECT_NEAR( 34.2325327356, (double)hamon::tan(T(-1.6)), error);
	EXPECT_NEAR( 7.69660213946, (double)hamon::tan(T(-1.7)), error);
	EXPECT_NEAR( 4.28626167463, (double)hamon::tan(T(-1.8)), error);
	EXPECT_NEAR( 2.92709751468, (double)hamon::tan(T(-1.9)), error);
	EXPECT_NEAR( 2.18503986326, (double)hamon::tan(T(-2.0)), error);
	EXPECT_NEAR( 0.74702229723, (double)hamon::tan(T(-2.5)), error);
	EXPECT_NEAR( 0.14254654307, (double)hamon::tan(T(-3.0)), error);
	EXPECT_NEAR(-0.37458564015, (double)hamon::tan(T(-3.5)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::tan(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::tan(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::tan(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::tan(T(-0.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tan(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tan(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tan(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tan(-inf)));
}

template <typename T>
void TanTestSignedInt(void)
{
	HAMON_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR( 0.00000000000, hamon::tan(T( 0)), error);
	EXPECT_NEAR( 1.55740772465, hamon::tan(T( 1)), error);
	EXPECT_NEAR(-1.55740772465, hamon::tan(T(-1)), error);
	EXPECT_NEAR(-2.18503986326, hamon::tan(T( 2)), error);
	EXPECT_NEAR( 2.18503986326, hamon::tan(T(-2)), error);
	EXPECT_NEAR(-0.14254654307, hamon::tan(T( 3)), error);
	EXPECT_NEAR( 0.14254654307, hamon::tan(T(-3)), error);
}

template <typename T>
void TanTestUnsignedInt(void)
{
	HAMON_CONSTEXPR double error = 0.00000000001;

	EXPECT_NEAR( 0.00000000000, hamon::tan(T(0)), error);
	EXPECT_NEAR( 1.55740772465, hamon::tan(T(1)), error);
	EXPECT_NEAR(-2.18503986326, hamon::tan(T(2)), error);
	EXPECT_NEAR(-0.14254654307, hamon::tan(T(3)), error);
}

GTEST_TEST(CMathTest, TanTest)
{
	TanTestFloat<float>(0.0001);
	TanTestFloat<double>(0.0000000001);
	TanTestFloat<long double>(0.0000000001);

//	TanTestSignedInt<int>();
	TanTestSignedInt<signed char>();
//	TanTestSignedInt<short>();
	TanTestSignedInt<long>();
//	TanTestSignedInt<long long>();

	TanTestUnsignedInt<unsigned int>();
//	TanTestUnsignedInt<unsigned char>();
	TanTestUnsignedInt<unsigned short>();
//	TanTestUnsignedInt<unsigned long>();
	TanTestUnsignedInt<unsigned long long>();
}

}	// namespace tan_test

}	// namespace hamon_cmath_test
