/**
 *	@file	unit_test_complex_acos.cpp
 *
 *	@brief	acos関数のテスト
 *
 *	template<class T> complex<T> acos(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/acos.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers/pi.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace acos_test
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
	static_assert(hamon::is_same<decltype(hamon::acos(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR T pi = hamon::numbers::pi_fn<T>();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::acos(hamon::complex<T>(1, 2));
		EXPECT_NEAR( 1.1437177404024204, (double)x.real(), error);
		EXPECT_NEAR(-1.5285709194809982, (double)x.imag(), error);
	}
	{
		auto x = hamon::acos(hamon::complex<T>(-3.0, 1.5));
		EXPECT_NEAR( 2.6594445688559656, (double)x.real(), error);
		EXPECT_NEAR(-1.8902413596022003, (double)x.imag(), error);
	}
	{
		auto x = hamon::acos(hamon::complex<T>(2.5, -1.5));
		EXPECT_NEAR(0.56743361506164591, (double)x.real(), error);
		EXPECT_NEAR(1.7501487613175148,  (double)x.imag(), error);
	}
	{
		auto x = hamon::acos(hamon::complex<T>(-2.5, -3.5));
		EXPECT_NEAR(2.1784350605720864, (double)x.real(), error);
		EXPECT_NEAR(2.156624662472399,  (double)x.imag(), error);
	}

	// For any z, acos(z) = π - acos(-z).
	{
		hamon::complex<T> z{2.5, 3.5};
		EXPECT_TRUE((complex_near(hamon::acos(z), pi - hamon::acos(-z), error)));
	}
	{
		hamon::complex<T> z{-2.5, 3.5};
		EXPECT_TRUE((complex_near(hamon::acos(z), pi - hamon::acos(-z), error)));
	}
	{
		hamon::complex<T> z{2.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::acos(z), pi - hamon::acos(-z), error)));
	}
	{
		hamon::complex<T> z{-1.5, 1.0};
		EXPECT_TRUE((complex_near(hamon::acos(z), pi - hamon::acos(-z), error)));
	}

	// std::acos(std::conj(z)) == std::conj(std::acos(z))
	{
		hamon::complex<T> z{1.0, 2.5};
		EXPECT_TRUE((complex_near(hamon::acos(hamon::conj(z)), hamon::conj(hamon::acos(z)), error)));
	}
	{
		hamon::complex<T> z{1.5, -2.5};
		EXPECT_TRUE((complex_near(hamon::acos(hamon::conj(z)), hamon::conj(hamon::acos(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 3.5};
		EXPECT_TRUE((complex_near(hamon::acos(hamon::conj(z)), hamon::conj(hamon::acos(z)), error)));
	}
	{
		hamon::complex<T> z{-1.5, -2.5};
		EXPECT_TRUE((complex_near(hamon::acos(hamon::conj(z)), hamon::conj(hamon::acos(z)), error)));
	}

#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::acos(hamon::complex<T>(1, 2));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1437177404024204, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5285709194809982, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::acos(hamon::complex<T>(-3.0, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.6594445688559656, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.8902413596022003, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::acos(hamon::complex<T>(2.5, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.56743361506164591, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.7501487613175148,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::acos(hamon::complex<T>(-2.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.1784350605720864, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.156624662472399,  (double)x.imag(), error);
	}

	// For any z, acos(z) = π - acos(-z).
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{2.5, 3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acos(z), pi - hamon::acos(-z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acos(z), pi - hamon::acos(-z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{2.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acos(z), pi - hamon::acos(-z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, 1.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acos(z), pi - hamon::acos(-z), error)));
	}

	// std::acos(std::conj(z)) == std::conj(std::acos(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acos(hamon::conj(z)), hamon::conj(hamon::acos(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acos(hamon::conj(z)), hamon::conj(hamon::acos(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acos(hamon::conj(z)), hamon::conj(hamon::acos(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::acos(hamon::conj(z)), hamon::conj(hamon::acos(z)), error)));
	}

	HAMON_CXX11_CONSTEXPR T nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = std::numeric_limits<T>::infinity();

	// If z is (±0,+0), the result is (π/2,-0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi / 2, -0.0), hamon::acos(hamon::complex<T>(+0.0, +0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi / 2, -0.0), hamon::acos(hamon::complex<T>(-0.0, +0.0))));

	// If z is (±0,NaN), the result is (π/2,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi / 2, nan), hamon::acos(hamon::complex<T>(+0.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi / 2, nan), hamon::acos(hamon::complex<T>(-0.0, nan))));

	// If z is (x,+∞) (for any finite x), the result is (π/2,-∞)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi / 2, -inf), hamon::acos(hamon::complex<T>( 1.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi / 2, -inf), hamon::acos(hamon::complex<T>(-2.0, +inf))));

	// If z is (x,NaN) (for any nonzero finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acos(hamon::complex<T>( 1.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acos(hamon::complex<T>(-2.5, nan))));

	// If z is (-∞,y) (for any positive finite y), the result is (π,-∞)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi, -inf), hamon::acos(hamon::complex<T>(-inf, 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi, -inf), hamon::acos(hamon::complex<T>(-inf, 2.5))));

	// If z is (+∞,y) (for any positive finite y), the result is (+0,-∞)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, -inf), hamon::acos(hamon::complex<T>(+inf, 1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, -inf), hamon::acos(hamon::complex<T>(+inf, 2.5))));

	// If z is (-∞,+∞), the result is (3π/4,-∞)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi * 3 / 4, -inf), hamon::acos(hamon::complex<T>(-inf, +inf))));

	// If z is (+∞,+∞), the result is (π/4,-∞)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(pi / 4, -inf), hamon::acos(hamon::complex<T>(+inf, +inf))));

	// If z is (±∞,NaN), the result is (NaN,±∞) (the sign of the imaginary part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(nan, +inf), hamon::acos(hamon::complex<T>(+inf, nan))) ||
		complex_eq(hamon::complex<T>(nan, -inf), hamon::acos(hamon::complex<T>(+inf, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(nan, +inf), hamon::acos(hamon::complex<T>(-inf, nan))) ||
		complex_eq(hamon::complex<T>(nan, -inf), hamon::acos(hamon::complex<T>(-inf, nan))));

	// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acos(hamon::complex<T>(nan,  1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acos(hamon::complex<T>(nan, -2.5))));

	// If z is (NaN,+∞), the result is (NaN,-∞)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, -inf), hamon::acos(hamon::complex<T>(nan, +inf))));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::acos(hamon::complex<T>(nan, nan))));
#endif
}

GTEST_TEST(ComplexTest, AcosTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace acos_test

}	// namespace hamon_complex_test
