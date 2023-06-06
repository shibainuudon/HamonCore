/**
 *	@file	unit_test_cmath_fmin.cpp
 *
 *	@brief	fmin のテスト
 */

#include <hamon/cmath/fmin.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fmin_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fmin(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::fminf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmin(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmin(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmin(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmin(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmin(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmin(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmin(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmin(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmin(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmin(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fminl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmin(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmin(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmin(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmin(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmin(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FMinTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR auto nan1    = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2    = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1    = std::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2    = std::numeric_limits<T2>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf3    = std::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmin(T1( 0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmin(T1( 0.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmin(T1( 1.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fmin(T1( 2.5), T2( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, hamon::fmin(T1( 1.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fmin(T1(-0.5), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::fmin(T1( 0.5), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::fmin(T1(-0.5), T2(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, hamon::fmin(T1(-1.5), T2(-0.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5,  hamon::fmin( inf1,     T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.5,  hamon::fmin( T1(3.5),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fmin(-inf1,     T2( 4.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fmin( T1(5.5), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::fmin( inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fmin(-inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fmin( inf1,    -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::fmin(-inf1,    -inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmin(nan1,    T2(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::fmin(T1(0.5), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmin(nan1, nan2)));
}

template <typename T1, typename T2>
void FMinTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmin(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmin(T1( 0), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmin(T1( 1), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmin(T1( 2), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmin(T1( 1), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::fmin(T1(-1), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::fmin(T1( 1), T2(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::fmin(T1(-2), T2(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, hamon::fmin(T1(-4), T2(-3)));
}

template <typename T1, typename T2>
void FMinTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::fmin(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::fmin(T1( 1), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::fmin(T1(10), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::fmin(T1(20), T2(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, hamon::fmin(T1(11), T2(20)));
}

GTEST_TEST(CMathTest, FMinTest)
{
	FMinTestFloat<float,       float>();
//	FMinTestFloat<float,       double>();
	FMinTestFloat<float,       long double>();
//	FMinTestFloat<double,      float>();
	FMinTestFloat<double,      double>();
//	FMinTestFloat<double,      long double>();
	FMinTestFloat<long double, float>();
//	FMinTestFloat<long double, double>();
	FMinTestFloat<long double, long double>();

//	FMinTestSignedInt<int,         int>();
	FMinTestSignedInt<int,         float>();
//	FMinTestSignedInt<int,         double>();
	FMinTestSignedInt<int,         long double>();
//	FMinTestSignedInt<float,       int>();
	FMinTestSignedInt<double,      int>();
//	FMinTestSignedInt<long double, int>();

	FMinTestUnsignedInt<unsigned int, unsigned int>();
//	FMinTestUnsignedInt<unsigned int, float>();
	FMinTestUnsignedInt<unsigned int, double>();
//	FMinTestUnsignedInt<unsigned int, long double>();
	FMinTestUnsignedInt<float,        unsigned int>();
//	FMinTestUnsignedInt<double,       unsigned int>();
	FMinTestUnsignedInt<long double,  unsigned int>();
}

}	// namespace fmin_test

}	// namespace hamon_cmath_test
