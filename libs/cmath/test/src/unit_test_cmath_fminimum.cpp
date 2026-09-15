/**
 *	@file	unit_test_cmath_fminimum.cpp
 *
 *	@brief	fminimum のテスト
 */

#include <hamon/cmath/fminimum.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fminimum_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fminimum(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FMinimumTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR auto nan1    = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2    = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1    = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2    = hamon::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf3    = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fminimum(T1( 0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fminimum(T1( 0.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fminimum(T1( 1.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fminimum(T1( 2.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fminimum(T1( 1.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fminimum(T1(-0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fminimum(T1( 0.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::fminimum(T1(-0.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::fminimum(T1(-1.5), T2(-0.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5,  hamon::fminimum( inf1,     T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.5,  hamon::fminimum( T1(3.5),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum(-inf1,     T2( 4.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum( T1(5.5), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fminimum( inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum(-inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum( inf1,    -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum(-inf1,    -inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fminimum(T1(+0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fminimum(T1(+0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fminimum(T1(-0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::fminimum(T1(-0.0), T2(-0.0))));

	// 引数のいずれかが NaN の場合、 NaN を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fminimum(nan1,    T2(0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fminimum(T1(0.5), nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fminimum(nan1,    nan2)));

	// -0.0 と +0.0 の比較では、 -0.0 を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero( hamon::fminimum(T1(-0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::signbit(hamon::fminimum(T1(-0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero( hamon::fminimum(T1(+0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::signbit(hamon::fminimum(T1(+0.0), T2(-0.0))));
}

template <typename T1, typename T2>
void FMinimumTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fminimum(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fminimum(T1( 0), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fminimum(T1( 1), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fminimum(T1( 2), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fminimum(T1( 1), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::fminimum(T1(-1), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::fminimum(T1( 1), T2(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::fminimum(T1(-2), T2(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, hamon::fminimum(T1(-4), T2(-3)));
}

template <typename T1, typename T2>
void FMinimumTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fminimum(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fminimum(T1( 1), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fminimum(T1(10), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::fminimum(T1(20), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::fminimum(T1(11), T2(20)));
}

GTEST_TEST(CMathTest, FMinimumTest)
{
	FMinimumTestFloat<float,       float>();
	FMinimumTestFloat<float,       double>();
//	FMinimumTestFloat<float,       long double>();
	FMinimumTestFloat<double,      float>();
	FMinimumTestFloat<double,      double>();
	FMinimumTestFloat<double,      long double>();
//	FMinimumTestFloat<long double, float>();
	FMinimumTestFloat<long double, double>();
	FMinimumTestFloat<long double, long double>();

	FMinimumTestSignedInt<int,         int>();
//	FMinimumTestSignedInt<int,         float>();
	FMinimumTestSignedInt<int,         double>();
//	FMinimumTestSignedInt<int,         long double>();
	FMinimumTestSignedInt<float,       int>();
//	FMinimumTestSignedInt<double,      int>();
	FMinimumTestSignedInt<long double, int>();

	FMinimumTestUnsignedInt<unsigned int, unsigned int>();
//	FMinimumTestUnsignedInt<unsigned int, float>();
	FMinimumTestUnsignedInt<unsigned int, double>();
	FMinimumTestUnsignedInt<unsigned int, long double>();
	FMinimumTestUnsignedInt<float,        unsigned int>();
//	FMinimumTestUnsignedInt<double,       unsigned int>();
	FMinimumTestUnsignedInt<long double,  unsigned int>();
}

}	// namespace fminimum_test

}	// namespace hamon_cmath_test
