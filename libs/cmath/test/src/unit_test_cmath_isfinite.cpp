/**
 *	@file	unit_test_cmath_isfinite.cpp
 *
 *	@brief	isfinite のテスト
 */

#include <hamon/cmath/isfinite.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4756 4723 4056)

namespace hamon_cmath_test
{

namespace isfinite_test
{

static_assert(hamon::is_same<bool, decltype(hamon::isfinite(0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isfinite(0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isfinite(0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::isfinite(0   ))>::value, "");

template <typename T>
void IsFiniteTestFloat(void)
{
	HAMON_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isfinite(inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::isfinite(-inf));
	EXPECT_FALSE(hamon::isfinite(T(1) / zero));
	EXPECT_FALSE(hamon::isfinite(max * T(2)));
	EXPECT_FALSE(hamon::isfinite(lowest * T(2)));
	EXPECT_FALSE(hamon::isfinite(nan));
	EXPECT_FALSE(hamon::isfinite(-nan));
//	EXPECT_FALSE(hamon::isfinite(inf - inf));
	EXPECT_FALSE(hamon::isfinite(zero / zero));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(min * T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(min / T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(1) / min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(1) / max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(1) / lowest));
}

template <typename T>
void IsFiniteTestSignedInt(void)
{
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(max));
}

template <typename T>
void IsFiniteTestUnsignedInt(void)
{
	HAMON_CONSTEXPR auto min = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto max = std::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isfinite(max));
}

GTEST_TEST(CMathTest, IsFiniteTest)
{
	IsFiniteTestFloat<float>();
	IsFiniteTestFloat<double>();
	IsFiniteTestFloat<long double>();

	IsFiniteTestSignedInt<int>();
//	IsFiniteTestSignedInt<signed char>();
	IsFiniteTestSignedInt<short>();
//	IsFiniteTestSignedInt<long>();
	IsFiniteTestSignedInt<long long>();

//	IsFiniteTestUnsignedInt<unsigned int>();
	IsFiniteTestUnsignedInt<unsigned char>();
//	IsFiniteTestUnsignedInt<unsigned short>();
	IsFiniteTestUnsignedInt<unsigned long>();
//	IsFiniteTestUnsignedInt<unsigned long long>();
}

}	// namespace isfinite_test

}	// namespace hamon_cmath_test

HAMON_WARNING_POP()
