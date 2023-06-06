/**
 *	@file	unit_test_complex_cos.cpp
 *
 *	@brief	cos関数のテスト
 *
 *	template<class T> complex<T> cos(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/cos.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace cos_test
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
	static_assert(hamon::is_same<decltype(hamon::cos(hamon::complex<T>{})), hamon::complex<T>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

#if defined(HAMON_USE_STD_COMPLEX)
	{
		auto x = hamon::cos(hamon::complex<T>(1.0, 0.0));
		EXPECT_NEAR( 0.00000000000000000, (double)x.imag(), error);
		EXPECT_NEAR( 0.54030230586813977, (double)x.real(), error);
	}
	{
		auto x = hamon::cos(hamon::complex<T>(0.0, 1.0));
		EXPECT_NEAR(-0.0000000000000000, (double)x.imag(), error);
		EXPECT_NEAR( 1.5430806348152437, (double)x.real(), error);
	}
	{
		auto x = hamon::cos(hamon::complex<T>(1.0, 2.0));
		EXPECT_NEAR(-3.0518977991517997, (double)x.imag(), error);
		EXPECT_NEAR( 2.0327230070196656, (double)x.real(), error);
	}
	{
		auto x = hamon::cos(hamon::complex<T>(-2.5, 1.5));
		EXPECT_NEAR( 1.2743144408870994, (double)x.imag(), error);
		EXPECT_NEAR(-1.8846179444033462, (double)x.real(), error);
	}
	{
		auto x = hamon::cos(hamon::complex<T>(3.0, -1.5));
		EXPECT_NEAR( 0.3004839338646903, (double)x.imag(), error);
		EXPECT_NEAR(-2.3288678680215553, (double)x.real(), error);
	}
	{
		auto x = hamon::cos(hamon::complex<T>(-4.5, -3.5));
		EXPECT_NEAR(-3.493481825361676, (double)x.real(), error);
		EXPECT_NEAR(16.170916398971684, (double)x.imag(), error * 1e1);
	}
#else
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cos(hamon::complex<T>(1.0, 0.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)x.imag(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54030230586813977, (double)x.real(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cos(hamon::complex<T>(0.0, 1.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.0000000000000000, (double)x.imag(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5430806348152437, (double)x.real(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cos(hamon::complex<T>(1.0, 2.0));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.0518977991517997, (double)x.imag(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0327230070196656, (double)x.real(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cos(hamon::complex<T>(-2.5, 1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.2743144408870994, (double)x.imag(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.8846179444033462, (double)x.real(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cos(hamon::complex<T>(3.0, -1.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.3004839338646903, (double)x.imag(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.3288678680215553, (double)x.real(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::cos(hamon::complex<T>(-4.5, -3.5));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.493481825361676, (double)x.real(), error * 1e1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(16.170916398971684, (double)x.imag(), error * 1e1);
	}
#endif
}

GTEST_TEST(ComplexTest, CosTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace cos_test

}	// namespace hamon_complex_test
