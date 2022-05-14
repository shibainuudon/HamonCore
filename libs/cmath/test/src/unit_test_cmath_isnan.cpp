/**
 *	@file	unit_test_cmath_isnan.cpp
 *
 *	@brief	isnan のテスト
 */

#include <hamon/cmath/isnan.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace isnan_test
{

static_assert(std::is_same<bool, decltype(hamon::isnan(0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isnan(0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isnan(0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::isnan(0   ))>::value, "");

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4056)	// 浮動小数点数の定数演算でオーバーフローしました。
HAMON_WARNING_DISABLE_MSVC(4723)	// 除算の 2 番目のオペランドは、コンパイル時に 0 と評価され、不定の結果を返します。

template <typename T>
void IsNaNTestFloat(void)
{
	HAMON_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(+nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(-nan));
//	EXPECT_TRUE(hamon::isnan(inf - inf));
	EXPECT_TRUE(hamon::isnan(zero / zero));

	EXPECT_FALSE(hamon::isnan(T(1) / zero));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(lowest));
	EXPECT_FALSE(hamon::isnan(max * T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(min * T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(min / T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(1) / min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(1) / max));
}

HAMON_WARNING_POP()

template <typename T>
void IsNaNTestSignedInt(void)
{
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(max));
}

template <typename T>
void IsNaNTestUnsignedInt(void)
{
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnan(max));
}

GTEST_TEST(CMathTest, IsNaNTest)
{
	IsNaNTestFloat<float>();
	IsNaNTestFloat<double>();
	IsNaNTestFloat<long double>();

//	IsNaNTestSignedInt<int>();
	IsNaNTestSignedInt<signed char>();
//	IsNaNTestSignedInt<short>();
	IsNaNTestSignedInt<long>();
//	IsNaNTestSignedInt<long long>();

	IsNaNTestUnsignedInt<unsigned int>();
//	IsNaNTestUnsignedInt<unsigned char>();
	IsNaNTestUnsignedInt<unsigned short>();
//	IsNaNTestUnsignedInt<unsigned long>();
	IsNaNTestUnsignedInt<unsigned long long>();
}

}	// namespace isnan_test

}	// namespace hamon_cmath_test
