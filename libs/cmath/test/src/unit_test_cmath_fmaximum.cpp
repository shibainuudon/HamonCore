/**
 *	@file	unit_test_cmath_fmaximum.cpp
 *
 *	@brief	fmaximum のテスト
 */

#include <hamon/cmath/fmaximum.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fmaximum_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fmaximum(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FMaximumTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR auto nan1    = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2    = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1    = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2    = hamon::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf3    = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmaximum(T1( 0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fmaximum(T1( 0.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fmaximum(T1( 1.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::fmaximum(T1( 2.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::fmaximum(T1( 1.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmaximum(T1(-0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmaximum(T1( 0.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fmaximum(T1(-0.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fmaximum(T1(-1.5), T2(-0.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum( inf1,     T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum( T1(3.5),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.5,  hamon::fmaximum(-inf1,     T2( 4.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5.5,  hamon::fmaximum( T1(5.5), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum( inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum(-inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum( inf1,    -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fmaximum(-inf1,    -inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fmaximum(T1(+0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmaximum(T1(+0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fmaximum(T1(-0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::fmaximum(T1(-0.0), T2(-0.0))));

	// 引数のいずれかが NaN の場合、 NaN を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmaximum(nan1,    T2(0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmaximum(T1(0.5), nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmaximum(nan1,    nan2)));

	// -0.0 と +0.0 の比較では、 +0.0 を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fmaximum(T1(-0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmaximum(T1(-0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fmaximum(T1(+0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmaximum(T1(+0.0), T2(-0.0))));
}

template <typename T1, typename T2>
void FMaximumTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmaximum(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmaximum(T1( 0), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmaximum(T1( 1), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fmaximum(T1( 2), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fmaximum(T1( 1), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmaximum(T1(-1), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmaximum(T1( 1), T2(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, hamon::fmaximum(T1(-2), T2(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::fmaximum(T1(-4), T2(-3)));
}

template <typename T1, typename T2>
void FMaximumTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmaximum(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::fmaximum(T1( 1), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::fmaximum(T1(11), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::fmaximum(T1(20), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::fmaximum(T1(11), T2(21)));
}

GTEST_TEST(CMathTest, FMaximumTest)
{
	FMaximumTestFloat<float,       float>();
	FMaximumTestFloat<float,       double>();
//	FMaximumTestFloat<float,       long double>();
	FMaximumTestFloat<double,      float>();
	FMaximumTestFloat<double,      double>();
	FMaximumTestFloat<double,      long double>();
//	FMaximumTestFloat<long double, float>();
	FMaximumTestFloat<long double, double>();
	FMaximumTestFloat<long double, long double>();

	FMaximumTestSignedInt<int,         int>();
//	FMaximumTestSignedInt<int,         float>();
	FMaximumTestSignedInt<int,         double>();
//	FMaximumTestSignedInt<int,         long double>();
	FMaximumTestSignedInt<float,       int>();
//	FMaximumTestSignedInt<double,      int>();
	FMaximumTestSignedInt<long double, int>();

	FMaximumTestUnsignedInt<unsigned int, unsigned int>();
//	FMaximumTestUnsignedInt<unsigned int, float>();
	FMaximumTestUnsignedInt<unsigned int, double>();
	FMaximumTestUnsignedInt<unsigned int, long double>();
	FMaximumTestUnsignedInt<float,        unsigned int>();
//	FMaximumTestUnsignedInt<double,       unsigned int>();
	FMaximumTestUnsignedInt<long double,  unsigned int>();
}

}	// namespace fmaximum_test

}	// namespace hamon_cmath_test
