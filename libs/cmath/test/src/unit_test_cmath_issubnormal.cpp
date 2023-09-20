/**
 *	@file	unit_test_cmath_issubnormal.cpp
 *
 *	@brief	issubnormal のテスト
 */

#include <hamon/cmath/issubnormal.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4756 4723 4056)

namespace hamon_cmath_test
{

namespace issubnormal_test
{

static_assert(hamon::is_same<bool, decltype(hamon::issubnormal(0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::issubnormal(0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::issubnormal(0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::issubnormal(0   ))>::value, "");

template <typename T>
void IsSubnormalTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto denorm_min = hamon::numeric_limits<T>::denorm_min();
	T zero = 0;	// MSVCでのエラーを避けるために変数にする

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(-inf));
	EXPECT_FALSE(hamon::issubnormal(hamon::exp(T(80000))));
	EXPECT_FALSE(hamon::issubnormal(T(1) / zero));
	EXPECT_FALSE(hamon::issubnormal(max * T(2)));
	EXPECT_FALSE(hamon::issubnormal(lowest * T(2)));
	EXPECT_FALSE(hamon::issubnormal(nan));
	EXPECT_FALSE(hamon::issubnormal(-nan));
	EXPECT_FALSE(hamon::issubnormal(inf - inf));
	EXPECT_FALSE(hamon::issubnormal(zero / zero));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(min * T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(1) / min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::issubnormal(min / T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::issubnormal(T(1) / max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::issubnormal(T(1) / lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::issubnormal(denorm_min));
}

template <typename T>
void IsSubnormalTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(max));
}

template <typename T>
void IsSubnormalTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::issubnormal(max));
}

GTEST_TEST(CMathTest, IsSubnormalTest)
{
	IsSubnormalTestFloat<float>();
	IsSubnormalTestFloat<double>();
	IsSubnormalTestFloat<long double>();

//	IsSubnormalTestSignedInt<int>();
	IsSubnormalTestSignedInt<signed char>();
//	IsSubnormalTestSignedInt<short>();
	IsSubnormalTestSignedInt<long>();
//	IsSubnormalTestSignedInt<long long>();

	IsSubnormalTestUnsignedInt<unsigned int>();
//	IsSubnormalTestUnsignedInt<unsigned char>();
	IsSubnormalTestUnsignedInt<unsigned short>();
//	IsSubnormalTestUnsignedInt<unsigned long>();
	IsSubnormalTestUnsignedInt<unsigned long long>();
}

}	// namespace issubnormal_test

}	// namespace hamon_cmath_test

HAMON_WARNING_POP()
