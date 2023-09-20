/**
 *	@file	unit_test_cmath_llround.cpp
 *
 *	@brief	llround のテスト
 */

#include <hamon/cmath/llround.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace llround_test
{

static_assert(hamon::is_same<long long, decltype(hamon::llround(0.0f))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llroundf(0.0f))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llround(0.0 ))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llround(0.0l))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llroundl(0.0l))>::value, "");
static_assert(hamon::is_same<long long, decltype(hamon::llround(0   ))>::value, "");

template <typename T>
void LLRoundTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon() * 2;

	HAMON_CXX11_CONSTEXPR auto llmin = hamon::numeric_limits<long long>::lowest();
	HAMON_CXX11_CONSTEXPR auto llmax = hamon::numeric_limits<long long>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2L,  hamon::llround(T(-1.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2L,  hamon::llround(T(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1L,  hamon::llround(T(-1.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1L,  hamon::llround(T(-0.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1L,  hamon::llround(T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::llround(T(-0.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::llround(T( 0.0) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::llround(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::llround(T( 0.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::llround(T( 0.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1L,  hamon::llround(T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1L,  hamon::llround(T( 0.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1L,  hamon::llround(T( 1.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2L,  hamon::llround(T( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2L,  hamon::llround(T( 1.5) + eps));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(llmin, hamon::llround(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(llmax, hamon::llround(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(llmin, hamon::llround(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(llmax, hamon::llround(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(llmin, hamon::llround(nan));
}

template <typename T>
void LLRoundTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   0L, hamon::llround((T)   0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   1L, hamon::llround((T)   1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  -1L, hamon::llround((T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   3L, hamon::llround((T)   3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  -3L, hamon::llround((T)  -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 100L, hamon::llround((T) 100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-100L, hamon::llround((T)-100));
}

template <typename T>
void LLRoundTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0L, hamon::llround((T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1L, hamon::llround((T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  3L, hamon::llround((T)  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(100L, hamon::llround((T)100));
}

GTEST_TEST(CMathTest, LLRoundTest)
{
	LLRoundTestFloat<float>();
	LLRoundTestFloat<double>();
	LLRoundTestFloat<long double>();

//	LLRoundTestSignedInt<int>();
	LLRoundTestSignedInt<signed char>();
//	LLRoundTestSignedInt<short>();
	LLRoundTestSignedInt<long>();
//	LLRoundTestSignedInt<long long>();

	LLRoundTestUnsignedInt<unsigned int>();
//	LLRoundTestUnsignedInt<unsigned char>();
	LLRoundTestUnsignedInt<unsigned short>();
//	LLRoundTestUnsignedInt<unsigned long>();
	LLRoundTestUnsignedInt<unsigned long long>();
}

}	// namespace llround_test

}	// namespace hamon_cmath_test
