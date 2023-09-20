/**
 *	@file	unit_test_cmath_fmax.cpp
 *
 *	@brief	fmax のテスト
 */

#include <hamon/cmath/fmax.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fmax_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fmax(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::fmaxf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmax(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmax(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmax(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmax(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmax(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmax(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmax(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmax(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmax(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmax(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmaxl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmax(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmax(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmax(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmax(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmax(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FMaxTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR auto nan1    = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2    = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1    = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2    = hamon::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf3    = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmax(T1( 0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fmax(T1( 0.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fmax(T1( 1.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::fmax(T1( 2.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, hamon::fmax(T1( 1.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmax(T1(-0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmax(T1( 0.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fmax(T1(-0.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fmax(T1(-1.5), T2(-0.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmax( inf1,     T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmax( T1(3.5),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.5,  hamon::fmax(-inf1,     T2( 4.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5.5,  hamon::fmax( T1(5.5), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmax( inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmax(-inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmax( inf1,    -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fmax(-inf1,    -inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmax(nan1,    T2(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmax(T1(0.5), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmax(nan1, nan2)));
}

template <typename T1, typename T2>
void FMaxTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmax(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmax(T1( 0), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmax(T1( 1), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fmax(T1( 2), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fmax(T1( 1), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmax(T1(-1), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmax(T1( 1), T2(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, hamon::fmax(T1(-2), T2(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::fmax(T1(-4), T2(-3)));
}

template <typename T1, typename T2>
void FMaxTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmax(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::fmax(T1( 1), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::fmax(T1(11), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::fmax(T1(20), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(21, hamon::fmax(T1(11), T2(21)));
}

GTEST_TEST(CMathTest, FMaxTest)
{
//	FMaxTestFloat<float,       float>();
	FMaxTestFloat<float,       double>();
//	FMaxTestFloat<float,       long double>();
	FMaxTestFloat<double,      float>();
//	FMaxTestFloat<double,      double>();
	FMaxTestFloat<double,      long double>();
//	FMaxTestFloat<long double, float>();
	FMaxTestFloat<long double, double>();
//	FMaxTestFloat<long double, long double>();

	FMaxTestSignedInt<int,         int>();
//	FMaxTestSignedInt<int,         float>();
	FMaxTestSignedInt<int,         double>();
//	FMaxTestSignedInt<int,         long double>();
	FMaxTestSignedInt<float,       int>();
//	FMaxTestSignedInt<double,      int>();
	FMaxTestSignedInt<long double, int>();

	FMaxTestUnsignedInt<unsigned int, unsigned int>();
//	FMaxTestUnsignedInt<unsigned int, float>();
	FMaxTestUnsignedInt<unsigned int, double>();
	FMaxTestUnsignedInt<unsigned int, long double>();
	FMaxTestUnsignedInt<float,        unsigned int>();
//	FMaxTestUnsignedInt<double,       unsigned int>();
	FMaxTestUnsignedInt<long double,  unsigned int>();
}

}	// namespace fmax_test

}	// namespace hamon_cmath_test
