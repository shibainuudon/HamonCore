/**
 *	@file	unit_test_cmath_nexttoward.cpp
 *
 *	@brief	nexttoward のテスト
 */

#include <hamon/cmath/nexttoward.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace nexttoward_test
{

static_assert(hamon::is_same<float,       decltype(hamon::nexttoward(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::nexttowardf(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nexttoward(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nexttoward(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nexttowardl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nexttoward(0,    0.0l))>::value, "");

template <typename T>
void NextTowardTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::lowest();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(2.0) == hamon::nexttoward(T(+2.0), T(+2.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(2.0) <  hamon::nexttoward(T(+2.0), T(+3.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(2.0) >  hamon::nexttoward(T(+2.0), T(+1.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nexttoward(T(+2.0), T(+3.0)) == hamon::nexttoward(T(+2.0), +inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nexttoward(T(+2.0), T(+1.0)) == hamon::nexttoward(T(+2.0), -inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(5.0) < hamon::nexttoward(T(+5.0), +inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(T(5.0) > hamon::nexttoward(T(+5.0), -inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(max  == hamon::nexttoward(max, max));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(+inf == hamon::nexttoward(max, +inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(max  >  hamon::nexttoward(max, -inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(min  == hamon::nexttoward(min, min));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(-inf == hamon::nexttoward(min, -inf));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(min  <  hamon::nexttoward(min, +inf));

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(max, hamon::nexttoward(+inf, T(0.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(min, hamon::nexttoward(-inf, T(0.0)));

	// if either from or to is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(nan,  T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(nan,  min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(nan,  max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(nan,  +inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(nan,  -inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(T(1), nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(min,  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(max,  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(+inf, nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(-inf, nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nexttoward(nan,  nan)));
}

GTEST_TEST(CMathTest, NextTowardTest)
{
	NextTowardTestFloat<float>();
	NextTowardTestFloat<double>();
#if !defined(HAMON_APPLE_CLANG)
	NextTowardTestFloat<long double>();
#endif
}

}	// namespace nexttoward_test

}	// namespace hamon_cmath_test
