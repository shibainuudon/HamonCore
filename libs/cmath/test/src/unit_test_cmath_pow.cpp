/**
 *	@file	unit_test_cmath_pow.cpp
 *
 *	@brief	pow のテスト
 */

#include <hamon/cmath/pow.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace pow_test
{

static_assert(hamon::is_same<float,       decltype(hamon::pow(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::powf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::pow(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::pow(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::pow(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::pow(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::pow(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::pow(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::pow(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::pow(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::pow(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::pow(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::powl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::pow(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::pow(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::pow(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::pow(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::pow(0   , 0   ))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 0.0001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 0.00000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 0.00000000001;
}

template <typename T1, typename T2>
void PowTestFloat()
{
	using Promoted = hamon::float_promote_t<T1, T2>;
	HAMON_CXX11_CONSTEXPR double error = get_error<Promoted>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(8.0,               (double)hamon::pow(T1(2.0), T2( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.0,               (double)hamon::pow(T1(2.0), T2( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0,               (double)hamon::pow(T1(2.0), T2( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.414213562373095, (double)hamon::pow(T1(2.0), T2( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,               (double)hamon::pow(T1(2.0), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.707106781186547, (double)hamon::pow(T1(2.0), T2(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5,               (double)hamon::pow(T1(2.0), T2(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.25,              (double)hamon::pow(T1(2.0), T2(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.125,             (double)hamon::pow(T1(2.0), T2(-3.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(15.625,            (double)hamon::pow(T1(2.5), T2( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(6.25,              (double)hamon::pow(T1(2.5), T2( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.5,               (double)hamon::pow(T1(2.5), T2( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.58113883008419,  (double)hamon::pow(T1(2.5), T2( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,               (double)hamon::pow(T1(2.5), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.6324555320336757,(double)hamon::pow(T1(2.5), T2(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.4,               (double)hamon::pow(T1(2.5), T2(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.16,              (double)hamon::pow(T1(2.5), T2(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.064,             (double)hamon::pow(T1(2.5), T2(-3.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(27.0,              (double)hamon::pow(T1(3.0), T2( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(9.0,               (double)hamon::pow(T1(3.0), T2( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.0,               (double)hamon::pow(T1(3.0), T2( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.732050807568877, (double)hamon::pow(T1(3.0), T2( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,               (double)hamon::pow(T1(3.0), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5773502691896259,(double)hamon::pow(T1(3.0), T2(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.3333333333333333,(double)hamon::pow(T1(3.0), T2(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1111111111111111,(double)hamon::pow(T1(3.0), T2(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.037037037037037, (double)hamon::pow(T1(3.0), T2(-3.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0,              (double)hamon::pow(T1(-2.0), T2( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4.0,              (double)hamon::pow(T1(-2.0), T2( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-8.0,              (double)hamon::pow(T1(-2.0), T2( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.5,              (double)hamon::pow(T1(-2.5), T2( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.25,             (double)hamon::pow(T1(-2.5), T2( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-15.625,           (double)hamon::pow(T1(-2.5), T2( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.5,              (double)hamon::pow(T1(-2.0), T2(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.25,             (double)hamon::pow(T1(-2.0), T2(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.125,            (double)hamon::pow(T1(-2.0), T2(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.4,              (double)hamon::pow(T1(-2.5), T2(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.16,             (double)hamon::pow(T1(-2.5), T2(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.064,            (double)hamon::pow(T1(-2.5), T2(-3.0)), error);
}

template <typename T>
void PowTestErrorHandling(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	// pow(+0, exp), where exp is a negative odd integer, returns +∞ and raises FE_DIVBYZERO
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(+0.0), T(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(+0.0), T(-5.0)));

	// pow(-0, exp), where exp is a negative odd integer, returns -∞ and raises FE_DIVBYZERO
//	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::pow(T(-0.0), T(-3.0)));
//	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::pow(T(-0.0), T(-5.0)));
	// ※HAMONでは-0と+0を区別しない
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(-0.0), T(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(-0.0), T(-5.0)));

	// pow(±0, exp), where exp is negative, finite, and is an even integer or a non-integer, returns +∞ and raises FE_DIVBYZERO
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(+0.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(-0.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(+0.0), T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(-0.0), T(-0.5)));

	// pow(±0, -∞) returns +∞ and may raise FE_DIVBYZERO
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(+0.0), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::pow(T(-0.0), -inf));

	// pow(+0, exp), where exp is a positive odd integer, returns +0
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(T(+0.0), T(3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(T(+0.0), T(5.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(+0.0), T(3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(+0.0), T(5.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(+0.0), T(3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(+0.0), T(5.0))));

	// pow(-0, exp), where exp is a positive odd integer, returns -0
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(-0.0),       hamon::pow(T(-0.0), T(3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(-0.0),       hamon::pow(T(-0.0), T(5.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(-0.0), T(3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(-0.0), T(5.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(-0.0), T(3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(-0.0), T(5.0))));

	// pow(±0, exp), where exp is positive non-integer or a positive even integer, returns +0
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T( 0),         hamon::pow(T(+0.0), T(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T( 0),         hamon::pow(T(-0.0), T(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T( 0),         hamon::pow(T(+0.0), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T( 0),         hamon::pow(T(-0.0), T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(+0.0), T(0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(-0.0), T(0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(+0.0), T(2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(-0.0), T(2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(+0.0), T(0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(-0.0), T(0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(+0.0), T(2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(-0.0), T(2.0))));

	// pow(-1, ±∞) returns 1
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T(-1.0),  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T(-1.0), -inf));

	// pow(+1, exp) returns 1 for any exp, even when exp is NaN
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0), T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0), T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0), T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0), T( 2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0),  inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0),  nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 1.0), -nan));

	// pow(base, ±0) returns 1 for any base, even when base is NaN
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 2.0), T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 2.0), T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 3.0), T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T( 3.0), T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T(-2.0), T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T(-2.0), T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T(-3.0), T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(T(-3.0), T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow( inf, T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow( inf, T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(-inf, T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(-inf, T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow( nan, T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow( nan, T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(-nan, T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::pow(-nan, T(-0.0)));

	// pow(base, exp) returns NaN and raises FE_INVALID if base is finite and negative and exp is finite and non-integer.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::pow(T(-2.0), T( 0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::pow(T(-2.0), T(-0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::pow(T(-2.0), T( 1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::pow(T(-2.0), T(-1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::pow(T(-0.5), T( 2.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::pow(T(-0.5), T(-2.5))));

	// pow(base, -∞) returns +∞ for any |base|<1
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(T( 0.5), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(T(-0.5), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(T( 0.0), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(T(-0.0), -inf));

	// pow(base, -∞) returns +0 for any |base|>1
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T( 1.5), -inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(-1.5), -inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T( 1.5), -inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(-1.5), -inf)));

	// pow(base, +∞) returns +0 for any |base|<1
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T( 0.5), inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(-0.5), inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T( 0.5), inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(-0.5), inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T( 0.0), inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(T(-0.0), inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T( 0.0), inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(T(-0.0), inf)));

	// pow(base, +∞) returns +∞ for any |base|>1
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(T( 1.5), inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(T(-1.5), inf));

	// pow(-∞, exp) returns -0 if exp is a negative odd integer
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(-0.0),       hamon::pow(-inf, T(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(-0.0),       hamon::pow(-inf, T(-5.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(-inf, T(-3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(-inf, T(-5.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(-inf, T(-3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(-inf, T(-5.0))));

	// pow(-∞, exp) returns +0 if exp is a negative non-integer or even integer
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(-inf, T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(-inf, T(-4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(-inf, T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(-inf, T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(-inf, T(-4.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(-inf, T(-0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(-inf, T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(-inf, T(-4.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(-inf, T(-0.5))));

	// pow(-∞, exp) returns -∞ if exp is a positive odd integer
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::pow(-inf, T(3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::pow(-inf, T(5.0)));

	// pow(-∞, exp) returns +∞ if exp is a positive non-integer or even integer
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(-inf, T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(-inf, T(4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(-inf, T(0.5)));

	// pow(+∞, exp) returns +0 for any negative exp
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(inf, T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(inf, T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(inf, T(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (T(+0.0),       hamon::pow(inf, -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(inf, T(-0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(inf, T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(inf, T(-3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::pow(inf, -inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(inf, T(-0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(inf, T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(inf, T(-3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::pow(inf, -inf)));

	// pow(+∞, exp) returns +∞ for any positive exp
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(inf, T(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(inf, T(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(inf, T(3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::pow(inf, inf));
}

template <typename T1, typename T2>
void PowTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(8.0,   (double)hamon::pow(T1(2), T2( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.0,   (double)hamon::pow(T1(2), T2( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0,   (double)hamon::pow(T1(2), T2( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,   (double)hamon::pow(T1(2), T2( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5,   (double)hamon::pow(T1(2), T2(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.25,  (double)hamon::pow(T1(2), T2(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.125, (double)hamon::pow(T1(2), T2(-3)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(27.0,      (double)hamon::pow(T1(3), T2( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 9.0,      (double)hamon::pow(T1(3), T2( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0,      (double)hamon::pow(T1(3), T2( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,      (double)hamon::pow(T1(3), T2( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 3.0, (double)hamon::pow(T1(3), T2(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0 / 9.0, (double)hamon::pow(T1(3), T2(-2)), error);
}

GTEST_TEST(CMathTest, PowTest)
{
	PowTestFloat<float,       float>();
//	PowTestFloat<float,       double>();
	PowTestFloat<float,       long double>();
//	PowTestFloat<double,      float>();
	PowTestFloat<double,      double>();
//	PowTestFloat<double,      long double>();
	PowTestFloat<long double, float>();
//	PowTestFloat<long double, double>();
	PowTestFloat<long double, long double>();

	PowTestErrorHandling<float>();
	PowTestErrorHandling<double>();
	PowTestErrorHandling<long double>();

//	PowTestInteger<int, int>();
	PowTestInteger<int, float>();
//	PowTestInteger<int, double>();
	PowTestInteger<int, long double>();
//	PowTestInteger<float, int>();
	PowTestInteger<double, int>();
//	PowTestInteger<long double, int>();
}

}	// namespace pow_test

}	// namespace hamon_cmath_test
