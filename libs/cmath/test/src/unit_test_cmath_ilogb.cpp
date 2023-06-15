/**
 *	@file	unit_test_cmath_ilogb.cpp
 *
 *	@brief	ilogb のテスト
 */

#include <hamon/cmath/ilogb.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ilogb_test
{

static_assert(hamon::is_same<int, decltype(hamon::ilogb(0.0f))>::value, "");
static_assert(hamon::is_same<int, decltype(hamon::ilogbf(0.0f))>::value, "");
static_assert(hamon::is_same<int, decltype(hamon::ilogb(0.0 ))>::value, "");
static_assert(hamon::is_same<int, decltype(hamon::ilogb(0   ))>::value, "");
static_assert(hamon::is_same<int, decltype(hamon::ilogb(0.0l))>::value, "");
static_assert(hamon::is_same<int, decltype(hamon::ilogbl(0.0l))>::value, "");

template <typename T>
void ILogbTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T(-17.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T(-16.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T(-15.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T( -9.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T( -8.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T( -7.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T( -5.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T( -4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T( -3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T( -2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::ilogb(T( -1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::ilogb(T( -0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, hamon::ilogb(T( -0.25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::ilogb(T( -0.125)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, hamon::ilogb(T(  0.125)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, hamon::ilogb(T(  0.25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1, hamon::ilogb(T(  0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::ilogb(T(  1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::ilogb(T(  1.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T(  2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T(  2.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T(  3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T(  3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  4.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  5.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  7.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T(  8.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T(  9.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T( 15.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T( 16.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T( 17.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ILOGB0,   hamon::ilogb(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ILOGB0,   hamon::ilogb(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(INT_MAX,     hamon::ilogb(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(INT_MAX,     hamon::ilogb(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ILOGBNAN, hamon::ilogb(+nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ILOGBNAN, hamon::ilogb(-nan));
}

template <typename T>
void ILogbTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T(-17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T(-16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T(-15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T( -9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T( -8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T( -7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T( -5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T( -4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T( -3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T( -2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::ilogb(T( -1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::ilogb(T(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T(  3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T(  8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T(  9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T( 15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T( 16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T( 17)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ILOGB0, hamon::ilogb(T(0)));
}

template <typename T>
void ILogbTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::ilogb(T(  1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T(  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::ilogb(T(  3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, hamon::ilogb(T(  7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T(  8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T(  9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, hamon::ilogb(T( 15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T( 16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::ilogb(T( 17)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(FP_ILOGB0, hamon::ilogb(T(0)));
}

GTEST_TEST(CMathTest, ILogbTest)
{
	ILogbTestFloat<float>();
	ILogbTestFloat<double>();
	ILogbTestFloat<long double>();

	ILogbTestSignedInt<int>();
//	ILogbTestSignedInt<signed char>();
	ILogbTestSignedInt<short>();
//	ILogbTestSignedInt<long>();
	ILogbTestSignedInt<long long>();

//	ILogbTestUnsignedInt<unsigned int>();
	ILogbTestUnsignedInt<unsigned char>();
//	ILogbTestUnsignedInt<unsigned short>();
	ILogbTestUnsignedInt<unsigned long>();
//	ILogbTestUnsignedInt<unsigned long long>();
}

}	// namespace ilogb_test

}	// namespace hamon_cmath_test
