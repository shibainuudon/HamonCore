/**
 *	@file	unit_test_cmath_isnormal.cpp
 *
 *	@brief	isnormal のテスト
 */

#include <hamon/cmath/isnormal.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4756 4723 4056)

namespace hamon_cmath_test
{

namespace isnormal_test
{

static_assert(hamon::is_same<bool, decltype(hamon::isnormal(0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isnormal(0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isnormal(0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isnormal(0   ))>::value, "");

template <typename T>
void IsNormalTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto denorm_min = std::numeric_limits<T>::denorm_min();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(-inf));
	EXPECT_FALSE(hamon::isnormal(T(1) / zero));
	EXPECT_FALSE(hamon::isnormal(max * T(2)));
	EXPECT_FALSE(hamon::isnormal(lowest * T(2)));
	EXPECT_FALSE(hamon::isnormal(nan));
	EXPECT_FALSE(hamon::isnormal(-nan));
	EXPECT_FALSE(hamon::isnormal(inf - inf));
	EXPECT_FALSE(hamon::isnormal(zero / zero));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(min * T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(min / T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(T(1) / min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(T(1) / max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(T(1) / lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(denorm_min));
}

template <typename T>
void IsNormalTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(max));
}

template <typename T>
void IsNormalTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isnormal(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnormal(max));
}

GTEST_TEST(CMathTest, IsNormalTest)
{
	IsNormalTestFloat<float>();
	IsNormalTestFloat<double>();
	IsNormalTestFloat<long double>();

	IsNormalTestSignedInt<int>();
//	IsNormalTestSignedInt<signed char>();
	IsNormalTestSignedInt<short>();
//	IsNormalTestSignedInt<long>();
	IsNormalTestSignedInt<long long>();

//	IsNormalTestUnsignedInt<unsigned int>();
	IsNormalTestUnsignedInt<unsigned char>();
//	IsNormalTestUnsignedInt<unsigned short>();
	IsNormalTestUnsignedInt<unsigned long>();
//	IsNormalTestUnsignedInt<unsigned long long>();
}

}	// namespace isnormal_test

}	// namespace hamon_cmath_test

HAMON_WARNING_POP()
