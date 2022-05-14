/**
 *	@file	unit_test_cmath_fabs.cpp
 *
 *	@brief	fabs のテスト
 */

#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace fabs_test
{

static_assert(std::is_same<float,       decltype(hamon::fabs(0.0f))>::value, "");
static_assert(std::is_same<float,       decltype(hamon::fabsf(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::fabs(0.0 ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::fabs(0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::fabs(0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::fabsl(0.0l))>::value, "");

template <typename T>
void FabsTestFloat(void)
{
	HAMON_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.0), hamon::fabs(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.0), hamon::fabs(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3.5), hamon::fabs(T( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3.5), hamon::fabs(T(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max), hamon::fabs(T( max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max), hamon::fabs(T(-max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(min), hamon::fabs(T( min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(min), hamon::fabs(T(-min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max), hamon::fabs(T( lowest)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max), hamon::fabs(T(-lowest)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(inf), hamon::fabs(T( inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(inf), hamon::fabs(T(-inf)));

	{
		HAMON_CONSTEXPR auto t = hamon::fabs(T(+0.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(t));
	}
	{
		HAMON_CONSTEXPR auto t = hamon::fabs(T(-0.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(t));
	}
	{
		HAMON_CONSTEXPR auto t = hamon::fabs(nan);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(t));
	}
	{
		HAMON_CONSTEXPR auto t = hamon::fabs(-nan);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(t));
	}
}

template <typename T>
void FabsTestSignedInt(void)
{
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(0),     hamon::fabs(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(1),     hamon::fabs(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(1),     hamon::fabs(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(3),     hamon::fabs(T( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(3),     hamon::fabs(T(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(max),   hamon::fabs(T( max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(max),   hamon::fabs(T(-max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(max)+1, hamon::fabs(T( min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(max)+1, hamon::fabs(T( lowest)));
}

template <typename T>
void FabsTestUnsignedInt(void)
{
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(0),      hamon::fabs(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(1),      hamon::fabs(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(3),      hamon::fabs(T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(max),    hamon::fabs(T(max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(min),    hamon::fabs(T(min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(double(lowest), hamon::fabs(T(lowest)));
}

GTEST_TEST(CMathTest, FAbsTest)
{
	FabsTestFloat<float>();
	FabsTestFloat<double>();
	FabsTestFloat<long double>();

	FabsTestSignedInt<int>();
	FabsTestSignedInt<signed char>();
//	FabsTestSignedInt<short>();
	FabsTestSignedInt<long>();
//	FabsTestSignedInt<long long>();

	FabsTestUnsignedInt<unsigned int>();
//	FabsTestUnsignedInt<unsigned char>();
	FabsTestUnsignedInt<unsigned short>();
//	FabsTestUnsignedInt<unsigned long>();
	FabsTestUnsignedInt<unsigned long long>();
}

}	// namespace fabs_test

}	// namespace hamon_cmath_test
