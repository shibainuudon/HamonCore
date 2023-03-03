/**
 *	@file	unit_test_cmath_saturate.cpp
 *
 *	@brief	saturate のテスト
 */

#include <hamon/cmath/saturate.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace saturate_test
{

static_assert(hamon::is_same<float,       decltype(hamon::saturate(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::saturate(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::saturate(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::saturate(0.0l))>::value, "");

template <typename T>
void SaturateTestFloat(void)
{
	HAMON_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::saturate(T(lowest)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::saturate(T(-0.2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::saturate(T(-0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::saturate(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.1), hamon::saturate(T( 0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.2), hamon::saturate(T( 0.2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.9), hamon::saturate(T( 0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.0), hamon::saturate(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.0), hamon::saturate(T( 1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.0), hamon::saturate(T(max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.0), hamon::saturate(T(inf)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::saturate(nan)));
}

template <typename T>
void SaturateTestSignedInt(void)
{
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::saturate(T(lowest)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::saturate(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::saturate(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::saturate(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::saturate(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::saturate(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::saturate(T(max)));
}

template <typename T>
void SaturateTestUnsignedInt(void)
{
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::saturate(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::saturate(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::saturate(T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), hamon::saturate(T(max)));
}

GTEST_TEST(CMathTest, SaturateTest)
{
	SaturateTestFloat<float>();
	SaturateTestFloat<double>();
	SaturateTestFloat<long double>();

	SaturateTestSignedInt<int>();
	SaturateTestSignedInt<signed char>();
//	SaturateTestSignedInt<short>();
	SaturateTestSignedInt<long>();
//	SaturateTestSignedInt<long long>();

	SaturateTestUnsignedInt<unsigned int>();
//	SaturateTestUnsignedInt<unsigned char>();
	SaturateTestUnsignedInt<unsigned short>();
//	SaturateTestUnsignedInt<unsigned long>();
	SaturateTestUnsignedInt<unsigned long long>();
}

}	// namespace saturate_test

}	// namespace hamon_cmath_test
