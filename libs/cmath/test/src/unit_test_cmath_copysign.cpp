/**
 *	@file	unit_test_cmath_copysign.cpp
 *
 *	@brief	copysign のテスト
 */

#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace copysign_test
{

static_assert(hamon::is_same<float,       decltype(hamon::copysign(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::copysignf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::copysign(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::copysign(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::copysign(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::copysign(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::copysign(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::copysign(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::copysign(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::copysign(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::copysign(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::copysign(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::copysignl(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::copysign(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::copysign(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::copysign(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::copysign(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::copysign(0   , 0   ))>::value, "");

template <typename T>
void CopysignTestFloat(void)
{
	HAMON_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::copysign(T( 1.0), T(+2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::copysign(T( 1.0), T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 5.0), hamon::copysign(T(-5.0), T(+2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-5.0), hamon::copysign(T(-5.0), T(-2.0)));
	
	// HAMONでは、yが±0のときはxの符号は変更されない
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), hamon::copysign(T( 2.0), T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), hamon::copysign(T( 2.0), T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-3.0), hamon::copysign(T(-3.0), T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-3.0), hamon::copysign(T(-3.0), T(-0.0)));
	
	// HAMONでは、yが±NaNのときはxの符号は変更されない
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 4.0), hamon::copysign(T( 4.0), +nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 4.0), hamon::copysign(T( 4.0), -nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-5.0), hamon::copysign(T(-5.0), +nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-5.0), hamon::copysign(T(-5.0), -nan));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 6.0), hamon::copysign(T( 6.0), +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-6.0), hamon::copysign(T( 6.0), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 7.0), hamon::copysign(T(-7.0), +inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-7.0), hamon::copysign(T(-7.0), -inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( max, hamon::copysign(max, T(+1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-max, hamon::copysign(max, T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( min, hamon::copysign(min, T(+1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-min, hamon::copysign(min, T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( max, hamon::copysign(lowest, T(+1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-max, hamon::copysign(lowest, T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf, hamon::copysign(inf, T(+3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::copysign(inf, T(-3.0)));

	// HAMONでは、+NaNと-NaNは区別されない
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::copysign(nan, T(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::copysign(nan, T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(nan, T(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(nan, T(-1.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::copysign(nan, T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::copysign(nan, T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(nan, T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(nan, T(-0.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::copysign(nan,  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::copysign(nan, -nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(nan,  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(nan, -nan)));

	// HAMONでは、+0と-0は区別されない
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::copysign(T(0), T(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::copysign(T(0), T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(T(0), T(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(T(0), T(-1.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::copysign(T(0), T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::copysign(T(0), T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(T(0), T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(T(0), T(-0.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::copysign(T(0),  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::copysign(T(0), -nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(T(0),  nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::copysign(T(0), -nan)));
}

template <typename T>
void CopysignTestSignedInt(void)
{
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::copysign(T(1), T(+2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::copysign(T(1), T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 5), hamon::copysign(T(-5), +2.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-5), hamon::copysign(T(-5), -2.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( max, hamon::copysign(max, +1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-max, hamon::copysign(max, -1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-double(min), hamon::copysign(min, T(+1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( double(min), hamon::copysign(min, T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-double(min), hamon::copysign(lowest, T(+1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( double(min), hamon::copysign(lowest, T(-1)));
}

template <typename T>
void CopysignTestUnsignedInt(void)
{
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::copysign(T(1), T(+2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0, hamon::copysign(T(1), -2.0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( double(max), hamon::copysign(max, +1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-double(max), hamon::copysign(max, -1.0f));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( min, hamon::copysign(min, +1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( min, hamon::copysign(min, -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( lowest, hamon::copysign(lowest, +1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( lowest, hamon::copysign(lowest, -1));
}

GTEST_TEST(CMathTest, CopySignTest)
{
	CopysignTestFloat<float>();
	CopysignTestFloat<double>();
	CopysignTestFloat<long double>();

	CopysignTestSignedInt<int>();
//	CopysignTestSignedInt<signed char>();
	CopysignTestSignedInt<short>();
//	CopysignTestSignedInt<long>();
	CopysignTestSignedInt<long long>();

	CopysignTestUnsignedInt<unsigned int>();
	CopysignTestUnsignedInt<unsigned char>();
//	CopysignTestUnsignedInt<unsigned short>();
	CopysignTestUnsignedInt<unsigned long>();
//	CopysignTestUnsignedInt<unsigned long long>();
}

}	// namespace copysign_test

}	// namespace hamon_cmath_test
