/**
 *	@file	unit_test_complex_cosh.cpp
 *
 *	@brief	cosh関数のテスト
 *
 *	template<class T> complex<T> cosh(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/cosh.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/cmath.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace cosh_test
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
	static_assert(hamon::is_same<decltype(hamon::cosh(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)

	{
		auto x = hamon::cosh(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR(-0.64214812471551996, (double)x.real(), error);
		EXPECT_NEAR( 1.0686074213827783,  (double)x.imag(), error);
	}
	{
		auto x = hamon::cosh(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR( 0.433780997607703,  (double)x.real(), error);
		EXPECT_NEAR(-6.0350486377665717, (double)x.imag(), error);
	}
	{
		auto x = hamon::cosh(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 0.71215823691759994, (double)x.real(), error);
		EXPECT_NEAR(-9.9927800165178322,  (double)x.imag(), error);
	}
	{
		auto x = hamon::cosh(hamon::complex<T>(-1.5, -3.5));
		EXPECT_NEAR(-2.2029297154417082,  (double)x.real(), error);
		EXPECT_NEAR(-0.74691551991135496, (double)x.imag(), error);
	}

	// cosh(conj(z)) == conj(cosh(z))
	{
		hamon::complex<T> z{1.0, 2.5};
		EXPECT_TRUE((complex_near(hamon::cosh(hamon::conj(z)), hamon::conj(hamon::cosh(z)), error)));
	}
	{
		hamon::complex<T> z{2.0, -2.5};
		EXPECT_TRUE((complex_near(hamon::cosh(hamon::conj(z)), hamon::conj(hamon::cosh(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 1.5};
		EXPECT_TRUE((complex_near(hamon::cosh(hamon::conj(z)), hamon::conj(hamon::cosh(z)), error)));
	}
	{
		hamon::complex<T> z{-1.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::cosh(hamon::conj(z)), hamon::conj(hamon::cosh(z)), error)));
	}

	// cosh(z) == cosh(-z)
	{
		hamon::complex<T> z{1.5, 2.0};
		EXPECT_TRUE((complex_eq(hamon::cosh(z), hamon::cosh(-z))));
	}
	{
		hamon::complex<T> z{-1.5, 2.5};
		EXPECT_TRUE((complex_eq(hamon::cosh(z), hamon::cosh(-z))));
	}
	{
		hamon::complex<T> z{3.5, -2.5};
		EXPECT_TRUE((complex_eq(hamon::cosh(z), hamon::cosh(-z))));
	}
	{
		hamon::complex<T> z{-2.5, -1.5};
		EXPECT_TRUE((complex_eq(hamon::cosh(z), hamon::cosh(-z))));
	}

#else

	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cosh(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.64214812471551996, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0686074213827783,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cosh(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.433780997607703,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-6.0350486377665717, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cosh(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.71215823691759994, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-9.9927800165178322,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cosh(hamon::complex<T>(-1.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.2029297154417082,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.74691551991135496, (double)x.imag(), error);
	}

	// cosh(conj(z)) == conj(cosh(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::cosh(hamon::conj(z)), hamon::conj(hamon::cosh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{2.0, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::cosh(hamon::conj(z)), hamon::conj(hamon::cosh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::cosh(hamon::conj(z)), hamon::conj(hamon::cosh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::cosh(hamon::conj(z)), hamon::conj(hamon::cosh(z)), error)));
	}

	// cosh(z) == cosh(-z)
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, 2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::cosh(z), hamon::cosh(-z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::cosh(z), hamon::cosh(-z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{3.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::cosh(z), hamon::cosh(-z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::cosh(z), hamon::cosh(-z))));
	}

	HAMON_CXX11_CONSTEXPR T nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = hamon::numeric_limits<T>::infinity();

	// If z is (+0,+0), the result is (1,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+1.0, +0.0), hamon::cosh(hamon::complex<T>(+0.0, +0.0))));

	// If z is (+0,+∞), the result is (NaN,±0) (the sign of the imaginary part is unspecified) and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(nan, +0.0), hamon::cosh(hamon::complex<T>(+0.0, +inf))) ||
		complex_eq(hamon::complex<T>(nan, -0.0), hamon::cosh(hamon::complex<T>(+0.0, +inf)))
	);

	// If z is (+0,NaN), the result is (NaN,±0) (the sign of the imaginary part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(nan, +0.0), hamon::cosh(hamon::complex<T>(+0.0, nan))) ||
		complex_eq(hamon::complex<T>(nan, -0.0), hamon::cosh(hamon::complex<T>(+0.0, nan)))
	);

	// If z is (x,+∞) (for any finite non-zero x), the result is (NaN,NaN) and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::cosh(hamon::complex<T>(+1.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::cosh(hamon::complex<T>(-2.5, +inf))));

	// If z is (x,NaN) (for any finite non-zero x), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::cosh(hamon::complex<T>(+1.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::cosh(hamon::complex<T>(-2.5, nan))));

	// If z is (+∞,+0), the result is (+∞,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::cosh(hamon::complex<T>(+inf, +0.0))));

	// If z is (+∞,y) (for any finite non-zero y), the result is +∞cis(y)
	{
		HAMON_CXX11_CONSTEXPR T y = +1.0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(+inf * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::cosh(hamon::complex<T>(+inf, y))));
	}
	{
		HAMON_CXX11_CONSTEXPR T y = +1.5;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(+inf * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::cosh(hamon::complex<T>(+inf, y))));
	}

	// If z is (+∞,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+inf, nan), hamon::cosh(hamon::complex<T>(+inf, +inf))) ||
		complex_eq(hamon::complex<T>(-inf, nan), hamon::cosh(hamon::complex<T>(+inf, +inf)))
	);

	// If z is (+∞,NaN), the result is (+∞,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::cosh(hamon::complex<T>(+inf, nan))));

	// If z is (NaN,+0), the result is (NaN,±0) (the sign of the imaginary part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(nan, +0.0), hamon::cosh(hamon::complex<T>(nan, +0.0))) ||
		complex_eq(hamon::complex<T>(nan, -0.0), hamon::cosh(hamon::complex<T>(nan, +0.0)))
	);

	// If z is (NaN,+y) (for any finite non-zero y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::cosh(hamon::complex<T>(nan, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::cosh(hamon::complex<T>(nan, -2.5))));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::cosh(hamon::complex<T>(nan, nan))));

#endif
}

GTEST_TEST(ComplexTest, CoshTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace cosh_test

}	// namespace hamon_complex_test
