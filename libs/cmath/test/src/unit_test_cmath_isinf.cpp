/**
 *	@file	unit_test_cmath_isinf.cpp
 *
 *	@brief	isinf のテスト
 */

#include <hamon/cmath/isinf.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace isinf_test
{

static_assert(hamon::is_same<bool, decltype(hamon::isinf(0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isinf(0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isinf(0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isinf(0   ))>::value, "");

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4056)	// 浮動小数点数の定数演算でオーバーフローしました。
HAMON_WARNING_DISABLE_MSVC(4723)	// 除算の 2 番目のオペランドは、コンパイル時に 0 と評価され、不定の結果を返します。

template <typename T>
void IsInfTestFloat(void)
{
	HAMON_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf(inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf(-inf));
	EXPECT_TRUE(hamon::isinf(T(1) / zero));
	EXPECT_TRUE(hamon::isinf(max * T(2)));

	EXPECT_FALSE(hamon::isinf(nan));
	EXPECT_FALSE(hamon::isinf(-nan));
	EXPECT_FALSE(hamon::isinf(inf - inf));
	EXPECT_FALSE(hamon::isinf(zero / zero));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(min * T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(min / T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(1) / min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(1) / max));
}

HAMON_WARNING_POP()

template <typename T>
void IsInfTestSignedInt(void)
{
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(max));
}

template <typename T>
void IsInfTestUnsignedInt(void)
{
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isinf(max));
}

GTEST_TEST(CMathTest, IsInfTest)
{
	IsInfTestFloat<float>();
	IsInfTestFloat<double>();
	IsInfTestFloat<long double>();

	IsInfTestSignedInt<int>();
//	IsInfTestSignedInt<signed char>();
	IsInfTestSignedInt<short>();
//	IsInfTestSignedInt<long>();
	IsInfTestSignedInt<long long>();

//	IsInfTestUnsignedInt<unsigned int>();
	IsInfTestUnsignedInt<unsigned char>();
//	IsInfTestUnsignedInt<unsigned short>();
	IsInfTestUnsignedInt<unsigned long>();
//	IsInfTestUnsignedInt<unsigned long long>();
}

}	// namespace isinf_test

}	// namespace hamon_cmath_test
