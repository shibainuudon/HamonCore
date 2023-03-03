/**
 *	@file	unit_test_cmath_is_integer.cpp
 *
 *	@brief	is_integer のテスト
 */

#include <hamon/cmath/is_integer.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace is_integer_test
{

static_assert(hamon::is_same<bool, decltype(hamon::is_integer(0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_integer(0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_integer(0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_integer(0   ))>::value, "");

template <typename T>
void IsIntegerTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-4.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T(-4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-3.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-3.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T(-3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-2.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-2.2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-2.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T(-2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-1.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(-0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 0.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 0.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 1.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 1.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T( 2.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 2.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 2.2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 2.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T( 3.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 3.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 3.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T( 4.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 4.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 9.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(10.1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T( 99.9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_integer(T(100.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(T(100.1)));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer( nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(-nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer( inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_integer(-inf));
}

template <typename T>
void IsIntegerTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(-100)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(-3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T( 3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T( 100)));
}

template <typename T>
void IsIntegerTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_integer(T(100)));
}

GTEST_TEST(CMathTest, IsIntegerTest)
{
	IsIntegerTestFloat<float>();
	IsIntegerTestFloat<double>();
	IsIntegerTestFloat<long double>();

	IsIntegerTestSignedInt<int>();
//	IsIntegerTestSignedInt<signed char>();
	IsIntegerTestSignedInt<short>();
//	IsIntegerTestSignedInt<long>();
	IsIntegerTestSignedInt<long long>();

//	IsIntegerTestUnsignedInt<unsigned int>();
	IsIntegerTestUnsignedInt<unsigned char>();
//	IsIntegerTestUnsignedInt<unsigned short>();
	IsIntegerTestUnsignedInt<unsigned long>();
//	IsIntegerTestUnsignedInt<unsigned long long>();
}

}	// namespace is_integer_test

}	// namespace hamon_cmath_test
