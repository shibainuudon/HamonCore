/**
 *	@file	unit_test_complex_tanh.cpp
 *
 *	@brief	tanh関数のテスト
 *
 *	template<class T> complex<T> tanh(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/tanh.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace tanh_test
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
	static_assert(hamon::is_same<decltype(hamon::tanh(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)

	{
		auto x = hamon::tanh(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 1.1667362572409199,  (double)x.real(), error);
		EXPECT_NEAR(-0.24345820118572525, (double)x.imag(), error);
	}
	{
		auto x = hamon::tanh(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR(-1.0134287782038935,    (double)x.real(), error);
		EXPECT_NEAR( 0.0019273435237456365, (double)x.imag(), error);
	}
	{
		auto x = hamon::tanh(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 1.0049197189087831,    (double)x.real(), error);
		EXPECT_NEAR(-0.0007030492243577473, (double)x.imag(), error);
	}
	{
		auto x = hamon::tanh(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(-0.99981392630805044,    (double)x.real(), error);
		EXPECT_NEAR(-0.00016212700415590612, (double)x.imag(), error);
	}

	// tanh(conj(z)) == conj(tanh(z))
	{
		hamon::complex<T> z{1.0, 2.5};
		EXPECT_TRUE((complex_near(hamon::tanh(hamon::conj(z)), hamon::conj(hamon::tanh(z)), error)));
	}
	{
		hamon::complex<T> z{1.5, -2.5};
		EXPECT_TRUE((complex_near(hamon::tanh(hamon::conj(z)), hamon::conj(hamon::tanh(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE((complex_near(hamon::tanh(hamon::conj(z)), hamon::conj(hamon::tanh(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::tanh(hamon::conj(z)), hamon::conj(hamon::tanh(z)), error)));
	}

	// tanh(-z) == -tanh(z)
	{
		hamon::complex<T> z{1.5, 2.0};
		EXPECT_TRUE((complex_eq(hamon::tanh(-z), -hamon::tanh(z))));
	}
	{
		hamon::complex<T> z{-1.5, 2.5};
		EXPECT_TRUE((complex_eq(hamon::tanh(-z), -hamon::tanh(z))));
	}
	{
		hamon::complex<T> z{3.5, -2.5};
		EXPECT_TRUE((complex_eq(hamon::tanh(-z), -hamon::tanh(z))));
	}
	{
		hamon::complex<T> z{-2.5, -1.5};
		EXPECT_TRUE((complex_eq(hamon::tanh(-z), -hamon::tanh(z))));
	}

#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tanh(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1667362572409199,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.24345820118572525, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tanh(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0134287782038935,    (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0019273435237456365, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tanh(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0049197189087831,    (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.0007030492243577473, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tanh(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.99981392630805044,    (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.00016212700415590612, (double)x.imag(), error);
	}

	// tanh(conj(z)) == conj(tanh(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::tanh(hamon::conj(z)), hamon::conj(hamon::tanh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::tanh(hamon::conj(z)), hamon::conj(hamon::tanh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::tanh(hamon::conj(z)), hamon::conj(hamon::tanh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::tanh(hamon::conj(z)), hamon::conj(hamon::tanh(z)), error)));
	}

	// tanh(-z) == -tanh(z)
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, 2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::tanh(-z), -hamon::tanh(z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::tanh(-z), -hamon::tanh(z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{3.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::tanh(-z), -hamon::tanh(z))));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_eq(hamon::tanh(-z), -hamon::tanh(z))));
	}

	HAMON_CXX11_CONSTEXPR T nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = hamon::numeric_limits<T>::infinity();

	// If z is (+0,+0), the result is (+0,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, +0.0), hamon::tanh(hamon::complex<T>(+0.0, +0.0))));

	// If z is (x,+∞) (for any non-zero finite x), the result is (NaN,NaN) and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::tanh(hamon::complex<T>(+1.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::tanh(hamon::complex<T>(-2.5, +inf))));

	// If z is (0,∞), the result should be (0,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, nan), hamon::tanh(hamon::complex<T>(+0.0, +inf))));

	// If z is (x,NaN) (for any non-zero finite x), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::tanh(hamon::complex<T>(+1.0, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::tanh(hamon::complex<T>(-2.5, nan))));

	// If z is (0,NaN), the result should be (0,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, nan), hamon::tanh(hamon::complex<T>(+0.0, nan))));

	// If z is (+∞,y) (for any finite positive y), the result is (1,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+1.0, +0.0), hamon::tanh(hamon::complex<T>(+inf, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+1.0, +0.0), hamon::tanh(hamon::complex<T>(+inf, +2.5))));

	// If z is (+∞,+∞), the result is (1,±0) (the sign of the imaginary part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+1.0, +0.0), hamon::tanh(hamon::complex<T>(+inf, +inf))) ||
		complex_eq(hamon::complex<T>(+1.0, -0.0), hamon::tanh(hamon::complex<T>(+inf, +inf)))
	);

	// If z is (+∞,NaN), the result is (1,±0) (the sign of the imaginary part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+1.0, +0.0), hamon::tanh(hamon::complex<T>(+inf, nan))) ||
		complex_eq(hamon::complex<T>(+1.0, -0.0), hamon::tanh(hamon::complex<T>(+inf, nan)))
	);

	// If z is (NaN,+0), the result is (NaN,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, +0.0), hamon::tanh(hamon::complex<T>(nan, +0.0))));

	// If z is (NaN,y) (for any non-zero y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::tanh(hamon::complex<T>(nan, +1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::tanh(hamon::complex<T>(nan, -2.0))));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::tanh(hamon::complex<T>(nan, nan))));
#endif
}

GTEST_TEST(ComplexTest, TanhTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace tanh_test

}	// namespace hamon_complex_test
