/**
 *	@file	unit_test_cmath_trunc.cpp
 *
 *	@brief	trunc のテスト
 */

#include <hamon/cmath/trunc.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace trunc_test
{

static_assert(hamon::is_same<float,       decltype(hamon::trunc(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::truncf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::trunc(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::trunc(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::trunc(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::truncl(0.0l))>::value, "");

template <typename T>
void TruncTestFloat(void)
{
	HAMON_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon() * 2;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T( 0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T( 0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T( 1.0) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::trunc(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::trunc(T( 1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::trunc(T( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::trunc(T( 1.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::trunc(T( 2.0) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), hamon::trunc(T( 2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), hamon::trunc(T( 2.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), hamon::trunc(T( 2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), hamon::trunc(T( 2.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), hamon::trunc(T( 3.0) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 3.0), hamon::trunc(T( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T(-0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T(-0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::trunc(T(-1.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::trunc(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::trunc(T(-1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::trunc(T(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::trunc(T(-1.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::trunc(T(-2.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::trunc(T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::trunc(T(-2.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::trunc(T(-2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::trunc(T(-2.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), hamon::trunc(T(-3.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-3.0), hamon::trunc(T(-3.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::trunc(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::trunc(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::trunc(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::trunc(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::trunc(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::trunc(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::trunc(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::trunc(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::trunc(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::trunc(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::trunc(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::trunc(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::trunc(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::trunc(-nan)));
}

template <typename T>
void TruncTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(   0), hamon::trunc(T(   0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(   1), hamon::trunc(T(   1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  -1), hamon::trunc(T(  -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(   3), hamon::trunc(T(   3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(  -3), hamon::trunc(T(  -3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 100), hamon::trunc(T( 100)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-100), hamon::trunc(T(-100)));
}

template <typename T>
void TruncTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(   0), hamon::trunc(T(   0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(   1), hamon::trunc(T(   1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(   3), hamon::trunc(T(   3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 100), hamon::trunc(T( 100)));
}

GTEST_TEST(CMathTest, TruncTest)
{
	TruncTestFloat<float>();
	TruncTestFloat<double>();
	TruncTestFloat<long double>();

	TruncTestSignedInt<int>();
//	TruncTestSignedInt<signed char>();
	TruncTestSignedInt<short>();
//	TruncTestSignedInt<long>();
	TruncTestSignedInt<long long>();

//	TruncTestUnsignedInt<unsigned int>();
	TruncTestUnsignedInt<unsigned char>();
//	TruncTestUnsignedInt<unsigned short>();
	TruncTestUnsignedInt<unsigned long>();
//	TruncTestUnsignedInt<unsigned long long>();
}

}	// namespace trunc_test

}	// namespace hamon_cmath_test
