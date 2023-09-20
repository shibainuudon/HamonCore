/**
 *	@file	unit_test_cmath_is_even.cpp
 *
 *	@brief	is_even のテスト
 */

#include <hamon/cmath/is_even.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace is_even_test
{

static_assert(hamon::is_same<bool, decltype(hamon::is_even(0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_even(0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_even(0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_even(0   ))>::value, "");

template <typename T>
void IsEvenTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-4.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T(-4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-3.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-3.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-2.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-2.2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-2.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-1.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 1.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T( 2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 2.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 2.2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 2.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 3.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 3.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T( 4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 4.1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even( nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(-nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even( inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(-inf));
}

template <typename T>
void IsEvenTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T( 3)));
}

template <typename T>
void IsEvenTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_even(T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_even(T(4)));
}

GTEST_TEST(CMathTest, IsEvenTest)
{
	IsEvenTestFloat<float>();
	IsEvenTestFloat<double>();
	IsEvenTestFloat<long double>();

//	IsEvenTestSignedInt<int>();
	IsEvenTestSignedInt<signed char>();
//	IsEvenTestSignedInt<short>();
	IsEvenTestSignedInt<long>();
//	IsEvenTestSignedInt<long long>();

	IsEvenTestUnsignedInt<unsigned int>();
//	IsEvenTestUnsignedInt<unsigned char>();
	IsEvenTestUnsignedInt<unsigned short>();
//	IsEvenTestUnsignedInt<unsigned long>();
	IsEvenTestUnsignedInt<unsigned long long>();
}

}	// namespace is_even_test

}	// namespace hamon_cmath_test
