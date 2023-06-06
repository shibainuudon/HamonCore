/**
 *	@file	unit_test_complex_acosh.cpp
 *
 *	@brief	acosh関数のテスト
 *
 *	template<class T> complex<T> acosh(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/acosh.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers/pi.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace acosh_test
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
	static_assert(hamon::is_same<decltype(hamon::acosh(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)

	{
		auto x = hamon::acosh(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 1.5285709194809982, (double)x.real(), error);
		EXPECT_NEAR( 1.1437177404024204, (double)x.imag(), error);
	}
	{
		auto x = hamon::acosh(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR( 1.7501487613175148, (double)x.real(), error);
		EXPECT_NEAR( 2.5741590385281472, (double)x.imag(), error);
	}
	{
		auto x = hamon::acosh(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 1.8902413596022003,  (double)x.real(), error);
		EXPECT_NEAR(-0.48214808473382775, (double)x.imag(), error);
	}
	{
		auto x = hamon::acosh(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR( 2.4319527481396968, (double)x.real(), error);
		EXPECT_NEAR(-2.4730526515659954, (double)x.imag(), error);
	}

	// std::acosh(std::conj(z)) == std::conj(std::acosh(z))
	{
		hamon::complex<T> z{1.0, 2.5};
		EXPECT_TRUE((complex_near(hamon::acosh(hamon::conj(z)), hamon::conj(hamon::acosh(z)), error)));
	}
	{
		hamon::complex<T> z{1.5, -2.5};
		EXPECT_TRUE((complex_near(hamon::acosh(hamon::conj(z)), hamon::conj(hamon::acosh(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE((complex_near(hamon::acosh(hamon::conj(z)), hamon::conj(hamon::acosh(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::acosh(hamon::conj(z)), hamon::conj(hamon::acosh(z)), error)));
	}

#else

	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::acosh(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5285709194809982, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1437177404024204, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::acosh(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7501487613175148, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.5741590385281472, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::acosh(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.8902413596022003,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.48214808473382775, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::acosh(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.4319527481396968, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.4730526515659954, (double)x.imag(), error);
	}

	// std::acosh(std::conj(z)) == std::conj(std::acosh(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acosh(hamon::conj(z)), hamon::conj(hamon::acosh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acosh(hamon::conj(z)), hamon::conj(hamon::acosh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acosh(hamon::conj(z)), hamon::conj(hamon::acosh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acosh(hamon::conj(z)), hamon::conj(hamon::acosh(z)), error)));
	}

	HAMON_CXX11_CONSTEXPR T pi = hamon::numbers::pi_fn<T>();
	HAMON_CXX11_CONSTEXPR T nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = std::numeric_limits<T>::infinity();

	// If z is (±0,+0), the result is (+0,π/2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, pi / 2), hamon::acosh(hamon::complex<T>(+0.0, +0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, pi / 2), hamon::acosh(hamon::complex<T>(-0.0, +0.0))));

	// If z is (x,+∞) (for any finite x), the result is (+∞,π/2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 2), hamon::acosh(hamon::complex<T>(+0.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 2), hamon::acosh(hamon::complex<T>(-1.5, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 2), hamon::acosh(hamon::complex<T>(+2.5, +inf))));

	// If z is (x,NaN) (for any non-zero finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acosh(hamon::complex<T>(+1.5, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acosh(hamon::complex<T>(-2.5, nan))));

	// If z is (0,NaN), the result should be (NaN,π/2)	(C11 DR471)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, pi / 2), hamon::acosh(hamon::complex<T>(+0.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, pi / 2), hamon::acosh(hamon::complex<T>(-0.0, nan))));

	// If z is (-∞,y) (for any positive finite y), the result is (+∞,π)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi), hamon::acosh(hamon::complex<T>(-inf, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi), hamon::acosh(hamon::complex<T>(-inf, +2.5))));

	// If z is (+∞,y) (for any positive finite y), the result is (+∞,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::acosh(hamon::complex<T>(+inf, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::acosh(hamon::complex<T>(+inf, +2.5))));

	// If z is (-∞,+∞), the result is (+∞,3π/4)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi * 3 / 4), hamon::acosh(hamon::complex<T>(-inf, +inf))));

	// If z is (±∞,NaN), the result is (+∞,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::acosh(hamon::complex<T>(+inf, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::acosh(hamon::complex<T>(-inf, nan))));

	// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acosh(hamon::complex<T>(nan, +0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acosh(hamon::complex<T>(nan, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acosh(hamon::complex<T>(nan, -2.5))));

	// If z is (NaN,+∞), the result is (+∞,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::acosh(hamon::complex<T>(nan, +inf))));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acosh(hamon::complex<T>(nan, nan))));

#endif
}

GTEST_TEST(ComplexTest, AcoshTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace acosh_test

}	// namespace hamon_complex_test
