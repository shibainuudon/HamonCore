/**
 *	@file	unit_test_cmath_nearbyint.cpp
 *
 *	@brief	nearbyint のテスト
 */

#include <hamon/cmath/nearbyint.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace nearbyint_test
{

static_assert(hamon::is_same<float,       decltype(hamon::nearbyint(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::nearbyintf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nearbyint(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nearbyint(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nearbyint(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nearbyintl(0.0l))>::value, "");

template <typename T>
void NearbyIntTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();

	switch (std::fegetround())
	{
	case FE_DOWNWARD:
		EXPECT_EQ(T( 0.0), hamon::nearbyint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::nearbyint(T( 2.5)));
		EXPECT_EQ(T(-3.0), hamon::nearbyint(T(-2.5)));
		EXPECT_EQ(T( 3.0), hamon::nearbyint(T( 3.5)));
		EXPECT_EQ(T(-4.0), hamon::nearbyint(T(-3.5)));
		break;
	case FE_TONEAREST:
		EXPECT_EQ(T( 0.0), hamon::nearbyint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::nearbyint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::nearbyint(T(-2.5)));
		EXPECT_EQ(T( 4.0), hamon::nearbyint(T( 3.5)));
		EXPECT_EQ(T(-4.0), hamon::nearbyint(T(-3.5)));
		break;
	case FE_TOWARDZERO:
		EXPECT_EQ(T( 0.0), hamon::nearbyint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::nearbyint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::nearbyint(T(-2.5)));
		EXPECT_EQ(T( 3.0), hamon::nearbyint(T( 3.5)));
		EXPECT_EQ(T(-3.0), hamon::nearbyint(T(-3.5)));
		break;
	case FE_UPWARD:
		EXPECT_EQ(T( 0.0), hamon::nearbyint(T( 0.0)));
		EXPECT_EQ(T( 3.0), hamon::nearbyint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::nearbyint(T(-2.5)));
		EXPECT_EQ(T( 4.0), hamon::nearbyint(T( 3.5)));
		EXPECT_EQ(T(-3.0), hamon::nearbyint(T(-3.5)));
		break;
	}

	EXPECT_EQ(+inf, hamon::nearbyint(+inf));
	EXPECT_EQ(-inf, hamon::nearbyint(-inf));
	EXPECT_TRUE(hamon::isnan(hamon::nearbyint(nan)));
}

template <typename T>
void NearbyIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, hamon::nearbyint(T( 0)));
	EXPECT_EQ( 2.0, hamon::nearbyint(T( 2)));
	EXPECT_EQ(-2.0, hamon::nearbyint(T(-2)));
	EXPECT_EQ( 3.0, hamon::nearbyint(T( 3)));
	EXPECT_EQ(-3.0, hamon::nearbyint(T(-3)));
}

template <typename T>
void NearbyIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, hamon::nearbyint(T( 0)));
	EXPECT_EQ( 2.0, hamon::nearbyint(T( 2)));
	EXPECT_EQ( 3.0, hamon::nearbyint(T( 3)));
}

GTEST_TEST(CMathTest, NearbyIntTest)
{
	NearbyIntTestFloat<float>();
	NearbyIntTestFloat<double>();
	NearbyIntTestFloat<long double>();

	NearbyIntTestSignedInt<int>();
//	NearbyIntTestSignedInt<signed char>();
	NearbyIntTestSignedInt<short>();
//	NearbyIntTestSignedInt<long>();
	NearbyIntTestSignedInt<long long>();

//	NearbyIntTestUnsignedInt<unsigned int>();
	NearbyIntTestUnsignedInt<unsigned char>();
//	NearbyIntTestUnsignedInt<unsigned short>();
	NearbyIntTestUnsignedInt<unsigned long>();
//	NearbyIntTestUnsignedInt<unsigned long long>();
}

}	// namespace nearbyint_test

}	// namespace hamon_cmath_test
