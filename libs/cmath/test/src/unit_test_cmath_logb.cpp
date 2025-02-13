/**
 *	@file	unit_test_cmath_logb.cpp
 *
 *	@brief	logb のテスト
 */

#include <hamon/cmath/logb.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace frexp_test
{

static_assert(hamon::is_same<float,       decltype(hamon::logb(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::logbf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::logb(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::logb(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::logb(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::logbl(0.0l))>::value, "");

template <typename T>
void LogbTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T(-17.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T(-16.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T(-15.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T( -9.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T( -8.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T( -7.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T( -5.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T( -4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T( -3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T( -2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::logb(T( -1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::logb(T( -0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, hamon::logb(T( -0.25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::logb(T( -0.125)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::logb(T(  0.125)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, hamon::logb(T(  0.25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::logb(T(  0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::logb(T(  1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::logb(T(  1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T(  2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T(  2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T(  3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T(  3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  4.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  5.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  7.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T(  8.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T(  9.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T( 15.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T( 16.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T( 17.0)));

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::numeric_limits<T>::max_exponent - 1, hamon::logb(max));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::numeric_limits<T>::max_exponent - 1, hamon::logb(-max));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::numeric_limits<T>::min_exponent - 1, hamon::logb(min));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(hamon::numeric_limits<T>::min_exponent - 1, hamon::logb(-min));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::logb(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::logb(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::logb(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::logb(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::logb(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::logb(-nan)));
}

template <typename T>
void LogbTestSignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T(-17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T(-16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T(-15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T( -9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T( -8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T( -7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T( -5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T( -4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T( -3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::logb(T( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::logb(T(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T(  3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T(  8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T(  9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T( 15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T( 16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T( 17)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::logb(T(0)));
}

template <typename T>
void LogbTestUnsignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::logb(T(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::logb(T(  3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::logb(T(  7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T(  8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T(  9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::logb(T( 15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T( 16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::logb(T( 17)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::logb(T(0)));
}

GTEST_TEST(CMathTest, LogbTest)
{
	LogbTestFloat<float>();
	LogbTestFloat<double>();
#if !defined(HAMON_APPLE_CLANG)
	LogbTestFloat<long double>();
#endif

//	LogbTestSignedInt<int>();
	LogbTestSignedInt<signed char>();
//	LogbTestSignedInt<short>();
	LogbTestSignedInt<long>();
//	LogbTestSignedInt<long long>();

	LogbTestUnsignedInt<unsigned int>();
//	LogbTestUnsignedInt<unsigned char>();
	LogbTestUnsignedInt<unsigned short>();
//	LogbTestUnsignedInt<unsigned long>();
	LogbTestUnsignedInt<unsigned long long>();
}

}	// namespace frexp_test

}	// namespace hamon_cmath_test
