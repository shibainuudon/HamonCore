/**
 *	@file	unit_test_complex_sqrt.cpp
 *
 *	@brief	sqrt関数のテスト
 *
 *	template<class T> complex<T> sqrt(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/sqrt.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace sqrt_test
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
	static_assert(hamon::is_same<decltype(hamon::sqrt(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::sqrt(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 1.272019649514069,   (double)x.real(), error);
		EXPECT_NEAR( 0.78615137775742328, (double)x.imag(), error);
	}
	{
		auto x = hamon::sqrt(hamon::complex<T>(1.0, -2.0));
		EXPECT_NEAR( 1.272019649514069,   (double)x.real(), error);
		EXPECT_NEAR(-0.78615137775742328, (double)x.imag(), error);
	}
	{
		auto x = hamon::sqrt(hamon::complex<T>(-3.0, 1.5));
		EXPECT_NEAR( 0.42077426623409642, (double)x.real(), error);
		EXPECT_NEAR( 1.7824283949502271,  (double)x.imag(), error);
	}
	{
		auto x = hamon::sqrt(hamon::complex<T>(-2.0, -1.0));
		EXPECT_NEAR( 0.34356074972251244, (double)x.real(), error);
		EXPECT_NEAR(-1.4553466902253549,  (double)x.imag(), error);
	}

	// std::sqrt(std::conj(z)) == std::conj(std::sqrt(z))
	{
		hamon::complex<T> z{1.0, 2.0};
		EXPECT_TRUE(complex_near(hamon::sqrt(hamon::conj(z)), hamon::conj(hamon::sqrt(z)), error));
	}
	{
		hamon::complex<T> z{1.0, -2.0};
		EXPECT_TRUE(complex_near(hamon::sqrt(hamon::conj(z)), hamon::conj(hamon::sqrt(z)), error));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE(complex_near(hamon::sqrt(hamon::conj(z)), hamon::conj(hamon::sqrt(z)), error));
	}
	{
		hamon::complex<T> z{-2.5, -4.5};
		EXPECT_TRUE(complex_near(hamon::sqrt(hamon::conj(z)), hamon::conj(hamon::sqrt(z)), error));
	}
#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sqrt(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.272019649514069,   (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.78615137775742328, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sqrt(hamon::complex<T>(1.0, -2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.272019649514069,   (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.78615137775742328, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sqrt(hamon::complex<T>(-3.0, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.42077426623409642, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7824283949502271,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sqrt(hamon::complex<T>(-2.0, -1.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.34356074972251244, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4553466902253549,  (double)x.imag(), error);
	}

	// std::sqrt(std::conj(z)) == std::conj(std::sqrt(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_near(hamon::sqrt(hamon::conj(z)), hamon::conj(hamon::sqrt(z)), error));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, -2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_near(hamon::sqrt(hamon::conj(z)), hamon::conj(hamon::sqrt(z)), error));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_near(hamon::sqrt(hamon::conj(z)), hamon::conj(hamon::sqrt(z)), error));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_near(hamon::sqrt(hamon::conj(z)), hamon::conj(hamon::sqrt(z)), error));
	}

	HAMON_CXX11_CONSTEXPR T nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = std::numeric_limits<T>::infinity();

	// If z is (±0,+0), the result is (+0,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, +0.0), hamon::sqrt(hamon::complex<T>(+0.0, +0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, +0.0), hamon::sqrt(hamon::complex<T>(-0.0, +0.0))));

	// If z is (x,+∞), the result is (+∞,+∞) even if x is NaN
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +inf), hamon::sqrt(hamon::complex<T>(+0.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +inf), hamon::sqrt(hamon::complex<T>(-0.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +inf), hamon::sqrt(hamon::complex<T>(+1.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +inf), hamon::sqrt(hamon::complex<T>(-2.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +inf), hamon::sqrt(hamon::complex<T>(+inf, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +inf), hamon::sqrt(hamon::complex<T>(-inf, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +inf), hamon::sqrt(hamon::complex<T>(nan, +inf))));

	// If z is (x,NaN), the result is (NaN,NaN) (unless x is ±∞) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sqrt(hamon::complex<T>(+0.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sqrt(hamon::complex<T>(+1.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sqrt(hamon::complex<T>(-2.0, nan))));

	// If z is (-∞,y), the result is (+0,+∞) for finite positive y
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, +inf), hamon::sqrt(hamon::complex<T>(-inf, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, +inf), hamon::sqrt(hamon::complex<T>(-inf, +2.0))));

	// If z is (+∞,y), the result is (+∞,+0) for finite positive y
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::sqrt(hamon::complex<T>(+inf, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::sqrt(hamon::complex<T>(+inf, +2.0))));

	// If z is (-∞,NaN), the result is (NaN,∞) (sign of imaginary part unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(nan, +inf), hamon::sqrt(hamon::complex<T>(-inf, nan))) ||
		complex_eq(hamon::complex<T>(nan, -inf), hamon::sqrt(hamon::complex<T>(-inf, nan))));

	// If z is (+∞,NaN), the result is (+∞,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::sqrt(hamon::complex<T>(+inf, nan))));

	// If z is (NaN,y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sqrt(hamon::complex<T>(nan, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sqrt(hamon::complex<T>(nan, -2.0))));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sqrt(hamon::complex<T>(nan, nan))));
#endif
}

GTEST_TEST(ComplexTest, SqrtTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace sqrt_test

}	// namespace hamon_complex_test
