/**
 *	@file	unit_test_complex_tan.cpp
 *
 *	@brief	tan関数のテスト
 *
 *	template<class T> complex<T> tan(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/tan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace tan_test
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
	static_assert(hamon::is_same<decltype(hamon::tan(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::tan(hamon::complex<T>(1.0, 0.0));
		EXPECT_NEAR( 1.5574077246549023, (double)x.real(), error);
		EXPECT_NEAR( 0.0000000000000000, (double)x.imag(), error);
	}
	{
		auto x = hamon::tan(hamon::complex<T>(0.0, 1.0));
		EXPECT_NEAR( 0.00000000000000000, (double)x.real(), error);
		EXPECT_NEAR( 0.76159415595576485, (double)x.imag(), error);
	}
	{
		auto x = hamon::tan(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR( 0.033812826079896691, (double)x.real(), error);
		EXPECT_NEAR( 1.0147936161466338,   (double)x.imag(), error);
	}
	{
		auto x = hamon::tan(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR( 0.092637836268419885, (double)x.real(), error);
		EXPECT_NEAR( 0.96778680215277402,  (double)x.imag(), error);
	}
	{
		auto x = hamon::tan(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR(-0.02533730030009158, (double)x.real(), error);
		EXPECT_NEAR(-0.90841741793375785, (double)x.imag(), error);
	}
	{
		auto x = hamon::tan(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(-0.00075285721538218638, (double)x.real(), error);
		EXPECT_NEAR(-1.0016627850956348,     (double)x.imag(), error);
	}
#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tan(hamon::complex<T>(1.0, 0.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5574077246549023, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tan(hamon::complex<T>(0.0, 1.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.76159415595576485, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tan(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.033812826079896691, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0147936161466338,   (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tan(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.092637836268419885, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.96778680215277402,  (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tan(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.02533730030009158, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.90841741793375785, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::tan(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.00075285721538218638, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0016627850956348,     (double)x.imag(), error);
	}
#endif
}

GTEST_TEST(ComplexTest, TanTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace tan_test

}	// namespace hamon_complex_test
