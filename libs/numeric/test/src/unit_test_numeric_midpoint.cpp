/**
 *	@file	unit_test_numeric_midpoint.cpp
 *
 *	@brief	midpoint のテスト
 */

#include <hamon/numeric/midpoint.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4307)	// 整数定数がオーバーフローしました。
HAMON_WARNING_DISABLE_MSVC(4308)	// 負の整数定数が符号なしの型に変換されました。

namespace hamon_numeric_test
{

namespace midpoint_test
{

template <typename T>
void test_floating()
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 2.0), T( 4.0)) == T( 3.0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 0.0), T( 0.4)) == T( 0.2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 0.0), T(-0.0)) == T( 0.0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(-1.0), T(-2.0)) == T(-1.5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 9e9), T(-9e9)) == T( 0.0));

	HAMON_CXX11_CONSTEXPR T min = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR T max = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(min, min) == min);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(max, min) == max/2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(min, max) == max/2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(max, max) == max);
}

template <typename T>
void test_signed_integral()
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 0), T( 0)) == T( 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 1), T( 1)) == T( 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 0), T( 1)) == T( 0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 1), T( 0)) == T( 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 0), T( 2)) == T( 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 3), T( 2)) == T( 3));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(-5), T( 4)) == T(-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T( 5), T(-4)) == T( 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(-5), T(-4)) == T(-5));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(-4), T(-5)) == T(-4));

	HAMON_CXX11_CONSTEXPR T min = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR T max = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(min),   T(max))   == T(-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max),   T(min))   == T(0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max),   T(max))   == T(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max),   T(max-1)) == T(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max-1), T(max-1)) == T(max-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max-1), T(max))   == T(max-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max),   T(max-2)) == T(max-1));
}

template <typename T>
void test_unsigned_integral()
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(0), T(0)) == T(0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(0), T(1)) == T(0));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(1), T(0)) == T(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(0), T(2)) == T(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(3), T(2)) == T(3));

	HAMON_CXX11_CONSTEXPR T max = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(0),     T(max))   == T(max/2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max),   T(0))     == T(max/2 + 1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max),   T(max))   == T(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max),   T(max-1)) == T(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max-1), T(max-1)) == T(max-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max-1), T(max))   == T(max-1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(T(max),   T(max-2)) == T(max-1));
}

template <typename T>
void test_pointer()
{
	HAMON_CXX11_CONSTEXPR T a[4]{};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a, a)   == a);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a, a+1) == a);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a, a+2) == a+1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a, a+3) == a+1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a, a+4) == a+2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a+1, a) == a+1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a+2, a) == a+1);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a+3, a) == a+2);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::midpoint(a+4, a) == a+2);
}

GTEST_TEST(NumericTest, MidpointTest)
{
	test_floating<float>();
	test_floating<double>();
	test_floating<long double>();

	test_signed_integral<signed char>();
	test_signed_integral<signed short>();
	test_signed_integral<signed int>();
	test_signed_integral<signed long>();
	test_signed_integral<signed long long>();

	test_unsigned_integral<unsigned char>();
	test_unsigned_integral<unsigned short>();
	test_unsigned_integral<unsigned int>();
	test_unsigned_integral<unsigned long>();
	test_unsigned_integral<unsigned long long>();

	test_pointer<float>();
	test_pointer<double>();
	test_pointer<char>();
	test_pointer<short>();
	test_pointer<int>();
}

}	// namespace midpoint_test

}	// namespace hamon_numeric_test

HAMON_WARNING_POP()
