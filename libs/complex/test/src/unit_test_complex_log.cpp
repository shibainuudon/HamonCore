/**
 *	@file	unit_test_complex_log.cpp
 *
 *	@brief	log関数のテスト
 *
 *	template<class T> complex<T> log(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/log.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace log_test
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
	static_assert(hamon::is_same<decltype(hamon::log(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::log(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 0.80471895621705014, (double)x.real(), error);
		EXPECT_NEAR( 1.1071487177940904,  (double)x.imag(), error);
	}
	{
		auto x = hamon::log(hamon::complex<T>(1.5, -1.5));
		EXPECT_NEAR( 0.75203869838813697, (double)x.real(), error);
		EXPECT_NEAR(-0.78539816339744828, (double)x.imag(), error);
	}
	{
		auto x = hamon::log(hamon::complex<T>(-3.0, 1.5));
		EXPECT_NEAR(1.2101840643252146, (double)x.real(), error);
		EXPECT_NEAR(2.677945044588987,  (double)x.imag(), error);
	}
	{
		auto x = hamon::log(hamon::complex<T>(-1.5, -2.5));
		EXPECT_NEAR( 1.0700330817481354, (double)x.real(), error);
		EXPECT_NEAR(-2.1112158270654806, (double)x.imag(), error);
	}

	// log(conj(z)) == conj(log(z))
	{
		hamon::complex<T> z{1.5, 2.0};
		EXPECT_TRUE((complex_near(hamon::log(hamon::conj(z)), hamon::conj(hamon::log(z)), error)));
	}
	{
		hamon::complex<T> z{1.5, -2.0};
		EXPECT_TRUE((complex_near(hamon::log(hamon::conj(z)), hamon::conj(hamon::log(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE((complex_near(hamon::log(hamon::conj(z)), hamon::conj(hamon::log(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::log(hamon::conj(z)), hamon::conj(hamon::log(z)), error)));
	}
#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::log(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.80471895621705014, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1071487177940904,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::log(hamon::complex<T>(1.5, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.75203869838813697, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.78539816339744828, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::log(hamon::complex<T>(-3.0, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.2101840643252146, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.677945044588987,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::log(hamon::complex<T>(-1.5, -2.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0700330817481354, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.1112158270654806, (double)x.imag(), error);
	}

	// log(conj(z)) == conj(log(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, 2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::log(hamon::conj(z)), hamon::conj(hamon::log(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, -2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::log(hamon::conj(z)), hamon::conj(hamon::log(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::log(hamon::conj(z)), hamon::conj(hamon::log(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::log(hamon::conj(z)), hamon::conj(hamon::log(z)), error)));
	}

	HAMON_CXX11_CONSTEXPR T pi = hamon::numbers::pi_fn<T>();
	HAMON_CXX11_CONSTEXPR T nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = hamon::numeric_limits<T>::infinity();

	// If z is (-0,+0), the result is (-∞,π) and FE_DIVBYZERO is raised
	//HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(-inf, pi), hamon::log(hamon::complex<T>(-0.0, +0.0))));
	// ※HAMONでは-0と+0を区別しない
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(-inf, +0.0), hamon::log(hamon::complex<T>(-0.0, +0.0))));

	// If z is (+0,+0), the result is (-∞,+0) and FE_DIVBYZERO is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(-inf, +0.0), hamon::log(hamon::complex<T>(+0.0, +0.0))));

	// If z is (x,+∞) (for any finite x), the result is (+∞,π/2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 2), hamon::log(hamon::complex<T>(+1.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 2), hamon::log(hamon::complex<T>(-2.5, +inf))));

	// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::log(hamon::complex<T>(+1.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::log(hamon::complex<T>(-2.5, nan))));

	// If z is (-∞,y) (for any finite positive y), the result is (+∞,π)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi), hamon::log(hamon::complex<T>(-inf, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi), hamon::log(hamon::complex<T>(-inf, +2.5))));

	// If z is (+∞,y) (for any finite positive y), the result is (+∞,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::log(hamon::complex<T>(+inf, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::log(hamon::complex<T>(+inf, +2.5))));

	// If z is (-∞,+∞), the result is (+∞,3π/4)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi * 3 / 4), hamon::log(hamon::complex<T>(-inf, +inf))));

	// If z is (+∞,+∞), the result is (+∞,π/4)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 4), hamon::log(hamon::complex<T>(+inf, +inf))));

	// If z is (±∞,NaN), the result is (+∞,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::log(hamon::complex<T>(+inf, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::log(hamon::complex<T>(-inf, nan))));

	// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::log(hamon::complex<T>(nan, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::log(hamon::complex<T>(nan, -2.5))));
	
	// If z is (NaN,+∞), the result is (+∞,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::log(hamon::complex<T>(nan, +inf))));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::log(hamon::complex<T>(nan, nan))));
#endif
}

GTEST_TEST(ComplexTest, LogTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace log_test

}	// namespace hamon_complex_test
