/**
 *	@file	unit_test_cmath_abs.cpp
 *
 *	@brief	abs のテスト
 */

#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace abs_test
{

static_assert(hamon::is_same<float,        decltype(hamon::abs(0.0f))>::value, "");
static_assert(hamon::is_same<double,       decltype(hamon::abs(0.0 ))>::value, "");
static_assert(hamon::is_same<long double,  decltype(hamon::abs(0.0l))>::value, "");
static_assert(hamon::is_same<signed   char,      decltype(hamon::abs((signed   char)0))>::value, "");
static_assert(hamon::is_same<unsigned char,      decltype(hamon::abs((unsigned char)0))>::value, "");
static_assert(hamon::is_same<signed   short,     decltype(hamon::abs((signed   short)0))>::value, "");
static_assert(hamon::is_same<unsigned short,     decltype(hamon::abs((unsigned short)0))>::value, "");
static_assert(hamon::is_same<signed   int,       decltype(hamon::abs((signed   int)0))>::value, "");
static_assert(hamon::is_same<unsigned int,       decltype(hamon::abs((unsigned int)0))>::value, "");
static_assert(hamon::is_same<signed   long,      decltype(hamon::abs((signed   long)0))>::value, "");
static_assert(hamon::is_same<unsigned long,      decltype(hamon::abs((unsigned long)0))>::value, "");
static_assert(hamon::is_same<signed   long long, decltype(hamon::abs((signed   long long)0))>::value, "");
static_assert(hamon::is_same<unsigned long long, decltype(hamon::abs((unsigned long long)0))>::value, "");

template <typename T>
void AbsTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.0), hamon::abs(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1.0), hamon::abs(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3.5), hamon::abs(T( 3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3.5), hamon::abs(T(-3.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max), hamon::abs(T( max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max), hamon::abs(T(-max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(min), hamon::abs(T( min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(min), hamon::abs(T(-min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max), hamon::abs(T( lowest)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max), hamon::abs(T(-lowest)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(inf), hamon::abs(T( inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(inf), hamon::abs(T(-inf)));

	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::abs(T(+0.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(t));
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::abs(T(-0.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::iszero(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(t));
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::abs(nan);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(t));
	}
	{
		HAMON_CXX11_CONSTEXPR auto t = hamon::abs(-nan);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(t));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(t));
	}
}

template <typename T>
void AbsTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0),   hamon::abs(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1),   hamon::abs(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1),   hamon::abs(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3),   hamon::abs(T( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3),   hamon::abs(T(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max,    hamon::abs(T( max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(max,    hamon::abs(T(-max)));
}

template <typename T>
void AbsTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0),      hamon::abs(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1),      hamon::abs(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3),      hamon::abs(T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(max),    hamon::abs(T(max)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(min),    hamon::abs(T(min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(lowest), hamon::abs(T(lowest)));
}

GTEST_TEST(CMathTest, AbsTest)
{
	AbsTestFloat<float>();
	AbsTestFloat<double>();
	AbsTestFloat<long double>();

	AbsTestSignedInt<int>();
//	AbsTestSignedInt<signed char>();
	AbsTestSignedInt<short>();
//	AbsTestSignedInt<long>();
	AbsTestSignedInt<long long>();

	AbsTestUnsignedInt<unsigned int>();
	AbsTestUnsignedInt<unsigned char>();
//	AbsTestUnsignedInt<unsigned short>();
	AbsTestUnsignedInt<unsigned long>();
//	AbsTestUnsignedInt<unsigned long long>();
}

}	// namespace abs_test

}	// namespace hamon_cmath_test
