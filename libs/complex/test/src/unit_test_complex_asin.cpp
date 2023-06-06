/**
 *	@file	unit_test_complex_asin.cpp
 *
 *	@brief	asin関数のテスト
 *
 *	template<class T> complex<T> asin(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/asin.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace asin_test
{

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 1e-6;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 1e-14;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-14;
}

template <typename T>
void test()
{
	static_assert(hamon::is_same<decltype(hamon::asin(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::asin(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 0.42707858639247609, (double)x.real(), error);
		EXPECT_NEAR( 1.5285709194809982,  (double)x.imag(), error);
	}
	{
		auto x = hamon::asin(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR(-1.0033627117332509, (double)x.real(), error);
		EXPECT_NEAR( 1.7501487613175148, (double)x.imag(), error);
	}
	{
		auto x = hamon::asin(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 1.0886482420610688, (double)x.real(), error);
		EXPECT_NEAR(-1.8902413596022003, (double)x.imag(), error);
	}
	{
		auto x = hamon::asin(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(-0.90225632477109885, (double)x.real(), error);
		EXPECT_NEAR(-2.4319527481396968,  (double)x.imag(), error);
	}
#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::asin(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.42707858639247609, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5285709194809982,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::asin(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0033627117332509, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7501487613175148, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::asin(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0886482420610688, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.8902413596022003, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::asin(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.90225632477109885, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.4319527481396968,  (double)x.imag(), error);
	}
#endif
}

GTEST_TEST(ComplexTest, AsinTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace asin_test

}	// namespace hamon_complex_test
