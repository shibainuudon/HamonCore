/**
 *	@file	unit_test_cmath_round.cpp
 *
 *	@brief	round のテスト
 */

#include <hamon/cmath/round.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace round_test
{

static_assert(hamon::is_same<float,       decltype(hamon::round(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::roundf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::round(0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::round(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::roundl(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::round(0   ))>::value, "");

template <typename T>
void RoundTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon() * 2;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-2.0,  hamon::round(T(-1.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-2.0,  hamon::round(T(-1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1.0,  hamon::round(T(-1.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1.0,  hamon::round(T(-0.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1.0,  hamon::round(T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.0,  hamon::round(T(-0.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.0,  hamon::round(T( 0.0) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.0,  hamon::round(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.0,  hamon::round(T( 0.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.0,  hamon::round(T( 0.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1.0,  hamon::round(T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1.0,  hamon::round(T( 0.5) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1.0,  hamon::round(T( 1.5) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 2.0,  hamon::round(T( 1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 2.0,  hamon::round(T( 1.5) + eps));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::round(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::round(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::round(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::round(T(-0.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::round(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::round(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::round(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::round(-inf)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::round(-nan)));
}

template <typename T>
void RoundTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   0, hamon::round((T)   0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   1, hamon::round((T)   1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -1, hamon::round((T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   3, hamon::round((T)   3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -3, hamon::round((T)  -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 100, hamon::round((T) 100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-100, hamon::round((T)-100));
}

template <typename T>
void RoundTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0, hamon::round((T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1, hamon::round((T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  3, hamon::round((T)  3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)100, hamon::round((T)100));
}

GTEST_TEST(CMathTest, RoundTest)
{
	RoundTestFloat<float>();
	RoundTestFloat<double>();
	RoundTestFloat<long double>();

//	RoundTestSignedInt<int>();
	RoundTestSignedInt<signed char>();
//	RoundTestSignedInt<short>();
	RoundTestSignedInt<long>();
//	RoundTestSignedInt<long long>();

	RoundTestUnsignedInt<unsigned int>();
//	RoundTestUnsignedInt<unsigned char>();
	RoundTestUnsignedInt<unsigned short>();
//	RoundTestUnsignedInt<unsigned long>();
	RoundTestUnsignedInt<unsigned long long>();
}

}	// namespace round_test

}	// namespace hamon_cmath_test
