/**
 *	@file	unit_test_complex_real_imag.cpp
 *
 *	@brief	real関数とimag関数のテスト
 *
 *	constexpr T real() const;
 *	constexpr void real(T val);
 *	constexpr T imag() const;
 *	constexpr void imag(T val);
 *
 *	template<class T> constexpr T real(const complex<T>& x);
 *	template<class FloatingPoint> constexpr FloatingPoint real(FloatingPoint f);
 *	template<class Integer> constexpr double real(Integer f);
 * 
 *	template<class T> constexpr T imag(const complex<T>& x);
 *	template<class FloatingPoint> constexpr FloatingPoint imag(FloatingPoint f);
 *	template<class Integer> constexpr double imag(Integer f);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/real.hpp>
#include <hamon/complex/imag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace real_imag_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool memfun_test()
{
	hamon::complex<T> c{1.5, 2.5};
	static_assert(hamon::is_same<decltype(c.real()), T>::value, "");
	static_assert(hamon::is_same<decltype(c.imag()), T>::value, "");
	static_assert(hamon::is_same<decltype(c.real(hamon::declval<T>())), void>::value, "");
	static_assert(hamon::is_same<decltype(c.imag(hamon::declval<T>())), void>::value, "");
	VERIFY(c.real() ==  1.5);
	VERIFY(c.imag() ==  2.5);
	c.real(-3);
	VERIFY(c.real() == -3.0);
	VERIFY(c.imag() ==  2.5);
	c.imag(4.5);
	VERIFY(c.real() == -3.0);
	VERIFY(c.imag() ==  4.5);
	return true;
}

#undef VERIFY

template <typename T>
void test()
{
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> c{1.5, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5, hamon::real(c));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5, hamon::imag(c));
		static_assert(hamon::is_same<decltype(hamon::real(c)), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::imag(c)), T>::value, "");
	}
	{
		HAMON_CXX11_CONSTEXPR T f{3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3.5, hamon::real(f));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::imag(f));
		static_assert(hamon::is_same<decltype(hamon::real(f)), T>::value, "");
		static_assert(hamon::is_same<decltype(hamon::imag(f)), T>::value, "");
	}
	{
		HAMON_CXX11_CONSTEXPR int i = 4;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.0, hamon::real(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::imag(i));
		static_assert(hamon::is_same<decltype(hamon::real(i)), double>::value, "");
		static_assert(hamon::is_same<decltype(hamon::imag(i)), double>::value, "");
	}
}

GTEST_TEST(ComplexTest, RealImagTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((memfun_test<float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((memfun_test<double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((memfun_test<long double>()));

	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace real_imag_test

}	// namespace hamon_complex_test
