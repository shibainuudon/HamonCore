/**
 *	@file	unit_test_complex_asinh.cpp
 *
 *	@brief	asinh関数のテスト
 *
 *	template<class T> complex<T> asinh(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/asinh.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace asinh_test
{

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 1e-4;
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
	static_assert(hamon::is_same<decltype(hamon::asinh(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)

	{
		auto x = hamon::asinh(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR(1.4693517443681852, (double)x.real(), error);
		EXPECT_NEAR(1.0634400235777519, (double)x.imag(), error);
	}
	{
		auto x = hamon::asinh(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR(-1.7776623775066449, (double)x.real(), error);
		EXPECT_NEAR(0.51554843573490672, (double)x.imag(), error);
	}
	{
		auto x = hamon::asinh(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 1.9168395294689364,  (double)x.real(), error);
		EXPECT_NEAR(-0.44656704907176997, (double)x.imag(), error);
	}
	{
		auto x = hamon::asinh(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(-2.4357376718882664,  (double)x.real(), error);
		EXPECT_NEAR(-0.65363098723852442, (double)x.imag(), error);
	}

	// asinh(conj(z)) == conj(asinh(z))
	{
		hamon::complex<T> z{1,2};
		EXPECT_TRUE((complex_near(hamon::asinh(hamon::conj(z)), hamon::conj(hamon::asinh(z)), error)));
	}
	{
		hamon::complex<T> z{1.5, -2.5};
		EXPECT_TRUE((complex_near(hamon::asinh(hamon::conj(z)), hamon::conj(hamon::asinh(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE((complex_near(hamon::asinh(hamon::conj(z)), hamon::conj(hamon::asinh(z)), error)));
	}
	{
		hamon::complex<T> z{-1.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::asinh(hamon::conj(z)), hamon::conj(hamon::asinh(z)), error)));
	}

	// asinh(-z) == -asinh(z)
	{
		hamon::complex<T> z{1.0, 2.5};
		EXPECT_TRUE((complex_near(hamon::asinh(-z), -hamon::asinh(z), error)));
	}
	{
		hamon::complex<T> z{1.5, -2.0};
		EXPECT_TRUE((complex_near(hamon::asinh(-z), -hamon::asinh(z), error)));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE((complex_near(hamon::asinh(-z), -hamon::asinh(z), error)));
	}
	{
		hamon::complex<T> z{-2.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::asinh(-z), -hamon::asinh(z), error)));
	}

#else

	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::asinh(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.4693517443681852, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0634400235777519, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::asinh(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.7776623775066449, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.51554843573490672, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::asinh(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.9168395294689364,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.44656704907176997, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::asinh(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.4357376718882664,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.65363098723852442, (double)x.imag(), error);
	}

	// asinh(conj(z)) == conj(asinh(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1,2};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::asinh(hamon::conj(z)), hamon::conj(hamon::asinh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::asinh(hamon::conj(z)), hamon::conj(hamon::asinh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::asinh(hamon::conj(z)), hamon::conj(hamon::asinh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::asinh(hamon::conj(z)), hamon::conj(hamon::asinh(z)), error)));
	}

	// asinh(-z) == -asinh(z)
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::asinh(-z), -hamon::asinh(z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, -2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::asinh(-z), -hamon::asinh(z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::asinh(-z), -hamon::asinh(z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::asinh(-z), -hamon::asinh(z), error)));
	}

	HAMON_CXX11_CONSTEXPR T pi = hamon::numbers::pi_fn<T>();
	HAMON_CXX11_CONSTEXPR T nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = hamon::numeric_limits<T>::infinity();

	// If z is (+0,+0), the result is (+0,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, +0.0), hamon::asinh(hamon::complex<T>(+0.0, +0.0))));

	// If z is (x,+∞) (for any positive finite x), the result is (+∞,π/2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 2), hamon::asinh(hamon::complex<T>(+1.5, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 2), hamon::asinh(hamon::complex<T>(+2.5, +inf))));

	// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::asinh(hamon::complex<T>(+0.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::asinh(hamon::complex<T>(+1.5, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::asinh(hamon::complex<T>(-2.5, nan))));

	// If z is (+∞,y) (for any positive finite y), the result is (+∞,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::asinh(hamon::complex<T>(+inf, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::asinh(hamon::complex<T>(+inf, +2.5))));

	// If z is (+∞,+∞), the result is (+∞,π/4)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, pi / 4), hamon::asinh(hamon::complex<T>(+inf, +inf))));

	// If z is (+∞,NaN), the result is (+∞,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, nan), hamon::asinh(hamon::complex<T>(+inf, nan))));

	// If z is (NaN,+0), the result is (NaN,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, +0.0), hamon::asinh(hamon::complex<T>(nan, +0.0))));

	// If z is (NaN,y) (for any finite nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::asinh(hamon::complex<T>(nan, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::asinh(hamon::complex<T>(nan, -2.5))));

	// If z is (NaN,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+inf, nan), hamon::asinh(hamon::complex<T>(nan, +inf))) ||
		complex_eq(hamon::complex<T>(-inf, nan), hamon::asinh(hamon::complex<T>(nan, +inf)))
	);

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::asinh(hamon::complex<T>(nan, nan))));

#endif
}

GTEST_TEST(ComplexTest, AsinhTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace asinh_test

}	// namespace hamon_complex_test
