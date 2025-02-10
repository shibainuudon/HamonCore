/**
 *	@file	unit_test_cmath_nextafter.cpp
 *
 *	@brief	nextafter のテスト
 */

#include <hamon/cmath/nextafter.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fpclassify.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace nextafter_test
{

static_assert(hamon::is_same<float,       decltype(hamon::nextafter(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::nextafterf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextafter(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextafter(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextafter(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextafter(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextafter(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextafter(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextafter(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextafter(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextafter(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextafter(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextafterl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextafter(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextafter(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextafter(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextafter(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextafter(0   , 0   ))>::value, "");

template <typename T>
void NextAfterTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto denorm_min = hamon::numeric_limits<T>::denorm_min();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(2.0) == hamon::nextafter(T(+2.0), T(+2.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(2.0) < hamon::nextafter(T(+2.0), T(+3.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(2.0) > hamon::nextafter(T(+2.0), T(+1.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextafter(T(+2.0), T(+3.0)) == hamon::nextafter(T(+2.0), +inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextafter(T(+2.0), T(+1.0)) == hamon::nextafter(T(+2.0), -inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(5.0) < hamon::nextafter(T(+5.0), +inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(5.0) > hamon::nextafter(T(+5.0), -inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(max    == hamon::nextafter(max, max));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(+inf   == hamon::nextafter(max, +inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(max    >  hamon::nextafter(max, -inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(lowest == hamon::nextafter(lowest, lowest));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(-inf   == hamon::nextafter(lowest, -inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(lowest <  hamon::nextafter(lowest, +inf));

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(max,    hamon::nextafter(+inf, T(0.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(lowest, hamon::nextafter(-inf, T(0.0)));

	HAMON_CXX14_CONSTEXPR T t0 = hamon::nextafter(T(-0.0), T(2.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t0 == denorm_min);

	HAMON_CXX14_CONSTEXPR T t1 = hamon::nextafter(T(), T(1.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t1 == denorm_min);

	HAMON_CXX14_CONSTEXPR T t2 = hamon::nextafter(T(), T());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t2 == T());
	EXPECT_TRUE(!std::signbit(t2));

	HAMON_CXX14_CONSTEXPR T t3 = hamon::nextafter(denorm_min, T(-2.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t3 == T());
	EXPECT_TRUE(!std::signbit(t3));

	HAMON_CXX14_CONSTEXPR T t4 = hamon::nextafter(min, T(-0.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t4 > T());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t4) == FP_SUBNORMAL);

	HAMON_CXX14_CONSTEXPR T t5 = hamon::nextafter(t4, T(1.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t5 == min);

	HAMON_CXX14_CONSTEXPR T t6 = hamon::nextafter(min, inf);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t6 > min);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t6) == FP_NORMAL);

	HAMON_CXX14_CONSTEXPR T t7 = hamon::nextafter(t6, -inf);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t7 == min);

	HAMON_CXX14_CONSTEXPR T t8 = hamon::nextafter(T(16.0), T(16.5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t8 > t7);

	HAMON_CXX14_CONSTEXPR T t9 = hamon::nextafter(t8, T(15.5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t9 == T(16.0));

	HAMON_CXX14_CONSTEXPR T t10 = hamon::nextafter(max, T(-0.5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t10 < max);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t10) == FP_NORMAL);

	HAMON_CXX14_CONSTEXPR T t11 = hamon::nextafter(t10, inf);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t11 == max);

	HAMON_CXX14_CONSTEXPR T t12 = hamon::nextafter(t11, inf);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t12) == FP_INFINITE);
	EXPECT_TRUE(!std::signbit(t12));

	HAMON_CXX14_CONSTEXPR T t13 = hamon::nextafter(inf, t12);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t13 == t12);

	HAMON_CXX14_CONSTEXPR T t14 = hamon::nextafter(t13, T(1.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t14 == max);

	HAMON_CXX14_CONSTEXPR T t15 = hamon::nextafter(nan, T());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t15) == FP_NAN);

	HAMON_CXX14_CONSTEXPR T t16 = hamon::nextafter(T(17.0), nan);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t16) == FP_NAN);

	HAMON_CXX14_CONSTEXPR T t17 = hamon::nextafter(T(), T(-0.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t17 == T());
	EXPECT_TRUE(std::signbit(t17));

	HAMON_CXX14_CONSTEXPR T t20 = hamon::nextafter(T(-0.0), T(-2.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t20 == -denorm_min);

	HAMON_CXX14_CONSTEXPR T t21 = hamon::nextafter(T(), T(-1.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t21 == -denorm_min);

	HAMON_CXX14_CONSTEXPR T t22 = hamon::nextafter(T(-0.0), T(-0.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t22 == T());
	EXPECT_TRUE(std::signbit(t22));

	HAMON_CXX14_CONSTEXPR T t23 = hamon::nextafter(-denorm_min, T(2.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t23 == T());
	EXPECT_TRUE(std::signbit(t23));

	HAMON_CXX14_CONSTEXPR T t24 = hamon::nextafter(-min, T());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t24 < T());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t24) == FP_SUBNORMAL);

	HAMON_CXX14_CONSTEXPR T t25 = hamon::nextafter(t24, T(-1.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t25 == -min);

	HAMON_CXX14_CONSTEXPR T t26 = hamon::nextafter(-min, -inf);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t26 < -min);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t26) == FP_NORMAL);

	HAMON_CXX14_CONSTEXPR T t27 = hamon::nextafter(t26, inf);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t27 == -min);

	HAMON_CXX14_CONSTEXPR T t28 = hamon::nextafter(T(-16.0), T(-16.5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t28 < t27);

	HAMON_CXX14_CONSTEXPR T t29 = hamon::nextafter(t28, T(-15.5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t29 == T(-16.0));

	HAMON_CXX14_CONSTEXPR T t30 = hamon::nextafter(-max, T(0.5));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t30 > -max);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t30) == FP_NORMAL);

	HAMON_CXX14_CONSTEXPR T t31 = hamon::nextafter(t30, -inf);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t31 == -max);

	HAMON_CXX14_CONSTEXPR T t32 = hamon::nextafter(t31, -inf);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t32) == FP_INFINITE);
	EXPECT_TRUE(std::signbit(t32));

	HAMON_CXX14_CONSTEXPR T t33 = hamon::nextafter(-inf, t32);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t33 == t32);

	HAMON_CXX14_CONSTEXPR T t34 = hamon::nextafter(t33, T(-1.0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t34 == -max);

	HAMON_CXX14_CONSTEXPR T t35 = hamon::nextafter(-nan, T());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t35) == FP_NAN);

	HAMON_CXX14_CONSTEXPR T t36 = hamon::nextafter(T(-17.0), nan);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::fpclassify(t36) == FP_NAN);

	HAMON_CXX14_CONSTEXPR T t37 = hamon::nextafter(T(-0.0), T());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(t37 == T());
	EXPECT_TRUE(!std::signbit(t37));

	// if either from or to is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(nan,  T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(nan,  min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(nan,  max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(nan,  +inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(nan,  -inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(T(1), nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(min,  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(max,  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(+inf, nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(-inf, nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextafter(nan,  nan)));
}

GTEST_TEST(CMathTest, NextAfterTest)
{
	NextAfterTestFloat<float>();
	NextAfterTestFloat<double>();
#if !defined(HAMON_APPLE_CLANG)
	NextAfterTestFloat<long double>();
#endif
}

}	// namespace nextafter_test

}	// namespace hamon_cmath_test
