/**
 *	@file	unit_test_cmath_lround.cpp
 *
 *	@brief	lround のテスト
 */

#include <hamon/cmath/lround.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace lround_test
{

static_assert(hamon::is_same<long, decltype(hamon::lround(0.0f))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lroundf(0.0f))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lround(0.0 ))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lround(0.0l))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lroundl(0.0l))>::value, "");
static_assert(hamon::is_same<long, decltype(hamon::lround(0   ))>::value, "");

template <typename T>
void LRoundTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto max = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon() * 2;

	HAMON_CXX11_CONSTEXPR auto lmin = std::numeric_limits<long>::lowest();
	HAMON_CXX11_CONSTEXPR auto lmax = std::numeric_limits<long>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2L,  hamon::lround(T(-1.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2L,  hamon::lround(T(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1L,  hamon::lround(T(-1.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1L,  hamon::lround(T(-0.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1L,  hamon::lround(T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::lround(T(-0.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::lround(T( 0.0) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::lround(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::lround(T( 0.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0L,  hamon::lround(T( 0.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1L,  hamon::lround(T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1L,  hamon::lround(T( 0.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1L,  hamon::lround(T( 1.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2L,  hamon::lround(T( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2L,  hamon::lround(T( 1.5) + eps));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(lmin, hamon::lround(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(lmax, hamon::lround(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(lmin, hamon::lround(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(lmax, hamon::lround(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(lmin, hamon::lround(nan));
}

template <typename T>
void LRoundTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   0L, hamon::lround((T)   0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   1L, hamon::lround((T)   1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  -1L, hamon::lround((T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   3L, hamon::lround((T)   3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  -3L, hamon::lround((T)  -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 100L, hamon::lround((T) 100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-100L, hamon::lround((T)-100));
}

template <typename T>
void LRoundTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0L, hamon::lround((T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1L, hamon::lround((T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  3L, hamon::lround((T)  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(100L, hamon::lround((T)100));
}

GTEST_TEST(CMathTest, LRoundTest)
{
	LRoundTestFloat<float>();
	LRoundTestFloat<double>();
	LRoundTestFloat<long double>();

//	LRoundTestSignedInt<int>();
	LRoundTestSignedInt<signed char>();
//	LRoundTestSignedInt<short>();
	LRoundTestSignedInt<long>();
//	LRoundTestSignedInt<long long>();

	LRoundTestUnsignedInt<unsigned int>();
//	LRoundTestUnsignedInt<unsigned char>();
	LRoundTestUnsignedInt<unsigned short>();
//	LRoundTestUnsignedInt<unsigned long>();
	LRoundTestUnsignedInt<unsigned long long>();
}

}	// namespace lround_test

}	// namespace hamon_cmath_test
