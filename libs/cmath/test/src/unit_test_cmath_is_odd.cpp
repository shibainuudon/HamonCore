/**
 *	@file	unit_test_cmath_is_odd.cpp
 *
 *	@brief	is_odd のテスト
 */

#include <hamon/cmath/is_odd.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace is_odd_test
{

static_assert(std::is_same<bool, decltype(hamon::is_odd(0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::is_odd(0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::is_odd(0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::is_odd(0   ))>::value, "");

template <typename T>
void IsOddTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-4.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-3.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-3.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-2.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-2.2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-2.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-1.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 1.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 2.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 2.2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 2.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 3.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 3.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 4.1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd( nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(-nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd( inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(-inf));
}

template <typename T>
void IsOddTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T( 3)));
}

template <typename T>
void IsOddTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_odd(T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_odd(T(4)));
}

GTEST_TEST(CMathTest, IsOddTest)
{
	IsOddTestFloat<float>();
	IsOddTestFloat<double>();
	IsOddTestFloat<long double>();

	IsOddTestSignedInt<int>();
//	IsOddTestSignedInt<signed char>();
	IsOddTestSignedInt<short>();
//	IsOddTestSignedInt<long>();
	IsOddTestSignedInt<long long>();

//	IsOddTestUnsignedInt<unsigned int>();
	IsOddTestUnsignedInt<unsigned char>();
//	IsOddTestUnsignedInt<unsigned short>();
	IsOddTestUnsignedInt<unsigned long>();
//	IsOddTestUnsignedInt<unsigned long long>();
}

}	// namespace is_odd_test

}	// namespace hamon_cmath_test
