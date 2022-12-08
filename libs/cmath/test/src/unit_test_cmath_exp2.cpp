/**
 *	@file	unit_test_cmath_exp2.cpp
 *
 *	@brief	exp2 のテスト
 */

#include <hamon/cmath/exp2.hpp>
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

namespace exp2_test
{

static_assert(std::is_same<float,       decltype(hamon::exp2(0.0f))>::value, "");
static_assert(std::is_same<float,       decltype(hamon::exp2f(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::exp2(0.0 ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::exp2(0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::exp2(0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::exp2l(0.0l))>::value, "");

template <typename T>
double exp2_error();

template <>
inline HAMON_CXX11_CONSTEXPR double exp2_error<float>()
{
	return 0.00001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double exp2_error<double>()
{
	return 0.00000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double exp2_error<long double>()
{
	return 0.00000000001;
}

template <typename T>
void Exp2TestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = exp2_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::exp2(T(+0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::exp2(T(-0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.09050773266, (double)hamon::exp2(T( 0.125)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.18920711500, (double)hamon::exp2(T( 0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.41421356237, (double)hamon::exp2(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.68179283051, (double)hamon::exp2(T( 0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.00000000000, (double)hamon::exp2(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.37841423000, (double)hamon::exp2(T( 1.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.82842712474, (double)hamon::exp2(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4.00000000000, (double)hamon::exp2(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5.65685424949, (double)hamon::exp2(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 8.00000000000, (double)hamon::exp2(T( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(11.31370849898, (double)hamon::exp2(T( 3.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(16.00000000000, (double)hamon::exp2(T( 4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(22.62741699796, (double)hamon::exp2(T( 4.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(32.00000000000, (double)hamon::exp2(T( 5.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.91700404320, (double)hamon::exp2(T(-0.125)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.84089641525, (double)hamon::exp2(T(-0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::exp2(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.59460355750, (double)hamon::exp2(T(-0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)hamon::exp2(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.25000000000, (double)hamon::exp2(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.17677669529, (double)hamon::exp2(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.12500000000, (double)hamon::exp2(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.08838834764, (double)hamon::exp2(T(-3.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.06250000000, (double)hamon::exp2(T(-4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.04419417382, (double)hamon::exp2(T(-4.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.03125000000, (double)hamon::exp2(T(-5.0)), error);
	
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0,   hamon::exp2(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::exp2(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::exp2(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::exp2(-nan)));
}

template <typename T>
void Exp2TestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.03125, hamon::exp2(T(-5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0625,  hamon::exp2(T(-4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.125,   hamon::exp2(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.25,    hamon::exp2(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.5,     hamon::exp2(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,     hamon::exp2(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0,     hamon::exp2(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4.0,     hamon::exp2(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 8.0,     hamon::exp2(T( 3)), error);
}

template <typename T>
void Exp2TestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, hamon::exp2(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0, hamon::exp2(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4.0, hamon::exp2(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 8.0, hamon::exp2(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(16.0, hamon::exp2(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(32.0, hamon::exp2(T( 5)), error);
}

GTEST_TEST(CMathTest, Exp2Test)
{
	Exp2TestFloat<float>();
	Exp2TestFloat<double>();
	Exp2TestFloat<long double>();

	Exp2TestSignedInt<int>();
	Exp2TestSignedInt<signed char>();
//	Exp2TestSignedInt<short>();
	Exp2TestSignedInt<long>();
//	Exp2TestSignedInt<long long>();

	Exp2TestUnsignedInt<unsigned int>();
//	Exp2TestUnsignedInt<unsigned char>();
	Exp2TestUnsignedInt<unsigned short>();
//	Exp2TestUnsignedInt<unsigned long>();
	Exp2TestUnsignedInt<unsigned long long>();
}

}	// namespace exp2_test

}	// namespace hamon_cmath_test
