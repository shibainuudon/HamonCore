/**
 *	@file	unit_test_cmath_repeat.cpp
 *
 *	@brief	repeat のテスト
 */

#include <hamon/cmath/repeat.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace repeat_test
{

static_assert(hamon::is_same<float,       decltype(hamon::repeat(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0f, 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0f, 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0f, 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0f, 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0f, 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0f, 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0f, 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0f, 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0f, 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0f, 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0f, 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0f, 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0f, 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0f, 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0f, 0   , 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0 , 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0 , 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0 , 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0 , 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0 , 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0 , 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0 , 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0.0 , 0   , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0.0l, 0   , 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0   , 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0   , 0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0   , 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0   , 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0   , 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0   , 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::repeat(0   , 0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::repeat(0   , 0   , 0   ))>::value, "");

template <typename T>
void RepeatTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::repeat(T( 0), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::repeat(T( 1), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), hamon::repeat(T( 2), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::repeat(T( 3), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::repeat(T( 4), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), hamon::repeat(T( 5), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::repeat(T( 6), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::repeat(T( 7), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), hamon::repeat(T( 8), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::repeat(T( 9), T(0), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::repeat(T(10), T(0), T(3)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(10), hamon::repeat(T( 0), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(11), hamon::repeat(T( 1), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(12), hamon::repeat(T( 2), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(13), hamon::repeat(T( 3), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(14), hamon::repeat(T( 4), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(15), hamon::repeat(T( 5), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(16), hamon::repeat(T( 6), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(17), hamon::repeat(T( 7), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(18), hamon::repeat(T( 8), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(19), hamon::repeat(T( 9), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(10), hamon::repeat(T(10), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(11), hamon::repeat(T(11), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(12), hamon::repeat(T(12), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(13), hamon::repeat(T(13), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(14), hamon::repeat(T(14), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(15), hamon::repeat(T(15), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(16), hamon::repeat(T(16), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(17), hamon::repeat(T(17), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(18), hamon::repeat(T(18), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(19), hamon::repeat(T(19), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(10), hamon::repeat(T(20), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(11), hamon::repeat(T(21), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(12), hamon::repeat(T(22), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(13), hamon::repeat(T(23), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(14), hamon::repeat(T(24), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(15), hamon::repeat(T(25), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(16), hamon::repeat(T(26), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(17), hamon::repeat(T(27), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(18), hamon::repeat(T(28), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(19), hamon::repeat(T(29), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(10), hamon::repeat(T(30), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(11), hamon::repeat(T(31), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(12), hamon::repeat(T(32), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(13), hamon::repeat(T(33), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(14), hamon::repeat(T(34), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(15), hamon::repeat(T(35), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(16), hamon::repeat(T(36), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(17), hamon::repeat(T(37), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(18), hamon::repeat(T(38), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(19), hamon::repeat(T(39), T(10), T(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(10), hamon::repeat(T(40), T(10), T(20)));
}

template <typename T>
void RepeatTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T(-15), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T(-14), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T(-13), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 3), hamon::repeat(T(-12), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 4), hamon::repeat(T(-11), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T(-10), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T( -9), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T( -8), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 3), hamon::repeat(T( -7), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 4), hamon::repeat(T( -6), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T( -5), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T( -4), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T( -3), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 3), hamon::repeat(T( -2), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 4), hamon::repeat(T( -1), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T(  0), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T(  1), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T(  2), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 3), hamon::repeat(T(  3), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 4), hamon::repeat(T(  4), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T(  5), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T(  6), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T(  7), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 3), hamon::repeat(T(  8), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 4), hamon::repeat(T(  9), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T( 10), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T( 11), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T( 12), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 3), hamon::repeat(T( 13), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 4), hamon::repeat(T( 14), T(0), T(5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T( 15), T(0), T(5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::repeat(T(-15), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T(-14), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T(-13), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T(-12), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-4), hamon::repeat(T(-11), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-3), hamon::repeat(T(-10), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2), hamon::repeat(T( -9), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::repeat(T( -8), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T( -7), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T( -6), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T( -5), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-4), hamon::repeat(T( -4), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-3), hamon::repeat(T( -3), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2), hamon::repeat(T( -2), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::repeat(T( -1), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T(  0), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T(  1), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T(  2), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-4), hamon::repeat(T(  3), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-3), hamon::repeat(T(  4), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2), hamon::repeat(T(  5), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::repeat(T(  6), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T(  7), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T(  8), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2), hamon::repeat(T(  9), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-4), hamon::repeat(T( 10), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-3), hamon::repeat(T( 11), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2), hamon::repeat(T( 12), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::repeat(T( 13), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::repeat(T( 14), T(-4), T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::repeat(T( 15), T(-4), T(3)));

	RepeatTestUnsignedInt<T>();
}

template <typename T>
void RepeatTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR double error = 0.0001;

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(nan,  T(0), T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(T(0), nan,  T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(T(0), T(0), nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(nan,  nan,  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(inf,  T(0), T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(T(0), -inf, T(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(T(0), T(0), inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(inf,  -inf, inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(T(0.0), T(0.0), T(-0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::repeat(T(0.0), T(1.0), T( 0.5))));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::repeat(T(-1.0), T(0.0), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::repeat(T(-0.5), T(0.0), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::repeat(T( 0.0), T(0.0), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::repeat(T( 0.5), T(0.0), T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::repeat(T( 1.0), T(0.0), T(0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.5), hamon::repeat(T(-2.0), T(1.5), T(1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.5), hamon::repeat(T(-1.0), T(1.5), T(1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.5), hamon::repeat(T( 0.0), T(1.5), T(1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.5), hamon::repeat(T( 1.0), T(1.5), T(1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.5), hamon::repeat(T( 2.0), T(1.5), T(1.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::repeat(T(-2.0), T(-2.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::repeat(T(-1.0), T(-2.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::repeat(T( 0.0), T(-2.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::repeat(T( 1.0), T(-2.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::repeat(T( 2.0), T(-2.0), T(-2.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.4, (double)hamon::repeat(T(-2.6), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.5, (double)hamon::repeat(T(-2.5), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.4, (double)hamon::repeat(T(-2.4), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.3, (double)hamon::repeat(T(-2.3), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.2, (double)hamon::repeat(T(-2.2), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.1, (double)hamon::repeat(T(-2.1), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T(-2.0), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T(-1.9), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T(-1.8), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.3, (double)hamon::repeat(T(-1.7), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.4, (double)hamon::repeat(T(-1.6), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.5, (double)hamon::repeat(T(-1.5), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.4, (double)hamon::repeat(T(-1.4), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.3, (double)hamon::repeat(T(-1.3), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.2, (double)hamon::repeat(T(-1.2), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.1, (double)hamon::repeat(T(-1.1), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T(-1.0), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T(-0.9), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T(-0.8), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.3, (double)hamon::repeat(T(-0.7), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.4, (double)hamon::repeat(T(-0.6), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.5, (double)hamon::repeat(T(-0.5), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.4, (double)hamon::repeat(T(-0.4), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.3, (double)hamon::repeat(T(-0.3), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.2, (double)hamon::repeat(T(-0.2), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.1, (double)hamon::repeat(T(-0.1), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T( 0.0), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T( 0.1), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T( 0.2), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.3, (double)hamon::repeat(T( 0.3), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.4, (double)hamon::repeat(T( 0.4), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.5, (double)hamon::repeat(T( 0.5), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.4, (double)hamon::repeat(T( 0.6), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.3, (double)hamon::repeat(T( 0.7), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.2, (double)hamon::repeat(T( 0.8), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.1, (double)hamon::repeat(T( 0.9), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T( 1.0), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T( 1.1), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T( 1.2), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.3, (double)hamon::repeat(T( 1.3), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.4, (double)hamon::repeat(T( 1.4), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.5, (double)hamon::repeat(T( 1.5), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.4, (double)hamon::repeat(T( 1.6), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.3, (double)hamon::repeat(T( 1.7), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.2, (double)hamon::repeat(T( 1.8), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.1, (double)hamon::repeat(T( 1.9), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T( 2.0), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T( 2.1), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T( 2.2), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.3, (double)hamon::repeat(T( 2.3), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.4, (double)hamon::repeat(T( 2.4), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.5, (double)hamon::repeat(T( 2.5), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.4, (double)hamon::repeat(T( 2.6), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.3, (double)hamon::repeat(T( 2.7), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.2, (double)hamon::repeat(T( 2.8), T(-0.5), T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.1, (double)hamon::repeat(T( 2.9), T(-0.5), T(0.5)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.8, (double)hamon::repeat(T(-300.2), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.9, (double)hamon::repeat(T(-300.1), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T(-300.0), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T(-299.9), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T(-299.8), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.8, (double)hamon::repeat(T(-200.2), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.9, (double)hamon::repeat(T(-200.1), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T(-200.0), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T(-199.9), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T(-199.8), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.8, (double)hamon::repeat(T(-100.2), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.9, (double)hamon::repeat(T(-100.1), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T(-100.0), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T( -99.9), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T( -99.8), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.8, (double)hamon::repeat(T(  -0.2), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.9, (double)hamon::repeat(T(  -0.1), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T(   0.0), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T(   0.1), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T(   0.2), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.8, (double)hamon::repeat(T(  99.8), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.9, (double)hamon::repeat(T(  99.9), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T( 100.0), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T( 100.1), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T( 100.2), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.8, (double)hamon::repeat(T( 199.8), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.9, (double)hamon::repeat(T( 199.9), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T( 200.0), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T( 200.1), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T( 200.2), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.8, (double)hamon::repeat(T( 299.8), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 99.9, (double)hamon::repeat(T( 299.9), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)hamon::repeat(T( 300.0), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.1, (double)hamon::repeat(T( 300.1), T(0), T(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.2, (double)hamon::repeat(T( 300.2), T(0), T(100)), error);

	RepeatTestSignedInt<T>();
}

template <typename T1, typename T2, typename T3>
void RepeatTest(void)
{
	using ResultType = hamon::float_promote_t<T1, T2, T3>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(20), hamon::repeat(T1( 0), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(21), hamon::repeat(T1( 1), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(38), hamon::repeat(T1(18), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(39), hamon::repeat(T1(19), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(20), hamon::repeat(T1(20), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(21), hamon::repeat(T1(21), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(39), hamon::repeat(T1(39), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(20), hamon::repeat(T1(40), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(21), hamon::repeat(T1(41), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(22), hamon::repeat(T1(42), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(39), hamon::repeat(T1(59), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(20), hamon::repeat(T1(60), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(21), hamon::repeat(T1(61), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(39), hamon::repeat(T1(79), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(20), hamon::repeat(T1(80), T2(20), T3(40)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(ResultType(21), hamon::repeat(T1(81), T2(20), T3(40)));
}

GTEST_TEST(CMathTest, RepeatTest)
{
	RepeatTestFloat<float>();
//	RepeatTestFloat<double>();
	RepeatTestFloat<long double>();

//	RepeatTestSignedInt<signed int>();
	RepeatTestSignedInt<signed char>();
//	RepeatTestSignedInt<signed short>();
	RepeatTestSignedInt<signed long>();
//	RepeatTestSignedInt<signed long long>();

	RepeatTestUnsignedInt<unsigned int>();
//	RepeatTestUnsignedInt<unsigned char>();
	RepeatTestUnsignedInt<unsigned short>();
//	RepeatTestUnsignedInt<unsigned long>();
	RepeatTestUnsignedInt<unsigned long long>();

//	RepeatTest<int, int, int>();
	RepeatTest<int, int, unsigned char>();
//	RepeatTest<int, int, float>();
	RepeatTest<int, int, long double>();
//	RepeatTest<int, unsigned char, int>();
	RepeatTest<int, unsigned char, unsigned char>();
//	RepeatTest<int, unsigned char, float>();
	RepeatTest<int, unsigned char, long double>();
//	RepeatTest<int, float, int>();
	RepeatTest<int, float, unsigned char>();
//	RepeatTest<int, float, float>();
	RepeatTest<int, float, long double>();
//	RepeatTest<int, long double, int>();
	RepeatTest<int, long double, unsigned char>();
//	RepeatTest<int, long double, float>();
	RepeatTest<int, long double, long double>();

//	RepeatTest<unsigned char, int, int>();
	RepeatTest<unsigned char, int, unsigned char>();
//	RepeatTest<unsigned char, int, float>();
	RepeatTest<unsigned char, int, long double>();
//	RepeatTest<unsigned char, unsigned char, int>();
	RepeatTest<unsigned char, unsigned char, unsigned char>();
//	RepeatTest<unsigned char, unsigned char, float>();
	RepeatTest<unsigned char, unsigned char, long double>();
//	RepeatTest<unsigned char, float, int>();
	RepeatTest<unsigned char, float, unsigned char>();
//	RepeatTest<unsigned char, float, float>();
	RepeatTest<unsigned char, float, long double>();
//	RepeatTest<unsigned char, long double, int>();
	RepeatTest<unsigned char, long double, unsigned char>();
//	RepeatTest<unsigned char, long double, float>();
	RepeatTest<unsigned char, long double, long double>();

//	RepeatTest<float, int, int>();
	RepeatTest<float, int, unsigned char>();
//	RepeatTest<float, int, float>();
	RepeatTest<float, int, long double>();
//	RepeatTest<float, unsigned char, int>();
	RepeatTest<float, unsigned char, unsigned char>();
//	RepeatTest<float, unsigned char, float>();
	RepeatTest<float, unsigned char, long double>();
//	RepeatTest<float, float, int>();
	RepeatTest<float, float, unsigned char>();
//	RepeatTest<float, float, float>();
	RepeatTest<float, float, long double>();
//	RepeatTest<float, long double, int>();
	RepeatTest<float, long double, unsigned char>();
//	RepeatTest<float, long double, float>();
	RepeatTest<float, long double, long double>();

	RepeatTest<long double, int, int>();
//	RepeatTest<long double, int, unsigned char>();
	RepeatTest<long double, int, float>();
//	RepeatTest<long double, int, long double>();
	RepeatTest<long double, unsigned char, int>();
//	RepeatTest<long double, unsigned char, unsigned char>();
	RepeatTest<long double, unsigned char, float>();
//	RepeatTest<long double, unsigned char, long double>();
	RepeatTest<long double, float, int>();
//	RepeatTest<long double, float, unsigned char>();
	RepeatTest<long double, float, float>();
//	RepeatTest<long double, float, long double>();
	RepeatTest<long double, long double, int>();
//	RepeatTest<long double, long double, unsigned char>();
	RepeatTest<long double, long double, float>();
//	RepeatTest<long double, long double, long double>();
}

}	// namespace repeat_test

}	// namespace hamon_cmath_test
