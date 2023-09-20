/**
 *	@file	unit_test_cmath_atan2.cpp
 *
 *	@brief	atan2 のテスト
 */

#include <hamon/cmath/atan2.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace atan2_test
{

static_assert(hamon::is_same<float,       decltype(hamon::atan2(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::atan2f(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan2(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan2(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan2(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan2(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan2(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan2(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan2(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan2(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan2(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan2(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan2l(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan2(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan2(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan2(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan2(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan2(0   , 0   ))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 0.000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 0.000000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 0.000000000001;
}

template <typename T1, typename T2>
void Atan2TestFloat()
{
	using R = hamon::float_promote_t<T1, T2>;
	HAMON_CXX11_CONSTEXPR auto nan1 = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = hamon::numeric_limits<T2>::infinity();

	HAMON_CXX11_CONSTEXPR auto pi                = hamon::numbers::pi_fn<R>();
	HAMON_CXX11_CONSTEXPR auto half_pi           = hamon::numbers::pi_fn<R>() / 2;
	HAMON_CXX11_CONSTEXPR auto three_quarters_pi = hamon::numbers::pi_fn<R>() * 3 / 4;
	HAMON_CXX11_CONSTEXPR auto quarter_pi        = hamon::numbers::pi_fn<R>() / 4;

	HAMON_CXX11_CONSTEXPR double error = get_error<R>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.00, (double)hamon::atan2(T1( 0.0), T2( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.00, (double)hamon::atan2(T1( 0.0), T2( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.00, (double)hamon::atan2(T1( 0.0), T2( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.25, (double)hamon::atan2(T1( 1.0), T2( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.25, (double)hamon::atan2(T1( 2.0), T2( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.25, (double)hamon::atan2(T1( 0.5), T2( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.50, (double)hamon::atan2(T1( 1.0), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.50, (double)hamon::atan2(T1( 2.0), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.50, (double)hamon::atan2(T1( 0.5), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.75, (double)hamon::atan2(T1( 1.0), T2(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.75, (double)hamon::atan2(T1( 2.0), T2(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  0.75, (double)hamon::atan2(T1( 0.5), T2(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  1.00, (double)hamon::atan2(T1( 0.0), T2(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  1.00, (double)hamon::atan2(T1( 0.0), T2(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi *  1.00, (double)hamon::atan2(T1( 0.0), T2(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.75, (double)hamon::atan2(T1(-1.0), T2(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.75, (double)hamon::atan2(T1(-2.0), T2(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.75, (double)hamon::atan2(T1(-0.5), T2(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.50, (double)hamon::atan2(T1(-1.0), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.50, (double)hamon::atan2(T1(-2.0), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.50, (double)hamon::atan2(T1(-0.5), T2( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.25, (double)hamon::atan2(T1(-1.0), T2( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.25, (double)hamon::atan2(T1(-2.0), T2( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)pi * -0.25, (double)hamon::atan2(T1(-0.5), T2( 0.5)), error);

	//If y is ±0 and x is negative or -0, ±π is returned
//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( pi, (double)hamon::atan2(T1(+0.0), T2(-0.0)), error);
//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-pi, (double)hamon::atan2(T1(-0.0), T2(-0.0)), error);
	// ※HAMONでは-0と+0を区別しない
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::atan2(T1(+0.0), T2(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::atan2(T1(-0.0), T2(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( pi, hamon::atan2(T1(+0.0), T2(-1.0)));
//	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-pi, hamon::atan2(T1(-0.0), T2(-1.0)));
	// ※HAMONでは-0と+0を区別しない
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( pi, hamon::atan2(T1(-0.0), T2(-1.0)));

	//If y is ±0 and x is positive or +0, ±0 is returned
	// ※HAMONでは-0と+0を区別しない
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::atan2(T1(+0.0), T2(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::atan2(T1(-0.0), T2(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::atan2(T1(+0.0), T2(+1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, hamon::atan2(T1(-0.0), T2(+1.0)));

	//If y is ±∞ and x is finite, ±π/2 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( half_pi, hamon::atan2( inf1, T2(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-half_pi, hamon::atan2(-inf1, T2(1.0)));

	//If y is ±∞ and x is -∞, ±3π/4 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( three_quarters_pi, hamon::atan2( inf1, -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-three_quarters_pi, hamon::atan2(-inf1, -inf2));

	//If y is ±∞ and x is +∞, ±π/4 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( quarter_pi, hamon::atan2( inf1, inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-quarter_pi, hamon::atan2(-inf1, inf2));

	//If x is ±0 and y is negative, -π/2 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-half_pi, hamon::atan2(T1(-1.0), T2(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-half_pi, hamon::atan2(T1(-1.0), T2(-0.0)));

	//If x is ±0 and y is positive, +π/2 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(half_pi, hamon::atan2(T1(+1.0), T2(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(half_pi, hamon::atan2(T1(+1.0), T2(-0.0)));

	//If x is -∞ and y is finite and positive, +π is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(pi, hamon::atan2(T1(+1.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(pi, hamon::atan2(T1(+1.0), -inf2));

	//If x is -∞ and y is finite and negative, -π is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-pi, hamon::atan2(T1(-1.0), -inf2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-pi, hamon::atan2(T1(-1.0), -inf2));

	//If x is +∞ and y is finite and positive, +0 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atan2(T1(+1.0), +inf2));

	//If x is +∞ and y is finite and negative, -0 is returned
	// ※HAMONでは-0と+0を区別しない
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atan2(T1(-1.0), +inf2));

	//If either x is NaN or y is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+nan1,    T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+nan1,    T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+nan1,    T2(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+nan1,    T2(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+nan1,    +inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+nan1,    -inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-nan1,    T2(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-nan1,    T2(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-nan1,    T2(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-nan1,    T2(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-nan1,    +inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-nan1,    -inf2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(T1(+0.0), +nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(T1(-0.0), +nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(T1(+1.0), +nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(T1(-1.0), +nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+inf1,    +nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-inf1,    +nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(T1(+0.0), -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(T1(-0.0), -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(T1(+1.0), -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(T1(-1.0), -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+inf1,    -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-inf1,    -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+nan1,    +nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(+nan1,    -nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-nan1,    +nan2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan2(-nan1,    -nan2)));
}

template <typename T1, typename T2>
void Atan2TestInteger(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR auto pi = hamon::numbers::pi_fn<double>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.00, (double)hamon::atan2(T1( 0), T2( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.25, (double)hamon::atan2(T1( 1), T2( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.50, (double)hamon::atan2(T1( 1), T2( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.75, (double)hamon::atan2(T1( 1), T2(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  1.00, (double)hamon::atan2(T1( 0), T2(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.75, (double)hamon::atan2(T1(-1), T2(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.50, (double)hamon::atan2(T1(-1), T2( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.25, (double)hamon::atan2(T1(-1), T2( 1)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.00, (double)hamon::atan2(T1( 0), T2( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.25, (double)hamon::atan2(T1( 2), T2( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.50, (double)hamon::atan2(T1( 2), T2( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.75, (double)hamon::atan2(T1( 2), T2(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  1.00, (double)hamon::atan2(T1( 0), T2(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.75, (double)hamon::atan2(T1(-2), T2(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.50, (double)hamon::atan2(T1(-2), T2( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.25, (double)hamon::atan2(T1(-2), T2( 2)), error);
}

GTEST_TEST(CMathTest, Atan2Test)
{
	Atan2TestFloat<float,       float>      ();
//	Atan2TestFloat<float,       double>     ();
	Atan2TestFloat<float,       long double>();
//	Atan2TestFloat<double,      float>      ();
	Atan2TestFloat<double,      double>     ();
//	Atan2TestFloat<double,      long double>();
	Atan2TestFloat<long double, float>      ();
//	Atan2TestFloat<long double, double>     ();
	Atan2TestFloat<long double, long double>();

	Atan2TestInteger<int,         int>();
	Atan2TestInteger<int,         float>();
//	Atan2TestInteger<int,         double>();
	Atan2TestInteger<int,         long double>();
//	Atan2TestInteger<float,       int>();
	Atan2TestInteger<double,      int>();
	Atan2TestInteger<long double, int>();
}

}	// namespace atan2_test

}	// namespace hamon_cmath_test
