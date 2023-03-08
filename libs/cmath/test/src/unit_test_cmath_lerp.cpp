/**
 *	@file	unit_test_cmath_lerp.cpp
 *
 *	@brief	lerp のテスト
 */

#include <hamon/cmath/lerp.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace lerp_test
{

static_assert(hamon::is_same<float,       decltype(hamon::lerp(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0f, 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0f, 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0f, 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0f, 0.0,  0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0f, 0.0,  0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0f, 0.0,  0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0f, 0.0,  0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0f, 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0f, 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0f, 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0f, 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0f, 0,    0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0f, 0,    0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0f, 0,    0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0f, 0,    0   ))>::value, "");

static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0,  0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0.0,  0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0.0,  0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0,  0.0,  0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0.0,  0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0,  0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0,  0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0,  0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0,  0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0,    0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0,    0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0,  0,    0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0.0,  0,    0   ))>::value, "");

static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0,  0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0,  0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0,  0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0,  0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0,    0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0,    0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0,    0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0.0l, 0,    0   ))>::value, "");

static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0,    0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0.0,  0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0.0,  0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0,    0.0,  0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0.0,  0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0,    0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0,    0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0,    0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0,    0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0,    0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0,    0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::lerp(0,    0,    0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::lerp(0,    0,    0   ))>::value, "");

template <typename T>
void LerpTest(void)
{
	//HAMON_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	//HAMON_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	// When isfinite(a) && isfinite(b):
	// ・If t == 0, the result is equal to a.
	// ・If t == 1, the result is equal to b.
	// ・If t >= 0 && t <= 1, the result is finite.
	// ・If isfinite(t) && a == b, the result is equal to a.
	// ・If isfinite(t) || (!isnan(t) && b-a != 0), the result is not NaN.

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-20.0), hamon::lerp(T( 0.0), T(10.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-10.0), hamon::lerp(T( 0.0), T(10.0), T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  0.0), hamon::lerp(T( 0.0), T(10.0), T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  2.5), hamon::lerp(T( 0.0), T(10.0), T( 0.25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  5.0), hamon::lerp(T( 0.0), T(10.0), T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  7.5), hamon::lerp(T( 0.0), T(10.0), T( 0.75)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 10.0), hamon::lerp(T( 0.0), T(10.0), T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 20.0), hamon::lerp(T( 0.0), T(10.0), T( 2.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-20.0), hamon::lerp(T( 0.0), 10.0f, T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-10.0), hamon::lerp(T( 0.0), 10.0f, T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  0.0), hamon::lerp(T( 0.0), 10.0f, T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  2.5), hamon::lerp(T( 0.0), 10.0f, T( 0.25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  5.0), hamon::lerp(T( 0.0), 10.0f, T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  7.5), hamon::lerp(T( 0.0), 10.0f, T( 0.75)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 10.0), hamon::lerp(T( 0.0), 10.0f, T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 20.0), hamon::lerp(T( 0.0), 10.0f, T( 2.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-10.0), hamon::lerp(10, 20, T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  0.0), hamon::lerp(10, 20, T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 10.0), hamon::lerp(10, 20, T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 12.5), hamon::lerp(10, 20, T( 0.25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 15.0), hamon::lerp(10, 20, T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 17.5), hamon::lerp(10, 20, T( 0.75)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 20.0), hamon::lerp(10, 20, T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 30.0), hamon::lerp(10, 20, T( 2.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(min, hamon::lerp(min, max, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::lerp(min, max, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::lerp(max, min, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(min, hamon::lerp(max, min, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(hamon::lerp(min, max, T(0.1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(hamon::lerp(min, max, T(0.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(hamon::lerp(min, max, T(0.9))));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::lerp(T( 0.0), T( 0.0), min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::lerp(T( 0.0), T( 0.0), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(10.0), hamon::lerp(T(10.0), T(10.0), min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(10.0), hamon::lerp(T(10.0), T(10.0), max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(min, hamon::lerp(min, min, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(min, hamon::lerp(min, min, T(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(min, hamon::lerp(min, min, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(min, hamon::lerp(min, min, min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(min, hamon::lerp(min, min, max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::lerp(max, max, T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::lerp(max, max, T(0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::lerp(max, max, T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::lerp(max, max, min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max, hamon::lerp(max, max, max));

	// TODO
	//HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::lerp(T(0.0), T(1.0), inf)));
	//HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::lerp(min,    max,    inf)));
	//HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::lerp(max,    min,    inf)));
}

GTEST_TEST(CMathTest, LerpTest)
{
	LerpTest<float>();
	LerpTest<double>();
	LerpTest<long double>();
}

}	// namespace lerp_test

}	// namespace hamon_cmath_test
