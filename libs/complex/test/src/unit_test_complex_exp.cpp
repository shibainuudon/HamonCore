/**
 *	@file	unit_test_complex_exp.cpp
 *
 *	@brief	exp関数のテスト
 *
 *	template<class T> complex<T> exp(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/exp.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace exp_test
{

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 1e-5;
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
	static_assert(hamon::is_same<decltype(hamon::exp(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)

	{
		auto x = hamon::exp(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR(-1.1312043837568135, (double)x.real(), error);
		EXPECT_NEAR( 2.4717266720048188, (double)x.imag(), error);
	}
	{
		auto x = hamon::exp(hamon::complex<T>(1.5, -2.0));
		EXPECT_NEAR(-1.8650407290090902, (double)x.real(), error);
		EXPECT_NEAR(-4.0751883394911843, (double)x.imag(), error);
	}
	{
		auto x = hamon::exp(hamon::complex<T>(-3.0, 1.5));
		EXPECT_NEAR( 0.0035217978955813046, (double)x.real(), error);
		EXPECT_NEAR( 0.049662351094657595,  (double)x.imag(), error);
	}
	{
		auto x = hamon::exp(hamon::complex<T>(-1.5, -2.5));
		EXPECT_NEAR(-0.17875930323887937, (double)x.real(), error);
		EXPECT_NEAR(-0.13353718535828996, (double)x.imag(), error);
	}

	// std::exp(std::conj(z)) == std::conj(std::exp(z))
	{
		hamon::complex<T> z{1.0, 2.5};
		EXPECT_TRUE(complex_near(hamon::exp(hamon::conj(z)), hamon::conj(hamon::exp(z)), error));
	}
	{
		hamon::complex<T> z{1.5, -2.5};
		EXPECT_TRUE(complex_near(hamon::exp(hamon::conj(z)), hamon::conj(hamon::exp(z)), error));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE(complex_near(hamon::exp(hamon::conj(z)), hamon::conj(hamon::exp(z)), error));
	}
	{
		hamon::complex<T> z{-1.5, -1.5};
		EXPECT_TRUE(complex_near(hamon::exp(hamon::conj(z)), hamon::conj(hamon::exp(z)), error));
	}

#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::exp(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.1312043837568135, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.4717266720048188, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::exp(hamon::complex<T>(1.5, -2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.8650407290090902, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-4.0751883394911843, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::exp(hamon::complex<T>(-3.0, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0035217978955813046, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.049662351094657595,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::exp(hamon::complex<T>(-1.5, -2.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.17875930323887937, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.13353718535828996, (double)x.imag(), error);
	}

	// std::exp(std::conj(z)) == std::conj(std::exp(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_near(hamon::exp(hamon::conj(z)), hamon::conj(hamon::exp(z)), error));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_near(hamon::exp(hamon::conj(z)), hamon::conj(hamon::exp(z)), error));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_near(hamon::exp(hamon::conj(z)), hamon::conj(hamon::exp(z)), error));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, -1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_near(hamon::exp(hamon::conj(z)), hamon::conj(hamon::exp(z)), error));
	}

	HAMON_CXX11_CONSTEXPR T nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = std::numeric_limits<T>::infinity();

	// If z is (±0,+0), the result is (1,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(1.0, +0.0), hamon::exp(hamon::complex<T>(+0.0, +0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(1.0, +0.0), hamon::exp(hamon::complex<T>(-0.0, +0.0))));

	// If z is (x,+∞) (for any finite x), the result is (NaN,NaN) and FE_INVALID is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>( 0.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>( 1.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>(-2.5, +inf))));

	// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>( 0.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>( 1.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>(-2.5, nan))));

	// If z is (+∞,+0), the result is (+∞,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::exp(hamon::complex<T>(+inf, +0.0))));

	// If z is (-∞,y) (for any finite y), the result is +0 * complex(cos(y), sin(y))
	{
		HAMON_CXX11_CONSTEXPR T y = +0.0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(T(+0) * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::exp(hamon::complex<T>(-inf, y))));
	}
	{
		HAMON_CXX11_CONSTEXPR T y = +1.0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(T(+0) * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::exp(hamon::complex<T>(-inf, y))));
	}
	{
		HAMON_CXX11_CONSTEXPR T y = -2.5;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(T(+0) * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::exp(hamon::complex<T>(-inf, y))));
	}

	// If z is (+∞,y) (for any finite nonzero y), the result is +∞ * complex(cos(y), sin(y))
	{
		HAMON_CXX11_CONSTEXPR T y = 1.0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(+inf * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::exp(hamon::complex<T>(+inf, y))));
	}
	{
		HAMON_CXX11_CONSTEXPR T y = -2.5;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(+inf * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::exp(hamon::complex<T>(+inf, y))));
	}

	// If z is (-∞,+∞), the result is (±0,±0) (signs are unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+0.0, +0.0), hamon::exp(hamon::complex<T>(-inf, +inf))) ||
		complex_eq(hamon::complex<T>(+0.0, -0.0), hamon::exp(hamon::complex<T>(-inf, +inf))) ||
		complex_eq(hamon::complex<T>(-0.0, +0.0), hamon::exp(hamon::complex<T>(-inf, +inf))) ||
		complex_eq(hamon::complex<T>(-0.0, -0.0), hamon::exp(hamon::complex<T>(-inf, +inf)))
	);

	// If z is (+∞,+∞), the result is (±∞,NaN) and FE_INVALID is raised (the sign of the real part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+inf, nan), hamon::exp(hamon::complex<T>(+inf, +inf))) ||
		complex_eq(hamon::complex<T>(-inf, nan), hamon::exp(hamon::complex<T>(+inf, +inf)))
	);

	// If z is (-∞,NaN), the result is (±0,±0) (signs are unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+0.0, +0.0), hamon::exp(hamon::complex<T>(-inf, nan))) ||
		complex_eq(hamon::complex<T>(+0.0, -0.0), hamon::exp(hamon::complex<T>(-inf, nan))) ||
		complex_eq(hamon::complex<T>(-0.0, +0.0), hamon::exp(hamon::complex<T>(-inf, nan))) ||
		complex_eq(hamon::complex<T>(-0.0, -0.0), hamon::exp(hamon::complex<T>(-inf, nan)))
	);

	// If z is (+∞,NaN), the result is (±∞,NaN) (the sign of the real part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+inf, nan), hamon::exp(hamon::complex<T>(+inf, nan))) ||
		complex_eq(hamon::complex<T>(-inf, nan), hamon::exp(hamon::complex<T>(+inf, nan)))
	);

	// If z is (NaN,+0), the result is (NaN,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, +0.0), hamon::exp(hamon::complex<T>(nan, +0.0))));

	// If z is (NaN,y) (for any nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>(nan, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>(nan, -2.5))));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::exp(hamon::complex<T>(nan, nan))));
#endif
}

GTEST_TEST(ComplexTest, ExpTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace exp_test

}	// namespace hamon_complex_test
