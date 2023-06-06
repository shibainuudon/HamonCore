/**
 *	@file	unit_test_complex_sub.cpp
 *
 *	@brief	減算演算子のテスト
 *
 *	template <typename T> constexpr complex<T> operator-(complex<T> const&, complex<T> const&);
 *	template <typename T> constexpr complex<T> operator-(complex<T> const&, T const&);
 *	template <typename T> constexpr complex<T> operator-(T const&, complex<T> const&);
 */

#include <hamon/complex/complex.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace sub_test
{

template <typename T>
void test()
{
	// complex - complex
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{1.5,  2.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{2.0, -1.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> c = lhs - rhs;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0, c.imag());
	}

	// complex - scalar
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{1.5,  2.5};
		HAMON_CXX11_CONSTEXPR T rhs{3};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> c = lhs - rhs;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.5, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.5, c.imag());
	}

	// scalar - complex
	{
		HAMON_CXX11_CONSTEXPR T lhs{-2.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{2.0, -1.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> c = lhs - rhs;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4.5, c.real());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.5, c.imag());
	}
}

GTEST_TEST(ComplexTest, SubTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace sub_test

}	// namespace hamon_complex_test
