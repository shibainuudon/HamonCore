/**
 *	@file	unit_test_complex_ctor_complex.cpp
 *
 *	@brief	complexからのコンストラクタのテスト
 *
 *	template<class X> constexpr explicit(see below) complex(const complex<X>& other);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

static_assert( hamon::is_constructible<hamon::complex<float>, hamon::complex<float>>::value, "");
static_assert( hamon::is_constructible<hamon::complex<float>, hamon::complex<double>>::value, "");
static_assert( hamon::is_constructible<hamon::complex<float>, hamon::complex<long double>>::value, "");
static_assert( hamon::is_constructible<hamon::complex<double>, hamon::complex<float>>::value, "");
static_assert( hamon::is_constructible<hamon::complex<double>, hamon::complex<double>>::value, "");
static_assert( hamon::is_constructible<hamon::complex<double>, hamon::complex<long double>>::value, "");
static_assert( hamon::is_constructible<hamon::complex<long double>, hamon::complex<float>>::value, "");
static_assert( hamon::is_constructible<hamon::complex<long double>, hamon::complex<double>>::value, "");
static_assert( hamon::is_constructible<hamon::complex<long double>, hamon::complex<long double>>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::complex<float>, hamon::complex<float>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::complex<float>, hamon::complex<double>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::complex<float>, hamon::complex<long double>>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::complex<double>, hamon::complex<float>>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::complex<double>, hamon::complex<double>>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::complex<double>, hamon::complex<long double>>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::complex<long double>, hamon::complex<float>>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::complex<long double>, hamon::complex<double>>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::complex<long double>, hamon::complex<long double>>::value, "");

GTEST_TEST(ComplexTest, CtorComplexTest)
{
	// float -> float
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
	// float -> double
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
	// float -> long double
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
	// double -> float
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
	// double -> double
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
	// double -> long double
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
	// long double -> float
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<float> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
	// long double -> double
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<double> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
	// long double -> long double
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c1{1.5f, 2.5f};
		HAMON_CXX11_CONSTEXPR hamon::complex<long double> c2{c1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5f, c2.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, c2.imag());
	}
}
