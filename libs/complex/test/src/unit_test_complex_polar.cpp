/**
 *	@file	unit_test_complex_polar.cpp
 *
 *	@brief	polar関数のテスト
 *
 *	template<class T> complex<T> polar(const T& rho, const T& theta = T());
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/polar.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers/pi.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace polar_test
{

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 1e-5;
//	return 1e-6;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 1e-13;
//	return 1e-15;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-13;
//	return 1e-15;
}

template <typename T>
void test()
{
	static_assert(hamon::is_same<decltype(hamon::polar(T{}, T{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR T half_pi = hamon::numbers::pi_fn<T>() / 2;

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	// hamon::polar(1, 0°) == hamon::complex( 1,  0)
	{
		auto x = hamon::polar(T{1}, half_pi * 0);
		EXPECT_NEAR(1.0, (double)x.real(), error);
		EXPECT_NEAR(0.0, (double)x.imag(), error);
	}
	// hamon::polar(1, 90°) == hamon::complex( 0,  1)
	{
		auto x = hamon::polar(T{1}, half_pi * 1);
		EXPECT_NEAR( 0.0, (double)x.real(), error);
		EXPECT_NEAR( 1.0, (double)x.imag(), error);
	}
	// hamon::polar(1, 180°) == hamon::complex(-1,  0)
	{
		auto x = hamon::polar(T{1}, half_pi * 2);
		EXPECT_NEAR(-1.0, (double)x.real(), error);
		EXPECT_NEAR( 0.0, (double)x.imag(), error);
	}
	// hamon::polar(1, 270°) == hamon::complex( 0, -1)
	{
		auto x = hamon::polar(T{1}, half_pi * 3);
		EXPECT_NEAR( 0.0, (double)x.real(), error);
		EXPECT_NEAR(-1.0, (double)x.imag(), error);
	}

	// hamon::polar(2, 0°) == hamon::complex( 2,  0)
	{
		auto x = hamon::polar(T{2});
		EXPECT_NEAR(2.0, (double)x.real(), error);
		EXPECT_NEAR(0.0, (double)x.imag(), error);
	}
	// hamon::polar(3, 90°) == hamon::complex( 0,  3)
	{
		auto x = hamon::polar(T{3}, half_pi * 1);
		EXPECT_NEAR( 0.0, (double)x.real(), error);
		EXPECT_NEAR( 3.0, (double)x.imag(), error);
	}
	// hamon::polar(4, 180°) == hamon::complex(-4,  0)
	{
		auto x = hamon::polar(T{4}, half_pi * 2);
		EXPECT_NEAR(-4.0, (double)x.real(), error);
		EXPECT_NEAR( 0.0, (double)x.imag(), error);
	}
	// hamon::polar(5, 270°) == hamon::complex( 0, -5)
	{
		auto x = hamon::polar(T{5}, half_pi * 3);
		EXPECT_NEAR( 0.0, (double)x.real(), error);
		EXPECT_NEAR(-5.0, (double)x.imag(), error);
	}
#else
	// hamon::polar(1, 0°) == hamon::complex( 1,  0)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::polar(T{1}, half_pi * 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0, (double)x.imag(), error);
	}
	// hamon::polar(1, 90°) == hamon::complex( 0,  1)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::polar(T{1}, half_pi * 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, (double)x.imag(), error);
	}
	// hamon::polar(1, 180°) == hamon::complex(-1,  0)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::polar(T{1}, half_pi * 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)x.imag(), error);
	}
	// hamon::polar(1, 270°) == hamon::complex( 0, -1)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::polar(T{1}, half_pi * 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0, (double)x.imag(), error);
	}

	// hamon::polar(2, 0°) == hamon::complex( 2,  0)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::polar(T{2});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0, (double)x.imag(), error);
	}
	// hamon::polar(3, 90°) == hamon::complex( 0,  3)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::polar(T{3}, half_pi * 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0, (double)x.imag(), error);
	}
	// hamon::polar(4, 180°) == hamon::complex(-4,  0)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::polar(T{4}, half_pi * 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-4.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)x.imag(), error);
	}
	// hamon::polar(5, 270°) == hamon::complex( 0, -5)
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::polar(T{5}, half_pi * 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-5.0, (double)x.imag(), error);
	}
#endif
}

GTEST_TEST(ComplexTest, PolarTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace polar_test

}	// namespace hamon_complex_test
