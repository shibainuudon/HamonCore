/**
 *	@file	unit_test_complex_log10.cpp
 *
 *	@brief	log10関数のテスト
 *
 *	template<class T> complex<T> log10(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/log10.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace log10_test
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
	static_assert(hamon::is_same<decltype(hamon::log10(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::log10(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 0.34948500216800937, (double)x.real(), error);
		EXPECT_NEAR( 0.48082857878423407, (double)x.imag(), error);
	}
	{
		auto x = hamon::log10(hamon::complex<T>(1.0, -2.0));
		EXPECT_NEAR( 0.34948500216800937, (double)x.real(), error);
		EXPECT_NEAR(-0.48082857878423407, (double)x.imag(), error);
	}
	{
		auto x = hamon::log10(hamon::complex<T>(-3.0, 1.5));
		EXPECT_NEAR( 0.52557626122369061, (double)x.real(), error);
		EXPECT_NEAR( 1.1630167557051547,  (double)x.imag(), error);
	}
	{
		auto x = hamon::log10(hamon::complex<T>(-2.5, -1.5));
		EXPECT_NEAR( 0.46470946285714637, (double)x.real(), error);
		EXPECT_NEAR(-1.1296751469614137,  (double)x.imag(), error);
	}

	// std::log10(std::conj(z)) == std::conj(std::log10(z))
	{
		hamon::complex<T> z{1.5, 2.0};
		EXPECT_TRUE((complex_near(hamon::log10(hamon::conj(z)), hamon::conj(hamon::log10(z)), error)));
	}
	{
		hamon::complex<T> z{1.0, -2.5};
		EXPECT_TRUE((complex_near(hamon::log10(hamon::conj(z)), hamon::conj(hamon::log10(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE((complex_near(hamon::log10(hamon::conj(z)), hamon::conj(hamon::log10(z)), error)));
	}
	{
		hamon::complex<T> z{-2.0, -3.0};
		EXPECT_TRUE((complex_near(hamon::log10(hamon::conj(z)), hamon::conj(hamon::log10(z)), error)));
	}
#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::log10(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.34948500216800937, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.48082857878423407, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::log10(hamon::complex<T>(1.0, -2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.34948500216800937, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.48082857878423407, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::log10(hamon::complex<T>(-3.0, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.52557626122369061, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1630167557051547,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::log10(hamon::complex<T>(-2.5, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.46470946285714637, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.1296751469614137,  (double)x.imag(), error);
	}

	// std::log10(std::conj(z)) == std::conj(std::log10(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, 2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::log10(hamon::conj(z)), hamon::conj(hamon::log10(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::log10(hamon::conj(z)), hamon::conj(hamon::log10(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::log10(hamon::conj(z)), hamon::conj(hamon::log10(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.0, -3.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::log10(hamon::conj(z)), hamon::conj(hamon::log10(z)), error)));
	}
#endif
}

GTEST_TEST(ComplexTest, Log10Test)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace log10_test

}	// namespace hamon_complex_test
