/**
 *	@file	unit_test_cmath_rint.cpp
 *
 *	@brief	rint のテスト
 */

#include <hamon/cmath/rint.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace rint_test
{

static_assert(hamon::is_same<float,       decltype(hamon::rint(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::rintf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::rint(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::rint(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::rint(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::rintl(0.0l))>::value, "");

template <typename T>
void RIntTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();

	switch (std::fegetround())
	{
	case FE_DOWNWARD:
		EXPECT_EQ(T( 0.0), hamon::rint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::rint(T( 2.5)));
		EXPECT_EQ(T(-3.0), hamon::rint(T(-2.5)));
		EXPECT_EQ(T( 3.0), hamon::rint(T( 3.5)));
		EXPECT_EQ(T(-4.0), hamon::rint(T(-3.5)));
		break;
	case FE_TONEAREST:
		EXPECT_EQ(T( 0.0), hamon::rint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::rint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::rint(T(-2.5)));
		EXPECT_EQ(T( 4.0), hamon::rint(T( 3.5)));
		EXPECT_EQ(T(-4.0), hamon::rint(T(-3.5)));
		break;
	case FE_TOWARDZERO:
		EXPECT_EQ(T( 0.0), hamon::rint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::rint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::rint(T(-2.5)));
		EXPECT_EQ(T( 3.0), hamon::rint(T( 3.5)));
		EXPECT_EQ(T(-3.0), hamon::rint(T(-3.5)));
		break;
	case FE_UPWARD:
		EXPECT_EQ(T( 0.0), hamon::rint(T( 0.0)));
		EXPECT_EQ(T( 3.0), hamon::rint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::rint(T(-2.5)));
		EXPECT_EQ(T( 4.0), hamon::rint(T( 3.5)));
		EXPECT_EQ(T(-3.0), hamon::rint(T(-3.5)));
		break;
	}

	EXPECT_EQ(+inf, hamon::rint(+inf));
	EXPECT_EQ(-inf, hamon::rint(-inf));
	EXPECT_TRUE(hamon::isnan(hamon::rint(nan)));
}

template <typename T>
void RIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, hamon::rint(T( 0)));
	EXPECT_EQ( 2.0, hamon::rint(T( 2)));
	EXPECT_EQ(-2.0, hamon::rint(T(-2)));
	EXPECT_EQ( 3.0, hamon::rint(T( 3)));
	EXPECT_EQ(-3.0, hamon::rint(T(-3)));
}

template <typename T>
void RIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, hamon::rint(T( 0)));
	EXPECT_EQ( 2.0, hamon::rint(T( 2)));
	EXPECT_EQ( 3.0, hamon::rint(T( 3)));
}

GTEST_TEST(CMathTest, RIntTest)
{
	RIntTestFloat<float>();
	RIntTestFloat<double>();
	RIntTestFloat<long double>();

	RIntTestSignedInt<int>();
//	RIntTestSignedInt<signed char>();
	RIntTestSignedInt<short>();
//	RIntTestSignedInt<long>();
	RIntTestSignedInt<long long>();

//	RIntTestUnsignedInt<unsigned int>();
	RIntTestUnsignedInt<unsigned char>();
//	RIntTestUnsignedInt<unsigned short>();
	RIntTestUnsignedInt<unsigned long>();
//	RIntTestUnsignedInt<unsigned long long>();
}

}	// namespace rint_test

}	// namespace hamon_cmath_test
