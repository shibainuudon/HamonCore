/**
 *	@file	unit_test_complex_sinh.cpp
 *
 *	@brief	sinh関数のテスト
 *
 *	template<class T> complex<T> sinh(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/sinh.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/cmath.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace sinh_test
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
	static_assert(hamon::is_same<decltype(hamon::sinh(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::sinh(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR(-0.48905625904129368, (double)x.real(), error);
		EXPECT_NEAR( 1.4031192506220405,  (double)x.imag(), error);
	}
	{
		auto x = hamon::sinh(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR(-0.42797453450615119, (double)x.real(), error);
		EXPECT_NEAR( 6.1169280123693115,  (double)x.imag(), error);
	}
	{
		auto x = hamon::sinh(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR(  0.70863643902201878, (double)x.real(), error);
		EXPECT_NEAR(-10.042442367612487,   (double)x.imag(), error);
	}
	{
		auto x = hamon::sinh(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(42.143370741504995, (double)x.real(), error * 1e2);
		EXPECT_NEAR(15.790198357309713, (double)x.imag(), error * 1e2);
	}

	// std::sinh(std::conj(z)) == std::conj(std::sinh(z))
	{
		hamon::complex<T> z{1.0, 2.5};
		EXPECT_TRUE((complex_near(hamon::sinh(hamon::conj(z)), hamon::conj(hamon::sinh(z)), error)));
	}
	{
		hamon::complex<T> z{2.0, -2.5};
		EXPECT_TRUE((complex_near(hamon::sinh(hamon::conj(z)), hamon::conj(hamon::sinh(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 1.5};
		EXPECT_TRUE((complex_near(hamon::sinh(hamon::conj(z)), hamon::conj(hamon::sinh(z)), error)));
	}
	{
		hamon::complex<T> z{-1.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::sinh(hamon::conj(z)), hamon::conj(hamon::sinh(z)), error)));
	}

	// std::sinh(z) == -std::sinh(-z)
	{
		hamon::complex<T> z{1.5, 2.0};
		EXPECT_TRUE((complex_eq(hamon::sinh(z), -hamon::sinh(-z))));
	}
	{
		hamon::complex<T> z{-1.5, 2.5};
		EXPECT_TRUE((complex_eq(hamon::sinh(z), -hamon::sinh(-z))));
	}
	{
		hamon::complex<T> z{3.5, -2.5};
		EXPECT_TRUE((complex_eq(hamon::sinh(z), -hamon::sinh(-z))));
	}
	{
		hamon::complex<T> z{-2.5, -1.5};
		EXPECT_TRUE((complex_eq(hamon::sinh(z), -hamon::sinh(-z))));
	}

#else

	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sinh(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.48905625904129368, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4031192506220405,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sinh(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.42797453450615119, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.1169280123693115,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sinh(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.70863643902201878, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-10.042442367612487,   (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sinh(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(42.143370741504995, (double)x.real(), error * 1e2);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(15.790198357309713, (double)x.imag(), error * 1e2);
	}

	// std::sinh(std::conj(z)) == std::conj(std::sinh(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::sinh(hamon::conj(z)), hamon::conj(hamon::sinh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{2.0, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::sinh(hamon::conj(z)), hamon::conj(hamon::sinh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::sinh(hamon::conj(z)), hamon::conj(hamon::sinh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::sinh(hamon::conj(z)), hamon::conj(hamon::sinh(z)), error)));
	}

	// std::sinh(z) == -std::sinh(-z)
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, 2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::sinh(z), -hamon::sinh(-z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::sinh(z), -hamon::sinh(-z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{3.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::sinh(z), -hamon::sinh(-z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::sinh(z), -hamon::sinh(-z))));
	}
	
	HAMON_CXX11_CONSTEXPR T nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = std::numeric_limits<T>::infinity();

	// If z is (+0,+0), the result is (+0,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, +0.0), hamon::sinh(hamon::complex<T>(+0.0, +0.0))));

	// If z is (+0,+∞), the result is (±0,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+0.0, nan), hamon::sinh(hamon::complex<T>(+0.0, +inf))) ||
		complex_eq(hamon::complex<T>(-0.0, nan), hamon::sinh(hamon::complex<T>(+0.0, +inf)))
	);

	// If z is (+0,NaN), the result is (±0,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+0.0, nan), hamon::sinh(hamon::complex<T>(+0.0, nan))) ||
		complex_eq(hamon::complex<T>(-0.0, nan), hamon::sinh(hamon::complex<T>(+0.0, nan)))
	);

	// If z is (x,+∞) (for any positive finite x), the result is (NaN,NaN) and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sinh(hamon::complex<T>(+1.5, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sinh(hamon::complex<T>(+2.0, +inf))));

	// If z is (x,NaN) (for any positive finite x), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sinh(hamon::complex<T>(+1.5, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sinh(hamon::complex<T>(+2.0, nan))));

	// If z is (+∞,+0), the result is (+∞,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::sinh(hamon::complex<T>(+inf, +0.0))));

	// If z is (+∞,y) (for any positive finite y), the result is +∞cis(y)
	{
		HAMON_CXX11_CONSTEXPR T y = +1.0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(+inf * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::sinh(hamon::complex<T>(+inf, y))));
	}
	{
		HAMON_CXX11_CONSTEXPR T y = +1.5;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(+inf * hamon::complex<T>(hamon::cos(y), hamon::sin(y)), hamon::sinh(hamon::complex<T>(+inf, y))));
	}

	// If z is (+∞,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+inf, nan), hamon::sinh(hamon::complex<T>(+inf, +inf))) ||
		complex_eq(hamon::complex<T>(-inf, nan), hamon::sinh(hamon::complex<T>(+inf, +inf)))
	);

	// If z is (+∞,NaN), the result is (±∞,NaN) (the sign of the real part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+inf, nan), hamon::sinh(hamon::complex<T>(+inf, nan))) ||
		complex_eq(hamon::complex<T>(-inf, nan), hamon::sinh(hamon::complex<T>(+inf, nan)))
	);

	// If z is (NaN,+0), the result is (NaN,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, +0.0), hamon::sinh(hamon::complex<T>(nan, +0.0))));

	// If z is (NaN,y) (for any finite nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sinh(hamon::complex<T>(nan, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sinh(hamon::complex<T>(nan, -2.5))));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::sinh(hamon::complex<T>(nan, nan))));

#endif
}

GTEST_TEST(ComplexTest, SinhTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace sinh_test

}	// namespace hamon_complex_test
