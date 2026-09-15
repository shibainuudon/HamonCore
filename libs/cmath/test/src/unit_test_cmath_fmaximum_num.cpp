/**
 *	@file	unit_test_cmath_fmaximum_num.cpp
 *
 *	@brief	fmaximum_num のテスト
 */

#include <hamon/cmath/fmaximum_num.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fmaximum_num_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fmaximum_num(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum_num(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum_num(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum_num(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum_num(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum_num(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum_num(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum_num(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum_num(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum_num(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum_num(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum_num(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum_num(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum_num(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaximum_num(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmaximum_num(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FMaximumNumTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR auto nan1    = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2    = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1    = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2    = hamon::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf3    = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmaximum_num(T1( 0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fmaximum_num(T1( 0.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fmaximum_num(T1( 1.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::fmaximum_num(T1( 2.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::fmaximum_num(T1( 1.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmaximum_num(T1(-0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmaximum_num(T1( 0.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fmaximum_num(T1(-0.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fmaximum_num(T1(-1.5), T2(-0.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum_num( inf1,     T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum_num( T1(3.5),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.5,  hamon::fmaximum_num(-inf1,     T2( 4.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5.5,  hamon::fmaximum_num( T1(5.5), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum_num( inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum_num(-inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmaximum_num( inf1,    -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fmaximum_num(-inf1,    -inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fmaximum_num(T1(+0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmaximum_num(T1(+0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fmaximum_num(T1(-0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::fmaximum_num(T1(-0.0), T2(-0.0))));

	// 引数の1つが NaN の場合 NaN でない方を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmaximum_num(nan1,    T2(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmaximum_num(T1(0.5), nan2));

	// 引数が2つとも NaN の場合 NaN を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmaximum_num(nan1, nan2)));

	// -0.0 と +0.0 の比較では、 +0.0 を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fmaximum_num(T1(-0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmaximum_num(T1(-0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(  hamon::fmaximum_num(T1(+0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmaximum_num(T1(+0.0), T2(-0.0))));
}

template <typename T1, typename T2>
void FMaximumNumTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmaximum_num(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmaximum_num(T1( 0), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmaximum_num(T1( 1), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fmaximum_num(T1( 2), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fmaximum_num(T1( 1), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmaximum_num(T1(-1), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmaximum_num(T1( 1), T2(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, hamon::fmaximum_num(T1(-2), T2(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::fmaximum_num(T1(-4), T2(-3)));
}

template <typename T1, typename T2>
void FMaximumNumTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmaximum_num(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::fmaximum_num(T1( 1), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::fmaximum_num(T1(11), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::fmaximum_num(T1(20), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::fmaximum_num(T1(11), T2(21)));
}

GTEST_TEST(CMathTest, FMaximumNumTest)
{
	FMaximumNumTestFloat<float,       float>();
	FMaximumNumTestFloat<float,       double>();
//	FMaximumNumTestFloat<float,       long double>();
	FMaximumNumTestFloat<double,      float>();
	FMaximumNumTestFloat<double,      double>();
	FMaximumNumTestFloat<double,      long double>();
//	FMaximumNumTestFloat<long double, float>();
	FMaximumNumTestFloat<long double, double>();
	FMaximumNumTestFloat<long double, long double>();

	FMaximumNumTestSignedInt<int,         int>();
//	FMaximumNumTestSignedInt<int,         float>();
	FMaximumNumTestSignedInt<int,         double>();
//	FMaximumNumTestSignedInt<int,         long double>();
	FMaximumNumTestSignedInt<float,       int>();
//	FMaximumNumTestSignedInt<double,      int>();
	FMaximumNumTestSignedInt<long double, int>();

	FMaximumNumTestUnsignedInt<unsigned int, unsigned int>();
//	FMaximumNumTestUnsignedInt<unsigned int, float>();
	FMaximumNumTestUnsignedInt<unsigned int, double>();
	FMaximumNumTestUnsignedInt<unsigned int, long double>();
	FMaximumNumTestUnsignedInt<float,        unsigned int>();
//	FMaximumNumTestUnsignedInt<double,       unsigned int>();
	FMaximumNumTestUnsignedInt<long double,  unsigned int>();
}

}	// namespace fmaximum_num_test

}	// namespace hamon_cmath_test
