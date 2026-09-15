/**
 *	@file	unit_test_cmath_fminimum_num.cpp
 *
 *	@brief	fminimum_num のテスト
 */

#include <hamon/cmath/fminimum_num.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fminimum_num_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fminimum_num(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum_num(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum_num(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum_num(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum_num(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum_num(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum_num(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum_num(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum_num(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum_num(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum_num(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum_num(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum_num(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum_num(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminimum_num(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fminimum_num(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FMinimumNumTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR auto nan1    = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2    = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1    = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2    = hamon::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf3    = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fminimum_num(T1( 0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fminimum_num(T1( 0.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fminimum_num(T1( 1.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fminimum_num(T1( 2.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fminimum_num(T1( 1.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fminimum_num(T1(-0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fminimum_num(T1( 0.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::fminimum_num(T1(-0.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::fminimum_num(T1(-1.5), T2(-0.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5,  hamon::fminimum_num( inf1,     T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.5,  hamon::fminimum_num( T1(3.5),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum_num(-inf1,     T2( 4.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum_num( T1(5.5), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fminimum_num( inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum_num(-inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum_num( inf1,    -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fminimum_num(-inf1,    -inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fminimum_num(T1(+0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fminimum_num(T1(+0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fminimum_num(T1(-0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::fminimum_num(T1(-0.0), T2(-0.0))));

	// 引数の1つが NaN の場合 NaN でない方を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fminimum_num(nan1,    T2(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fminimum_num(T1(0.5), nan2));

	// 引数が2つとも NaN の場合 NaN を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fminimum_num(nan1, nan2)));

	// -0.0 と +0.0 の比較では、 -0.0 を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero( hamon::fminimum_num(T1(-0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::signbit(hamon::fminimum_num(T1(-0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero( hamon::fminimum_num(T1(+0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::signbit(hamon::fminimum_num(T1(+0.0), T2(-0.0))));
}

template <typename T1, typename T2>
void FMinimumNumTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fminimum_num(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fminimum_num(T1( 0), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fminimum_num(T1( 1), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fminimum_num(T1( 2), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fminimum_num(T1( 1), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::fminimum_num(T1(-1), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::fminimum_num(T1( 1), T2(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::fminimum_num(T1(-2), T2(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, hamon::fminimum_num(T1(-4), T2(-3)));
}

template <typename T1, typename T2>
void FMinimumNumTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fminimum_num(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fminimum_num(T1( 1), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fminimum_num(T1(10), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::fminimum_num(T1(20), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::fminimum_num(T1(11), T2(20)));
}

GTEST_TEST(CMathTest, FMinimumNumTest)
{
	FMinimumNumTestFloat<float,       float>();
	FMinimumNumTestFloat<float,       double>();
//	FMinimumNumTestFloat<float,       long double>();
	FMinimumNumTestFloat<double,      float>();
	FMinimumNumTestFloat<double,      double>();
	FMinimumNumTestFloat<double,      long double>();
//	FMinimumNumTestFloat<long double, float>();
	FMinimumNumTestFloat<long double, double>();
	FMinimumNumTestFloat<long double, long double>();

	FMinimumNumTestSignedInt<int,         int>();
//	FMinimumNumTestSignedInt<int,         float>();
	FMinimumNumTestSignedInt<int,         double>();
//	FMinimumNumTestSignedInt<int,         long double>();
	FMinimumNumTestSignedInt<float,       int>();
//	FMinimumNumTestSignedInt<double,      int>();
	FMinimumNumTestSignedInt<long double, int>();

	FMinimumNumTestUnsignedInt<unsigned int, unsigned int>();
//	FMinimumNumTestUnsignedInt<unsigned int, float>();
	FMinimumNumTestUnsignedInt<unsigned int, double>();
	FMinimumNumTestUnsignedInt<unsigned int, long double>();
	FMinimumNumTestUnsignedInt<float,        unsigned int>();
//	FMinimumNumTestUnsignedInt<double,       unsigned int>();
	FMinimumNumTestUnsignedInt<long double,  unsigned int>();
}

}	// namespace fminimum_num_test

}	// namespace hamon_cmath_test
