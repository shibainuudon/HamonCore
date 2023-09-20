/**
 *	@file	unit_test_cmath_round_half_even.cpp
 *
 *	@brief	round_half_even のテスト
 */

#include <hamon/cmath/round_half_even.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace round_half_even_test
{

static_assert(hamon::is_same<float,       decltype(hamon::round_half_even(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::round_half_even(0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::round_half_even(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::round_half_even(0   ))>::value, "");

template <typename T>
void RoundHalfEvenTestUnsigned(void)
{
	using hamon::round_half_even;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0, round_half_even((T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1, round_half_even((T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)100, round_half_even((T)100));
}

template <typename T>
void RoundHalfEvenTestSigned(void)
{
	using hamon::round_half_even;

	RoundHalfEvenTestUnsigned<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -1, round_half_even((T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -3, round_half_even((T)  -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-100, round_half_even((T)-100));
}

template <typename T>
void RoundHalfEvenTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	using hamon::round_half_even;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), round_half_even(T( 0.0000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), round_half_even(T( 0.4999)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), round_half_even(T( 0.5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), round_half_even(T( 0.5001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), round_half_even(T( 1.0000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), round_half_even(T( 1.4999)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 1.5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 1.5001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 2.0000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 2.4999)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 2.0), round_half_even(T( 2.5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 3.0), round_half_even(T( 2.5001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0.0), round_half_even(T(-0.4999)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-0.0), round_half_even(T(-0.5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), round_half_even(T(-0.5001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), round_half_even(T(-1.0000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), round_half_even(T(-1.4999)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-1.5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-1.5001)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-2.0000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-2.4999)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-2.0), round_half_even(T(-2.5000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-3.0), round_half_even(T(-2.5001)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (round_half_even(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (round_half_even(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(round_half_even(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(round_half_even(-inf)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(round_half_even(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(round_half_even(-nan)));
}

GTEST_TEST(CMathTest, RoundHalfEvenTest)
{
//	RoundHalfEvenTestUnsigned<unsigned char>();
	RoundHalfEvenTestUnsigned<unsigned short>();
//	RoundHalfEvenTestUnsigned<unsigned int>();
	RoundHalfEvenTestUnsigned<unsigned long>();
//	RoundHalfEvenTestUnsigned<unsigned long long>();

	RoundHalfEvenTestSigned<signed char>();
//	RoundHalfEvenTestSigned<signed short>();
	RoundHalfEvenTestSigned<signed int>();
//	RoundHalfEvenTestSigned<signed long>();
	RoundHalfEvenTestSigned<signed long long>();

	RoundHalfEvenTestFloat<float>();
	RoundHalfEvenTestFloat<double>();
	RoundHalfEvenTestFloat<long double>();
}

}	// namespace round_half_even_test

}	// namespace hamon_cmath_test
