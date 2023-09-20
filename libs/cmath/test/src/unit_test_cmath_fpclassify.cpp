/**
 *	@file	unit_test_cmath_fpclassify.cpp
 *
 *	@brief	fpclassify のテスト
 */

#include <hamon/cmath/fpclassify.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fpclassify_test
{

static_assert(hamon::is_same<int, decltype(hamon::fpclassify(0.0f))>::value, "");
static_assert(hamon::is_same<int, decltype(hamon::fpclassify(0.0 ))>::value, "");
static_assert(hamon::is_same<int, decltype(hamon::fpclassify(0.0l))>::value, "");
static_assert(hamon::is_same<int, decltype(hamon::fpclassify(0   ))>::value, "");

template <typename T>
void FpClassifyTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto denorm_min = hamon::numeric_limits<T>::denorm_min();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_INFINITE,  hamon::fpclassify(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_INFINITE,  hamon::fpclassify(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NAN,       hamon::fpclassify(+nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NAN,       hamon::fpclassify(-nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL,    hamon::fpclassify(T(+1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL,    hamon::fpclassify(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ZERO,      hamon::fpclassify(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ZERO,      hamon::fpclassify(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL,    hamon::fpclassify(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL,    hamon::fpclassify(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL,    hamon::fpclassify(lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_SUBNORMAL, hamon::fpclassify( denorm_min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_SUBNORMAL, hamon::fpclassify(-denorm_min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_SUBNORMAL, hamon::fpclassify( min/2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_SUBNORMAL, hamon::fpclassify(-min/2));
}

template <typename T>
void FpClassifyTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ZERO,   hamon::fpclassify(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(max));
}

template <typename T>
void FpClassifyTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ZERO,   hamon::fpclassify(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ZERO,   hamon::fpclassify(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_NORMAL, hamon::fpclassify(max));
}

GTEST_TEST(CMathTest, FpClassifyTest)
{
	FpClassifyTestFloat<float>();
	FpClassifyTestFloat<double>();
	FpClassifyTestFloat<long double>();

	FpClassifyTestSignedInt<int>();
	FpClassifyTestSignedInt<signed char>();
	FpClassifyTestSignedInt<short>();
	FpClassifyTestSignedInt<long>();
	FpClassifyTestSignedInt<long long>();

	FpClassifyTestUnsignedInt<unsigned int>();
	FpClassifyTestUnsignedInt<unsigned char>();
	FpClassifyTestUnsignedInt<unsigned short>();
	FpClassifyTestUnsignedInt<unsigned long>();
	FpClassifyTestUnsignedInt<unsigned long long>();
}

}	// namespace fpclassify_test

}	// namespace hamon_cmath_test
