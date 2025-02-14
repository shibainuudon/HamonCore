/**
 *	@file	unit_test_cmath_llrint.cpp
 *
 *	@brief	llrint のテスト
 */

#include <hamon/cmath/llrint.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace llrint_test
{

static_assert(hamon::is_same<long long, decltype(hamon::llrint(0.0f))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llrintf(0.0f))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llrint(0.0 ))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llrint(0   ))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llrint(0.0l))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llrintl(0.0l))>::value, "");

template <typename T>
void LLRIntTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto inf   = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto nan   = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto llmax = hamon::numeric_limits<long long>::max();
	HAMON_CXX11_CONSTEXPR auto llmin = hamon::numeric_limits<long long>::min();

	switch (std::fegetround())
	{
	case FE_DOWNWARD:
		EXPECT_EQ(T( 0.0), hamon::llrint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::llrint(T( 2.5)));
		EXPECT_EQ(T(-3.0), hamon::llrint(T(-2.5)));
		EXPECT_EQ(T( 3.0), hamon::llrint(T( 3.5)));
		EXPECT_EQ(T(-4.0), hamon::llrint(T(-3.5)));
		break;
	case FE_TONEAREST:
		EXPECT_EQ(T( 0.0), hamon::llrint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::llrint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::llrint(T(-2.5)));
		EXPECT_EQ(T( 4.0), hamon::llrint(T( 3.5)));
		EXPECT_EQ(T(-4.0), hamon::llrint(T(-3.5)));
		break;
	case FE_TOWARDZERO:
		EXPECT_EQ(T( 0.0), hamon::llrint(T( 0.0)));
		EXPECT_EQ(T( 2.0), hamon::llrint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::llrint(T(-2.5)));
		EXPECT_EQ(T( 3.0), hamon::llrint(T( 3.5)));
		EXPECT_EQ(T(-3.0), hamon::llrint(T(-3.5)));
		break;
	case FE_UPWARD:

		EXPECT_EQ(T( 0.0), hamon::llrint(T( 0.0)));
		EXPECT_EQ(T( 3.0), hamon::llrint(T( 2.5)));
		EXPECT_EQ(T(-2.0), hamon::llrint(T(-2.5)));
		EXPECT_EQ(T( 4.0), hamon::llrint(T( 3.5)));
		EXPECT_EQ(T(-3.0), hamon::llrint(T(-3.5)));
		break;
	}
	EXPECT_EQ(llmax,  hamon::llrint(+inf));
	EXPECT_EQ(llmin,  hamon::llrint(-inf));
	EXPECT_EQ(T(0.0), hamon::llrint(nan));
}

template <typename T>
void LLRIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, hamon::llrint(T( 0)));
	EXPECT_EQ( 2.0, hamon::llrint(T( 2)));
	EXPECT_EQ(-2.0, hamon::llrint(T(-2)));
	EXPECT_EQ( 3.0, hamon::llrint(T( 3)));
	EXPECT_EQ(-3.0, hamon::llrint(T(-3)));
}

template <typename T>
void LLRIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, hamon::llrint(T( 0)));
	EXPECT_EQ( 2.0, hamon::llrint(T( 2)));
	EXPECT_EQ( 3.0, hamon::llrint(T( 3)));
}

GTEST_TEST(CMathTest, LLRIntTest)
{
	LLRIntTestFloat<float>();
	LLRIntTestFloat<double>();
	LLRIntTestFloat<long double>();

	LLRIntTestSignedInt<int>();
//	LLRIntTestSignedInt<signed char>();
	LLRIntTestSignedInt<short>();
//	LLRIntTestSignedInt<long>();
	LLRIntTestSignedInt<long long>();

//	LLRIntTestUnsignedInt<unsigned int>();
	LLRIntTestUnsignedInt<unsigned char>();
//	LLRIntTestUnsignedInt<unsigned short>();
	LLRIntTestUnsignedInt<unsigned long>();
//	LLRIntTestUnsignedInt<unsigned long long>();
}

}	// namespace llrint_test

}	// namespace hamon_cmath_test
