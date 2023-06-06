/**
 *	@file	unit_test_complex_atan.cpp
 *
 *	@brief	atan関数のテスト
 *
 *	template<class T> complex<T> atan(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/atan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace atan_test
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
	static_assert(hamon::is_same<decltype(hamon::atan(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::atan(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 1.3389725222944935,  (double)x.real(), error);
		EXPECT_NEAR( 0.40235947810852507, (double)x.imag(), error);
	}
	{
		auto x = hamon::atan(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR(-1.2767950250211129,  (double)x.real(), error);
		EXPECT_NEAR( 0.16348161685166601, (double)x.imag(), error);
	}
	{
		auto x = hamon::atan(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 1.3060015274038583,  (double)x.real(), error);
		EXPECT_NEAR(-0.12498898788227171, (double)x.imag(), error);
	}
	{
		auto x = hamon::atan(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(-1.4316464972923408,  (double)x.real(), error);
		EXPECT_NEAR(-0.10603931028007922, (double)x.imag(), error);
	}
#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::atan(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.3389725222944935,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.40235947810852507, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::atan(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.2767950250211129,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.16348161685166601, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::atan(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.3060015274038583,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.12498898788227171, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::atan(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4316464972923408,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.10603931028007922, (double)x.imag(), error);
	}
#endif
}

GTEST_TEST(ComplexTest, AtanTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace atan_test

}	// namespace hamon_complex_test
