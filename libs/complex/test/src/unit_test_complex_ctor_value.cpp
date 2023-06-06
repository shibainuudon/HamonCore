/**
 *	@file	unit_test_complex_ctor_value.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	constexpr complex(T const& re = T(), T const& im = T());
 */

#include <hamon/complex/complex.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(ComplexTest, CtorValueTest)
{
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.imag());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c{1.5f};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.imag());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c{-2.5f, 3.5f};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.5f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.5f, c.imag());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.imag());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c{1.5f};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.imag());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c{-2.5f, 3.5f};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.5f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.5f, c.imag());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.imag());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c{1.5f};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, c.imag());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c{-2.5f, 3.5f};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.5f, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.5f, c.imag());
	}
}
