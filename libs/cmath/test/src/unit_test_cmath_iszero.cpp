/**
 *	@file	unit_test_cmath_iszero.cpp
 *
 *	@brief	iszero のテスト
 */

#include <hamon/cmath/iszero.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace iszero_test
{

static_assert(std::is_same<bool, decltype(hamon::iszero(0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::iszero(0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::iszero(0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::iszero(0   ))>::value, "");

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4056)	// 浮動小数点数の定数演算でオーバーフローしました。
HAMON_WARNING_DISABLE_MSVC(4723)	// 除算の 2 番目のオペランドは、コンパイル時に 0 と評価され、不定の結果を返します。

template <typename T>
void IsZeroTestFloat(void)
{
	HAMON_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(-inf));
	EXPECT_FALSE(hamon::iszero(T(1) / zero));
	EXPECT_FALSE(hamon::iszero(max * T(2)));
	EXPECT_FALSE(hamon::iszero(lowest * T(2)));
	EXPECT_FALSE(hamon::iszero(nan));
	EXPECT_FALSE(hamon::iszero(-nan));
//	EXPECT_FALSE(hamon::iszero(inf - inf));
	EXPECT_FALSE(hamon::iszero(zero / zero));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(min * T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(T(1) / min));
}

HAMON_WARNING_POP()

template <typename T>
void IsZeroTestSignedInt(void)
{
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(max));
}

template <typename T>
void IsZeroTestUnsignedInt(void)
{
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::iszero(max));
}

GTEST_TEST(CMathTest, IsZeroTest)
{
	IsZeroTestFloat<float>();
	IsZeroTestFloat<double>();
	IsZeroTestFloat<long double>();

//	IsZeroTestSignedInt<int>();
	IsZeroTestSignedInt<signed char>();
//	IsZeroTestSignedInt<short>();
	IsZeroTestSignedInt<long>();
//	IsZeroTestSignedInt<long long>();

	IsZeroTestUnsignedInt<unsigned int>();
//	IsZeroTestUnsignedInt<unsigned char>();
	IsZeroTestUnsignedInt<unsigned short>();
//	IsZeroTestUnsignedInt<unsigned long>();
	IsZeroTestUnsignedInt<unsigned long long>();
}

}	// namespace iszero_test

}	// namespace hamon_cmath_test
