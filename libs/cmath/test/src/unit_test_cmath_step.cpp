/**
 *	@file	unit_test_cmath_step.cpp
 *
 *	@brief	step のテスト
 */

#include <hamon/cmath/step.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace step_test
{

static_assert(hamon::is_same<float,       decltype(hamon::step(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::step(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::step(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::step(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::step(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::step(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::step(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::step(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::step(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::step(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::step(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::step(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::step(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::step(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::step(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::step(0   , 0   ))>::value, "");

template <typename T1, typename T2>
void StepTestFloat(void)
{
	HAMON_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CONSTEXPR auto eps2 = std::numeric_limits<T2>::epsilon();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(0.0), T2( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(0.0), T2(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(0.0), T2( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(0.0), T2(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(0.0), T2( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(0.0), -eps2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(0.0),  eps2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(0.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(0.0),  inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(10.0), T2( 9.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(10.0), T2(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(10.0), T2(11.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(10.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(10.0),  inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step( inf1,  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step( inf1, -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(-inf1,  inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(-inf1, -inf2));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(nan1,    T2(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(0.0), nan2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(nan1,    nan2));
}

template <typename T1, typename T2>
void StepTestInteger(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(0), T2(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(0), T2( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(0), T2( 1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(20), T2(19)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(20), T2(20)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(20), T2(21)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(-30), T2(-29)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, hamon::step(T1(-30), T2(-30)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::step(T1(-30), T2(-31)));
}

GTEST_TEST(CMathTest, StepTest)
{
	StepTestFloat<float,       float>      ();
//	StepTestFloat<float,       double>     ();
	StepTestFloat<float,       long double>();
//	StepTestFloat<double,      float>      ();
	StepTestFloat<double,      double>     ();
//	StepTestFloat<double,      long double>();
	StepTestFloat<long double, float>      ();
//	StepTestFloat<long double, double>     ();
	StepTestFloat<long double, long double>();

//	StepTestInteger<int,         int>();
	StepTestInteger<int,         float>();
//	StepTestInteger<int,         double>();
	StepTestInteger<int,         long double>();
//	StepTestInteger<float,       int>();
	StepTestInteger<double,      int>();
//	StepTestInteger<long double, int>();
}

}	// namespace step_test

}	// namespace hamon_cmath_test
