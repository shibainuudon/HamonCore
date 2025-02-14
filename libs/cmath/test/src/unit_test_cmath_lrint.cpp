/**
 *	@file	unit_test_cmath_lrint.cpp
 *
 *	@brief	lrint のテスト
 */

#include <hamon/cmath/lrint.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace lrint_test
{

static_assert(hamon::is_same<long, decltype(hamon::lrint(0.0f))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lrintf(0.0f))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lrint(0.0 ))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lrint(0   ))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lrint(0.0l))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lrintl(0.0l))>::value, "");

template <typename T>
void LRIntTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto inf  = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto nan  = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto lmax = hamon::numeric_limits<long>::max();
	HAMON_CXX11_CONSTEXPR auto lmin = hamon::numeric_limits<long>::min();

	switch (std::fegetround())
	{
	case FE_DOWNWARD:
		EXPECT_EQ(T( 0.0), hamon::lrint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::lrint(T( 2.5)));
		EXPECT_EQ(T(-3.0), hamon::lrint(T(-2.5)));
		EXPECT_EQ(T( 3.0), hamon::lrint(T( 3.5)));
		EXPECT_EQ(T(-4.0), hamon::lrint(T(-3.5)));
		break;
	case FE_TONEAREST:
		EXPECT_EQ(T( 0.0), hamon::lrint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::lrint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::lrint(T(-2.5)));
		EXPECT_EQ(T( 4.0), hamon::lrint(T( 3.5)));
		EXPECT_EQ(T(-4.0), hamon::lrint(T(-3.5)));
		break;
	case FE_TOWARDZERO:
		EXPECT_EQ(T( 0.0), hamon::lrint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::lrint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::lrint(T(-2.5)));
		EXPECT_EQ(T( 3.0), hamon::lrint(T( 3.5)));
		EXPECT_EQ(T(-3.0), hamon::lrint(T(-3.5)));
		break;
	case FE_UPWARD:
		EXPECT_EQ(T( 0.0), hamon::lrint(T( 0.0)));
		EXPECT_EQ(T( 3.0), hamon::lrint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::lrint(T(-2.5)));
		EXPECT_EQ(T( 4.0), hamon::lrint(T( 3.5)));
		EXPECT_EQ(T(-3.0), hamon::lrint(T(-3.5)));
		break;
	}

	EXPECT_EQ(lmax,    hamon::lrint(+inf));
	EXPECT_EQ(lmin,    hamon::lrint(-inf));
	EXPECT_EQ(T( 0.0), hamon::lrint(nan));
}

template <typename T>
void LRIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, hamon::lrint(T( 0)));
	EXPECT_EQ( 2.0, hamon::lrint(T( 2)));
	EXPECT_EQ(-2.0, hamon::lrint(T(-2)));
	EXPECT_EQ( 3.0, hamon::lrint(T( 3)));
	EXPECT_EQ(-3.0, hamon::lrint(T(-3)));
}

template <typename T>
void LRIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, hamon::lrint(T( 0)));
	EXPECT_EQ( 2.0, hamon::lrint(T( 2)));
	EXPECT_EQ( 3.0, hamon::lrint(T( 3)));
}

GTEST_TEST(CMathTest, LRIntTest)
{
	LRIntTestFloat<float>();
	LRIntTestFloat<double>();
	LRIntTestFloat<long double>();

	LRIntTestSignedInt<int>();
//	LRIntTestSignedInt<signed char>();
	LRIntTestSignedInt<short>();
//	LRIntTestSignedInt<long>();
	LRIntTestSignedInt<long long>();

//	LRIntTestUnsignedInt<unsigned int>();
	LRIntTestUnsignedInt<unsigned char>();
//	LRIntTestUnsignedInt<unsigned short>();
	LRIntTestUnsignedInt<unsigned long>();
//	LRIntTestUnsignedInt<unsigned long long>();
}

}	// namespace lrint_test

}	// namespace hamon_cmath_test
