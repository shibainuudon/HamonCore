/**
 *	@file	unit_test_cmath_round_up.cpp
 *
 *	@brief	round_up のテスト
 */

#include <hamon/cmath/round_up.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace round_up_test
{

static_assert(hamon::is_same<float,       decltype(hamon::round_up(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::round_up(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::round_up(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::round_up(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::round_up(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::round_up(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::round_up(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::round_up(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::round_up(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::round_up(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::round_up(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::round_up(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<int,         decltype(hamon::round_up(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<int,         decltype(hamon::round_up(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<int,         decltype(hamon::round_up(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<int,         decltype(hamon::round_up(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void RoundUpTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  0), hamon::round_up(T1( 0), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  1), hamon::round_up(T1( 1), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  1), hamon::round_up(T1( 1), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  2), hamon::round_up(T1( 1), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  3), hamon::round_up(T1( 1), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  4), hamon::round_up(T1( 1), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  5), hamon::round_up(T1( 1), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  7), hamon::round_up(T1( 1), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  8), hamon::round_up(T1( 1), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  9), hamon::round_up(T1( 1), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 15), hamon::round_up(T1( 1), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 16), hamon::round_up(T1( 1), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 17), hamon::round_up(T1( 1), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 32), hamon::round_up(T1( 1), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  2), hamon::round_up(T1( 2), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  2), hamon::round_up(T1( 2), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  2), hamon::round_up(T1( 2), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  3), hamon::round_up(T1( 2), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  4), hamon::round_up(T1( 2), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  5), hamon::round_up(T1( 2), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  7), hamon::round_up(T1( 2), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  8), hamon::round_up(T1( 2), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  9), hamon::round_up(T1( 2), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 15), hamon::round_up(T1( 2), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 16), hamon::round_up(T1( 2), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 17), hamon::round_up(T1( 2), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 32), hamon::round_up(T1( 2), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  3), hamon::round_up(T1( 3), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  3), hamon::round_up(T1( 3), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  4), hamon::round_up(T1( 3), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  3), hamon::round_up(T1( 3), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  4), hamon::round_up(T1( 3), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  5), hamon::round_up(T1( 3), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  7), hamon::round_up(T1( 3), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  8), hamon::round_up(T1( 3), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  9), hamon::round_up(T1( 3), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 15), hamon::round_up(T1( 3), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 16), hamon::round_up(T1( 3), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 17), hamon::round_up(T1( 3), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 32), hamon::round_up(T1( 3), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  9), hamon::round_up(T1( 9), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  9), hamon::round_up(T1( 9), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 10), hamon::round_up(T1( 9), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  9), hamon::round_up(T1( 9), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 12), hamon::round_up(T1( 9), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 10), hamon::round_up(T1( 9), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 14), hamon::round_up(T1( 9), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 16), hamon::round_up(T1( 9), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1(  9), hamon::round_up(T1( 9), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 15), hamon::round_up(T1( 9), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 16), hamon::round_up(T1( 9), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 17), hamon::round_up(T1( 9), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 32), hamon::round_up(T1( 9), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 17), hamon::round_up(T1(17), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 17), hamon::round_up(T1(17), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 18), hamon::round_up(T1(17), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 18), hamon::round_up(T1(17), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 20), hamon::round_up(T1(17), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 20), hamon::round_up(T1(17), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 21), hamon::round_up(T1(17), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 24), hamon::round_up(T1(17), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 18), hamon::round_up(T1(17), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 30), hamon::round_up(T1(17), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 32), hamon::round_up(T1(17), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 17), hamon::round_up(T1(17), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T1( 32), hamon::round_up(T1(17), T2(32)));
}

template <typename T1, typename T2>
void RoundUpTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1, hamon::round_up(T1(-1), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -1, hamon::round_up(T1(-1), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-1), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2, hamon::round_up(T1(-2), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2, hamon::round_up(T1(-2), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2, hamon::round_up(T1(-2), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-2), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -3, hamon::round_up(T1(-3), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -3, hamon::round_up(T1(-3), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -2, hamon::round_up(T1(-3), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -3, hamon::round_up(T1(-3), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-3), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, hamon::round_up(T1(-9), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, hamon::round_up(T1(-9), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8, hamon::round_up(T1(-9), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, hamon::round_up(T1(-9), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8, hamon::round_up(T1(-9), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -5, hamon::round_up(T1(-9), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -7, hamon::round_up(T1(-9), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -8, hamon::round_up(T1(-9), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, hamon::round_up(T1(-9), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-9), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-9), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-9), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-9), T2(32)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-17, hamon::round_up(T1(-17), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-17, hamon::round_up(T1(-17), T2( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16, hamon::round_up(T1(-17), T2( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-15, hamon::round_up(T1(-17), T2( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16, hamon::round_up(T1(-17), T2( 4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-15, hamon::round_up(T1(-17), T2( 5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-14, hamon::round_up(T1(-17), T2( 7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16, hamon::round_up(T1(-17), T2( 8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( -9, hamon::round_up(T1(-17), T2( 9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-15, hamon::round_up(T1(-17), T2(15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-16, hamon::round_up(T1(-17), T2(16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-17, hamon::round_up(T1(-17), T2(17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0, hamon::round_up(T1(-17), T2(32)));

	RoundUpTestUnsignedInt<T1, T2>();
}

template <typename T1, typename T2>
void RoundUpTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.5), hamon::round_up(T1(-2.6), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.5), hamon::round_up(T1(-2.5), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1(-2.4), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1(-0.1), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1( 0.0), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.5), hamon::round_up(T1( 0.1), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.5), hamon::round_up(T1( 2.4), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.5), hamon::round_up(T1( 2.5), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 5.0), hamon::round_up(T1( 2.6), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 5.0), hamon::round_up(T1( 4.9), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 5.0), hamon::round_up(T1( 5.0), T2(2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 7.5), hamon::round_up(T1( 5.1), T2(2.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-3.5), hamon::round_up(T1(-3.6), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-3.5), hamon::round_up(T1(-3.5), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1(-3.4), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1(-0.1), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1( 0.0), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 3.5), hamon::round_up(T1( 0.1), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 3.5), hamon::round_up(T1( 3.4), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 3.5), hamon::round_up(T1( 3.5), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 7.0), hamon::round_up(T1( 3.6), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 7.0), hamon::round_up(T1( 6.9), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 7.0), hamon::round_up(T1( 7.0), T2(3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(10.5), hamon::round_up(T1( 7.1), T2(3.5)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-5.0), hamon::round_up(T1(-2.6), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.5), hamon::round_up(T1(-2.5), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.5), hamon::round_up(T1(-2.4), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-2.5), hamon::round_up(T1(-0.1), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1( 0.0), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1( 0.1), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1( 2.4), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.5), hamon::round_up(T1( 2.5), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.5), hamon::round_up(T1( 2.6), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.5), hamon::round_up(T1( 4.9), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 5.0), hamon::round_up(T1( 5.0), T2(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 5.0), hamon::round_up(T1( 5.1), T2(-2.5)));

	HAMON_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CONSTEXPR auto inf3 = std::numeric_limits<R>::infinity();

	// base が NaN  の場合、NaN  を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(T1( 1.0), nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(T1( 0.0), nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(T1(-1.0), nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up( inf1, nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(-inf1, nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up( nan1, nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(-nan1, nan2)));

	// x が NaN     の場合、NaN  を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up( nan1, T2(2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(-nan1, T2(3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up( nan1, T2(0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(-nan1, T2(0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up( nan1, inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(-nan1, inf2)));

	// base が ±∞ の場合、±∞ を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::round_up(T1( 1.0),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::round_up(T1( 0.0),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::round_up(T1(-1.0),  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::round_up( inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::round_up(-inf1,     inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::round_up(T1( 1.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::round_up(T1( 0.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::round_up(T1(-1.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::round_up( inf1,    -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::round_up(-inf1,    -inf2));

	// x が ±∞    の場合、±∞ を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::round_up( inf1, T2(2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::round_up(-inf1, T2(3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::round_up( inf1, T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::round_up(-inf1, T2(0.0)));

	// base == 0　  の場合、x    を返す。
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1.0), hamon::round_up(T1( 1.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0.0), hamon::round_up(T1( 0.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1.0), hamon::round_up(T1(-1.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 2.0), hamon::round_up(T1( 2.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-3.0), hamon::round_up(T1(-3.0), T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf3, hamon::round_up( inf1, T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf3, hamon::round_up(-inf1, T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up( nan1, T2(0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round_up(-nan1, T2(0.0))));

	RoundUpTestSignedInt<T1, T2>();
}

GTEST_TEST(CMathTest, RoundUpTest)
{
	RoundUpTestSignedInt<int, signed char>();
//	RoundUpTestSignedInt<int, short>();
	RoundUpTestSignedInt<int, int>();
//	RoundUpTestSignedInt<int, long>();
	RoundUpTestSignedInt<int, long long>();
//	RoundUpTestSignedInt<signed char, signed char>();
	RoundUpTestSignedInt<signed char, short>();
//	RoundUpTestSignedInt<signed char, int>();
	RoundUpTestSignedInt<signed char, long>();
//	RoundUpTestSignedInt<signed char, long long>();
	RoundUpTestSignedInt<long long, signed char>();
//	RoundUpTestSignedInt<long long, short>();
	RoundUpTestSignedInt<long long, int>();
//	RoundUpTestSignedInt<long long, long>();
	RoundUpTestSignedInt<long long, long long>();

//	RoundUpTestUnsignedInt<unsigned int, unsigned char>();
	RoundUpTestUnsignedInt<unsigned int, unsigned short>();
//	RoundUpTestUnsignedInt<unsigned int, unsigned int>();
	RoundUpTestUnsignedInt<unsigned int, unsigned long>();
//	RoundUpTestUnsignedInt<unsigned int, unsigned long long>();
	RoundUpTestUnsignedInt<unsigned char, unsigned char>();
//	RoundUpTestUnsignedInt<unsigned char, unsigned short>();
	RoundUpTestUnsignedInt<unsigned char, unsigned int>();
//	RoundUpTestUnsignedInt<unsigned char, unsigned long>();
	RoundUpTestUnsignedInt<unsigned char, unsigned long long>();
//	RoundUpTestUnsignedInt<unsigned long long, unsigned char>();
	RoundUpTestUnsignedInt<unsigned long long, unsigned short>();
//	RoundUpTestUnsignedInt<unsigned long long, unsigned int>();
	RoundUpTestUnsignedInt<unsigned long long, unsigned long>();
//	RoundUpTestUnsignedInt<unsigned long long, unsigned long long>();

	RoundUpTestFloat<float, float>();
//	RoundUpTestFloat<float, double>();
	RoundUpTestFloat<float, long double>();
//	RoundUpTestFloat<double, float>();
	RoundUpTestFloat<double, double>();
//	RoundUpTestFloat<double, long double>();
	RoundUpTestFloat<long double, float>();
//	RoundUpTestFloat<long double, double>();
	RoundUpTestFloat<long double, long double>();
}

}	// namespace round_up_test

}	// namespace hamon_cmath_test
