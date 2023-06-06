/**
 *	@file	unit_test_complex_sin.cpp
 *
 *	@brief	sin関数のテスト
 *
 *	template<class T> complex<T> sin(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/sin.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace sin_test
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
	static_assert(hamon::is_same<decltype(hamon::sin(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::sin(hamon::complex<T>(1.0, 0.0));
		EXPECT_NEAR( 0.8414709848078965, (double)x.real(), error);
		EXPECT_NEAR( 0.0000000000000000, (double)x.imag(), error);
	}
	{
		auto x = hamon::sin(hamon::complex<T>(0.0, 1.0));
		EXPECT_NEAR( 0.0000000000000000, (double)x.real(), error);
		EXPECT_NEAR( 1.1752011936438014, (double)x.imag(), error);
	}
	{
		auto x = hamon::sin(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 3.1657785132161678, (double)x.real(), error);
		EXPECT_NEAR( 1.9596010414216061, (double)x.imag(), error);
	}
	{
		auto x = hamon::sin(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR(-1.4078516262453893, (double)x.real(), error);
		EXPECT_NEAR(-1.7058586411644667, (double)x.imag(), error);
	}
	{
		auto x = hamon::sin(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 0.33197206386323619, (double)x.real(), error);
		EXPECT_NEAR( 2.1079706837093544,  (double)x.imag(), error);
	}
	{
		auto x = hamon::sin(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(16.200435250741684,  (double)x.real(), error);
		EXPECT_NEAR( 3.4871163437824504, (double)x.imag(), error);
	}
#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sin(hamon::complex<T>(1.0, 0.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.8414709848078965, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sin(hamon::complex<T>(0.0, 1.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1752011936438014, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sin(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.1657785132161678, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.9596010414216061, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sin(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4078516262453893, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.7058586411644667, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sin(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.33197206386323619, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.1079706837093544,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::sin(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(16.200435250741684,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.4871163437824504, (double)x.imag(), error * 1e1);
	}
#endif
}

GTEST_TEST(ComplexTest, SinTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace sin_test

}	// namespace hamon_complex_test
