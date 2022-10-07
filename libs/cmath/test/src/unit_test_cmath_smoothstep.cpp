/**
 *	@file	unit_test_cmath_smoothstep.cpp
 *
 *	@brief	smoothstep のテスト
 */

#include <hamon/cmath/smoothstep.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace smoothstep_test
{

static_assert(std::is_same<float,       decltype(hamon::smoothstep(0.0f, 0.0f, 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0f, 0.0f, 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0f, 0.0f, 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0f, 0.0f, 0   ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0f, 0.0 , 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0f, 0.0 , 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0f, 0.0 , 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0f, 0.0 , 0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0f, 0.0l, 0.0f))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0f, 0.0l, 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0f, 0.0l, 0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0f, 0.0l, 0   ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0f, 0   , 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0f, 0   , 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0f, 0   , 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0f, 0   , 0   ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0.0f, 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0.0f, 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0 , 0.0f, 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0.0f, 0   ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0.0 , 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0.0 , 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0 , 0.0 , 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0.0 , 0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0 , 0.0l, 0.0f))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0 , 0.0l, 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0 , 0.0l, 0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0 , 0.0l, 0   ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0   , 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0   , 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0 , 0   , 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0.0 , 0   , 0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0f, 0.0f))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0f, 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0f, 0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0f, 0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0 , 0.0f))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0 , 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0 , 0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0 , 0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0l, 0.0f))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0l, 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0l, 0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0.0l, 0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0   , 0.0f))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0   , 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0   , 0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0.0l, 0   , 0   ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0.0f, 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0.0f, 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0   , 0.0f, 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0.0f, 0   ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0.0 , 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0.0 , 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0   , 0.0 , 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0.0 , 0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0   , 0.0l, 0.0f))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0   , 0.0l, 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0   , 0.0l, 0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0   , 0.0l, 0   ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0   , 0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0   , 0.0 ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::smoothstep(0   , 0   , 0.0l))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::smoothstep(0   , 0   , 0   ))>::value, "");

template <typename T1, typename T2, typename T3>
void SmoothStepTestFloat(void)
{
	HAMON_CONSTEXPR double error = 0.0000001;

	HAMON_CONSTEXPR auto nan1 = std::numeric_limits<T1>::quiet_NaN();
	HAMON_CONSTEXPR auto nan2 = std::numeric_limits<T2>::quiet_NaN();
	HAMON_CONSTEXPR auto nan3 = std::numeric_limits<T3>::quiet_NaN();
	HAMON_CONSTEXPR auto inf1 = std::numeric_limits<T1>::infinity();
	HAMON_CONSTEXPR auto inf2 = std::numeric_limits<T2>::infinity();
	HAMON_CONSTEXPR auto inf3 = std::numeric_limits<T3>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), -inf3), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3( -1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3( -0.10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3(  0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.02800, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3(  0.10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.15625, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3(  0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.50000, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3(  0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.84375, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3(  0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3(  1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::smoothstep(T1(  0.0), T2( 1.0), T3(  2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::smoothstep(T1(  0.0), T2(10.0), T3(  0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00725, (double)hamon::smoothstep(T1(  0.0), T2(10.0), T3(  0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.02800, (double)hamon::smoothstep(T1(  0.0), T2(10.0), T3(  1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.50000, (double)hamon::smoothstep(T1(  0.0), T2(10.0), T3(  5.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.97200, (double)hamon::smoothstep(T1(  0.0), T2(10.0), T3(  9.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.99275, (double)hamon::smoothstep(T1(  0.0), T2(10.0), T3(  9.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::smoothstep(T1(  0.0), T2(10.0), T3( 10.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::smoothstep(T1(  0.0), T2(10.0), T3( 10.10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::smoothstep(T1(  0.0), T2(10.0), inf3), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-6.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-5.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-5.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.001184, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-4.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.104000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.352000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.500000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.648000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.896000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.998816, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3(-0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.000000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.000000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3( 0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.000000, (double)hamon::smoothstep(T1( -5.0), T2( 0.0), T3( 1.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::smoothstep(T1( 1.0), T2( 1.0), T3(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::smoothstep(T1( 1.0), T2( 1.0), T3( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::smoothstep(T1( 1.0), T2( 1.0), T3( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::smoothstep(T1( 1.0), T2( 1.0), T3( 2.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::smoothstep(T1( 10.0), T2( 10.0), T3(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::smoothstep(T1( 10.0), T2( 10.0), T3( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::smoothstep(T1( 10.0), T2( 10.0), T3( 9.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::smoothstep(T1( 10.0), T2( 10.0), T3( 9.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::smoothstep(T1( 10.0), T2( 10.0), T3(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::smoothstep(T1( 10.0), T2( 10.0), T3(10.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::smoothstep(T1( 10.0), T2( 10.0), T3(11.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1, inf2,   inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(-inf1, inf2,  -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::smoothstep(-inf1, inf2,   T3(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::smoothstep(-inf1, inf2,   T3( 0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::smoothstep(-inf1, inf2,   T3( 1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(inf1,  inf2,   inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(inf1,  inf2,  -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(inf1,  inf2,   T3(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(inf1,  inf2,   T3( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(inf1,  inf2,   T3( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1,-inf2,   inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1,-inf2,  -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1,-inf2,   T3(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1,-inf2,   T3( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1,-inf2,   T3( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1, T2(0),  inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(-inf1, T2(0), -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1, T2(0),  T3(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1, T2(0),  T3( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(-inf1, T2(0),  T3( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(T1(0), inf2,   inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(T1(0), inf2,  -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(T1(0), inf2,   T3(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(T1(0), inf2,   T3( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(T1(0), inf2,   T3( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(T1(0), T2(0),  inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(T1(0), T2(0), -inf3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (0.0,         hamon::smoothstep(T1(0), T2(0),  T3(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(T1(0), T2(0),  T3( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ  (1.0,         hamon::smoothstep(T1(0), T2(0),  T3( 1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(T1( 1.0), T2( 0.0), T3(0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(T1(-1.0), T2(-2.0), T3(0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(T1(10.0), T2( 9.0), T3(0.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(nan1,  nan2,  nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(nan1,  nan2,  T3(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(nan1,  T2(0), nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(nan1,  T2(0), T3(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(T1(0), nan2,  nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(T1(0), nan2,  T3(0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan(hamon::smoothstep(T1(0), T2(0), nan3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(hamon::smoothstep(T1(0), T2(0), T3(0))));
}

template <typename T1, typename T2, typename T3>
void SmoothStepTestInteger(void)
{
	HAMON_CONSTEXPR double error = 0.000000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::smoothstep(T1(-10), T2(10), T3(-99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::smoothstep(T1(-10), T2(10), T3(-11)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::smoothstep(T1(-10), T2(10), T3(-10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00725, (double)hamon::smoothstep(T1(-10), T2(10), T3( -9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.02800, (double)hamon::smoothstep(T1(-10), T2(10), T3( -8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.06075, (double)hamon::smoothstep(T1(-10), T2(10), T3( -7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.10400, (double)hamon::smoothstep(T1(-10), T2(10), T3( -6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.15625, (double)hamon::smoothstep(T1(-10), T2(10), T3( -5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.21600, (double)hamon::smoothstep(T1(-10), T2(10), T3( -4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.28175, (double)hamon::smoothstep(T1(-10), T2(10), T3( -3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.35200, (double)hamon::smoothstep(T1(-10), T2(10), T3( -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.42525, (double)hamon::smoothstep(T1(-10), T2(10), T3( -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.50000, (double)hamon::smoothstep(T1(-10), T2(10), T3(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.57475, (double)hamon::smoothstep(T1(-10), T2(10), T3(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.64800, (double)hamon::smoothstep(T1(-10), T2(10), T3(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.71825, (double)hamon::smoothstep(T1(-10), T2(10), T3(  3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.78400, (double)hamon::smoothstep(T1(-10), T2(10), T3(  4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.84375, (double)hamon::smoothstep(T1(-10), T2(10), T3(  5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.89600, (double)hamon::smoothstep(T1(-10), T2(10), T3(  6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.93925, (double)hamon::smoothstep(T1(-10), T2(10), T3(  7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.97200, (double)hamon::smoothstep(T1(-10), T2(10), T3(  8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.99275, (double)hamon::smoothstep(T1(-10), T2(10), T3(  9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::smoothstep(T1(-10), T2(10), T3( 10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::smoothstep(T1(-10), T2(10), T3( 11)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::smoothstep(T1(-10), T2(10), T3(100)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000, (double)hamon::smoothstep(T1(50), T2(100), T3(-50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000, (double)hamon::smoothstep(T1(50), T2(100), T3(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000, (double)hamon::smoothstep(T1(50), T2(100), T3( 49)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000, (double)hamon::smoothstep(T1(50), T2(100), T3( 50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.001184, (double)hamon::smoothstep(T1(50), T2(100), T3( 51)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.004672, (double)hamon::smoothstep(T1(50), T2(100), T3( 52)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.470016, (double)hamon::smoothstep(T1(50), T2(100), T3( 74)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.500000, (double)hamon::smoothstep(T1(50), T2(100), T3( 75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.529984, (double)hamon::smoothstep(T1(50), T2(100), T3( 76)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.995328, (double)hamon::smoothstep(T1(50), T2(100), T3( 98)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.998816, (double)hamon::smoothstep(T1(50), T2(100), T3( 99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.000000, (double)hamon::smoothstep(T1(50), T2(100), T3(100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.000000, (double)hamon::smoothstep(T1(50), T2(100), T3(101)), error);
}

GTEST_TEST(CMathTest, SmoothStepTest)
{
//	SmoothStepTestFloat<float, float,       float>      ();
	SmoothStepTestFloat<float, float,       double>     ();
//	SmoothStepTestFloat<float, float,       long double>();
	SmoothStepTestFloat<float, double,      float>      ();
//	SmoothStepTestFloat<float, double,      double>     ();
	SmoothStepTestFloat<float, double,      long double>();
//	SmoothStepTestFloat<float, long double, float>      ();
	SmoothStepTestFloat<float, long double, double>     ();
//	SmoothStepTestFloat<float, long double, long double>();

	SmoothStepTestFloat<double, float,       float>      ();
//	SmoothStepTestFloat<double, float,       double>     ();
	SmoothStepTestFloat<double, float,       long double>();
//	SmoothStepTestFloat<double, double,      float>      ();
	SmoothStepTestFloat<double, double,      double>     ();
//	SmoothStepTestFloat<double, double,      long double>();
	SmoothStepTestFloat<double, long double, float>      ();
//	SmoothStepTestFloat<double, long double, double>     ();
	SmoothStepTestFloat<double, long double, long double>();

//	SmoothStepTestFloat<long double, float,       float>      ();
	SmoothStepTestFloat<long double, float,       double>     ();
//	SmoothStepTestFloat<long double, float,       long double>();
	SmoothStepTestFloat<long double, double,      float>      ();
//	SmoothStepTestFloat<long double, double,      double>     ();
	SmoothStepTestFloat<long double, double,      long double>();
//	SmoothStepTestFloat<long double, long double, float>      ();
	SmoothStepTestFloat<long double, long double, double>     ();
//	SmoothStepTestFloat<long double, long double, long double>();

	SmoothStepTestInteger<int, int,         int>();
//	SmoothStepTestInteger<int, int,         float>();
	SmoothStepTestInteger<int, int,         double>();
//	SmoothStepTestInteger<int, int,         long double>();
	SmoothStepTestInteger<int, float,       int>();
//	SmoothStepTestInteger<int, double,      int>();
	SmoothStepTestInteger<int, long double, int>();

//	SmoothStepTestInteger<float, int,         int>();
	SmoothStepTestInteger<float, int,         float>();
//	SmoothStepTestInteger<float, int,         double>();
	SmoothStepTestInteger<float, int,         long double>();
//	SmoothStepTestInteger<float, float,       int>();
	SmoothStepTestInteger<float, double,      int>();
//	SmoothStepTestInteger<float, long double, int>();
}

}	// namespace smoothstep_test

}	// namespace hamon_cmath_test
