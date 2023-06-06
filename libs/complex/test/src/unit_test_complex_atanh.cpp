/**
 *	@file	unit_test_complex_atanh.cpp
 *
 *	@brief	atanh関数のテスト
 *
 *	template<class T> complex<T> atanh(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/atanh.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers/pi.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace atanh_test
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
	static_assert(hamon::is_same<decltype(hamon::atanh(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)

	{
		auto x = hamon::atanh(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 0.17328679513998629, (double)x.real(), error);
		EXPECT_NEAR( 1.1780972450961724,  (double)x.imag(), error);
	}
	{
		auto x = hamon::atanh(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR(-0.29251781316256364, (double)x.real(), error);
		EXPECT_NEAR( 1.3805431382387141,  (double)x.imag(), error);
	}
	{
		auto x = hamon::atanh(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 0.2678959040700476, (double)x.real(), error);
		EXPECT_NEAR(-1.4284311075335405, (double)x.imag(), error);
	}
	{
		auto x = hamon::atanh(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(-0.13770773959492247, (double)x.real(), error);
		EXPECT_NEAR(-1.4614618538579256,  (double)x.imag(), error);
	}

	// std::atanh(std::conj(z)) == std::conj(std::atanh(z))
	{
		hamon::complex<T> z{1.0, 2.5};
		EXPECT_TRUE((complex_near(hamon::atanh(hamon::conj(z)), hamon::conj(hamon::atanh(z)), error)));
	}
	{
		hamon::complex<T> z{2.0, -2.5};
		EXPECT_TRUE((complex_near(hamon::atanh(hamon::conj(z)), hamon::conj(hamon::atanh(z)), error)));
	}
	{
		hamon::complex<T> z{-2.5, 4.5};
		EXPECT_TRUE((complex_near(hamon::atanh(hamon::conj(z)), hamon::conj(hamon::atanh(z)), error)));
	}
	{
		hamon::complex<T> z{-1.5, -3.5};
		EXPECT_TRUE((complex_near(hamon::atanh(hamon::conj(z)), hamon::conj(hamon::atanh(z)), error)));
	}

	// std::atanh(-z) == -std::atanh(z)
	{
		hamon::complex<T> z{1.5, 2.0};
		EXPECT_TRUE((complex_near(hamon::atanh(-z), -hamon::atanh(z), error)));
	}
	{
		hamon::complex<T> z{-1.5, 2.5};
		EXPECT_TRUE((complex_near(hamon::atanh(-z), -hamon::atanh(z), error)));
	}
	{
		hamon::complex<T> z{3.5, -2.5};
		EXPECT_TRUE((complex_near(hamon::atanh(-z), -hamon::atanh(z), error)));
	}
	{
		hamon::complex<T> z{-2.5, -1.5};
		EXPECT_TRUE((complex_near(hamon::atanh(-z), -hamon::atanh(z), error)));
	}

#else

	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::atanh(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.17328679513998629, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1780972450961724,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::atanh(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.29251781316256364, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.3805431382387141,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::atanh(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.2678959040700476, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4284311075335405, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::atanh(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.13770773959492247, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4614618538579256,  (double)x.imag(), error);
	}

	// std::atanh(std::conj(z)) == std::conj(std::atanh(z))
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.0, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::atanh(hamon::conj(z)), hamon::conj(hamon::atanh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{2.0, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::atanh(hamon::conj(z)), hamon::conj(hamon::atanh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, 4.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::atanh(hamon::conj(z)), hamon::conj(hamon::atanh(z)), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, -3.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::atanh(hamon::conj(z)), hamon::conj(hamon::atanh(z)), error)));
	}

	// std::atanh(-z) == -std::atanh(z)
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{1.5, 2.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::atanh(-z), -hamon::atanh(z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-1.5, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::atanh(-z), -hamon::atanh(z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{3.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::atanh(-z), -hamon::atanh(z), error)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> z{-2.5, -1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((complex_near(hamon::atanh(-z), -hamon::atanh(z), error)));
	}

	HAMON_CXX11_CONSTEXPR T pi = hamon::numbers::pi_fn<T>();
	HAMON_CXX11_CONSTEXPR T nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR T inf = std::numeric_limits<T>::infinity();

	// If z is (+0,+0), the result is (+0,+0)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, +0.0), hamon::atanh(hamon::complex<T>(+0.0, +0.0))));

	// If z is (+0,NaN), the result is (+0,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, nan), hamon::atanh(hamon::complex<T>(+0.0, nan))));

	// If z is (+1,+0), the result is (+∞,+0) and FE_DIVBYZERO is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+inf, +0.0), hamon::atanh(hamon::complex<T>(+1.0, +0.0))));

	// If z is (x,+∞) (for any finite positive x), the result is (+0,π/2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, pi / 2), hamon::atanh(hamon::complex<T>(+1.0, +inf))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, pi / 2), hamon::atanh(hamon::complex<T>(+2.5, +inf))));

	// If z is (x,NaN) (for any finite nonzero x), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::atanh(hamon::complex<T>(+1.5, nan))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::atanh(hamon::complex<T>(-2.5, nan))));

	// If z is (+∞,y) (for any finite positive y), the result is (+0,π/2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, pi / 2), hamon::atanh(hamon::complex<T>(+inf, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, pi / 2), hamon::atanh(hamon::complex<T>(+inf, +2.5))));

	// If z is (+∞,+∞), the result is (+0,π/2)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, pi / 2), hamon::atanh(hamon::complex<T>(+inf, +inf))));

	// If z is (+∞,NaN), the result is (+0,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(+0.0, nan), hamon::atanh(hamon::complex<T>(+inf, nan))));

	// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::atanh(hamon::complex<T>(nan, +0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::atanh(hamon::complex<T>(nan, -0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::atanh(hamon::complex<T>(nan, +1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::atanh(hamon::complex<T>(nan, -2.5))));

	// If z is (NaN,+∞), the result is (±0,π/2) (the sign of the real part is unspecified)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(
		complex_eq(hamon::complex<T>(+0.0, pi / 2), hamon::atanh(hamon::complex<T>(nan, +inf))) ||
		complex_eq(hamon::complex<T>(-0.0, pi / 2), hamon::atanh(hamon::complex<T>(nan, +inf)))
	);

	// If z is (NaN,NaN), the result is (NaN,NaN)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(complex_eq(hamon::complex<T>(nan, nan), hamon::atanh(hamon::complex<T>(nan, nan))));

#endif
}

GTEST_TEST(ComplexTest, AtanhTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace atanh_test

}	// namespace hamon_complex_test
