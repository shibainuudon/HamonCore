/**
 *	@file	unit_test_cmath_fmod.cpp
 *
 *	@brief	fmod のテスト
 */

#include <hamon/cmath/fmod.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fmod_test
{

static_assert(hamon::is_same<float,       decltype(hamon::fmod(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::fmodf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmod(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmod(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmod(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmod(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmod(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmod(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmod(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmod(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmod(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmod(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmodl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmod(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmod(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmod(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::fmod(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::fmod(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void FmodTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan1 = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = hamon::numeric_limits<T2>::infinity();

	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.5), hamon::fmod(T1( 5.5), T2( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.5), hamon::fmod(T1(-5.5), T2( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.5), hamon::fmod(T1( 5.5), T2(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.5), hamon::fmod(T1(-5.5), T2(-3.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.5), hamon::fmod(T1( 5.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.5), hamon::fmod(T1(-5.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.5), hamon::fmod(T1( 5.5), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.5), hamon::fmod(T1(-5.5), T2(-2.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::fmod(T1( 7.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.0), hamon::fmod(T1(-7.5), T2( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::fmod(T1( 7.5), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-0.0), hamon::fmod(T1(-7.5), T2(-2.5)));

	//If x is ±0 and y is not zero, ±0 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::fmod(T1(+0.0), T2( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::fmod(T1(-0.0), T2( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmod(T1(+0.0), T2( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmod(T1(-0.0), T2( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::fmod(T1(+0.0), T2(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::fmod(T1(-0.0), T2(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmod(T1(+0.0), T2(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmod(T1(-0.0), T2(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::fmod(T1(+0.0), inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::fmod(T1(-0.0), inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmod(T1(+0.0), inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::fmod(T1(-0.0), inf2)));

	//If x is ±∞ and y is not NaN, NaN is returned and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod( inf1, T2( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(-inf1, T2( 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod( inf1, T2(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(-inf1, T2(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod( inf1, T2( 0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(-inf1, T2( 0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod( inf1, inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(-inf1, inf2)));

	//If y is ±0 and x is not NaN, NaN is returned and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(T1( 1.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(T1( 1.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(T1(-2.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(T1(-2.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(T1( 0.0), T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(T1( 0.0), T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(inf1,     T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(inf1,     T2(-0.0))));

	//If y is ±∞ and x is finite, x is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1.0), hamon::fmod(T1( 1.0), +inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1.0), hamon::fmod(T1( 1.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.0), hamon::fmod(T1(-2.0), +inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.0), hamon::fmod(T1(-2.0), -inf2));

	//If either argument is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(nan1, T2(1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(T1(1.0), nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::fmod(nan1, nan2)));
}

template <typename T1, typename T2>
void FmodTestInteger(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2), hamon::fmod(T1( 5), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2), hamon::fmod(T1(-5), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2), hamon::fmod(T1( 5), T2(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2), hamon::fmod(T1(-5), T2(-3)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 3), hamon::fmod(T1( 7), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-3), hamon::fmod(T1(-7), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 3), hamon::fmod(T1( 7), T2(-4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-3), hamon::fmod(T1(-7), T2(-4)));
}

GTEST_TEST(CMathTest, FmodTest)
{
//	FmodTestFloat<float,       float>      ();
	FmodTestFloat<float,       double>     ();
//	FmodTestFloat<float,       long double>();
	FmodTestFloat<double,      float>      ();
//	FmodTestFloat<double,      double>     ();
	FmodTestFloat<double,      long double>();
//	FmodTestFloat<long double, float>      ();
	FmodTestFloat<long double, double>     ();
//	FmodTestFloat<long double, long double>();

	FmodTestInteger<int,         int>();
//	FmodTestInteger<int,         float>();
	FmodTestInteger<int,         double>();
//	FmodTestInteger<int,         long double>();
	FmodTestInteger<float,       int>();
//	FmodTestInteger<double,      int>();
	FmodTestInteger<long double, int>();
}

}	// namespace fmod_test

}	// namespace hamon_cmath_test
