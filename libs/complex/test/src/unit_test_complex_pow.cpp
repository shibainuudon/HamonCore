/**
 *	@file	unit_test_complex_pow.cpp
 *
 *	@brief	pow関数のテスト
 *
 *	template<class T> complex<T> pow(const complex<T>& x, const complex<T>& y);
 *	template<class T> complex<T> pow(const complex<T>& x, const T& y);
 *	template<class T> complex<T> pow(const T& x, const complex<T>& y);
 * 
 *	template<class T1, class T2>
 *	complex<common_type_t<T1, T2>>
 *	pow(const complex<T1>& x, const complex<T2>& y);
 * 
 *	template<class T, class NonComplex>
 *	complex<common_type_t<T, NonComplex>>
 *	pow(const complex<T>& x, const NonComplex& y);
 * 
 *	template<class T, class NonComplex>
 *	complex<common_type_t<T, NonComplex>>
 *	pow(const NonComplex& x, const complex<T>& y);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/pow.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace pow_test
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

template <typename T1, typename T2>
void test()
{
	using CT = hamon::common_type_t<T1, T2>;

	static_assert(hamon::is_same<decltype(hamon::pow(hamon::complex<T1>{}, hamon::complex<T1>{})), hamon::complex<T1>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::pow(hamon::complex<T1>{}, T1{})), hamon::complex<T1>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::pow(T1{}, hamon::complex<T1>{})), hamon::complex<T1>>::value, "");

	static_assert(hamon::is_same<decltype(hamon::pow(hamon::complex<T1>{}, hamon::complex<T2>{})), hamon::complex<CT>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::pow(hamon::complex<T1>{}, T2{})), hamon::complex<CT>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::pow(T1{}, hamon::complex<T2>{})), hamon::complex<CT>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::pow(hamon::complex<T1>{}, int{})), hamon::complex<hamon::common_type_t<T1, int>>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::pow(int{}, hamon::complex<T2>{})), hamon::complex<hamon::common_type_t<int, T2>>>::value, "");

	HAMON_CXX11_CONSTEXPR double error = get_error<CT>();
	HAMON_CXX11_CONSTEXPR double error1 = get_error<T1>();
	HAMON_CXX11_CONSTEXPR double error2 = get_error<T2>();
	
#if defined(HAMON_USE_STD_COMPLEX)

	{
		auto x = hamon::pow(hamon::complex<T1>(1, 2), hamon::complex<T2>(3, 4));
		EXPECT_NEAR(0.12900959407446694,  (double)x.real(), error);
		EXPECT_NEAR(0.033924092905170011, (double)x.imag(), error);
	}
	{
		auto x = hamon::pow(hamon::complex<T1>(-1.0, +0.0), T2{0.5});
		EXPECT_NEAR( 0.0, (double)x.real(), error);
		EXPECT_NEAR( 1.0, (double)x.imag(), error);
	}
	//{
	//	auto x = hamon::pow(hamon::complex<T1>(-1.0, -0.0), T2{0.5});
	//	EXPECT_NEAR( 0.0, (double)x.real(), error);
	//	EXPECT_NEAR(-1.0, (double)x.imag(), error);
	//}
	{
		auto x = hamon::pow(T1{2}, hamon::complex<T2>{-3, 4});
		EXPECT_NEAR(-0.11658588460450894,  (double)x.real(), error);
		EXPECT_NEAR( 0.045085823836147648, (double)x.imag(), error);
	}
	{
		auto x = hamon::pow(hamon::complex<T1>(1, 2), int{2});
		EXPECT_NEAR(-3.0, (double)x.real(), error1);
		EXPECT_NEAR( 4.0, (double)x.imag(), error1);
	}
	{
		auto x = hamon::pow(int{3}, hamon::complex<T2>{1.5, 2.5});
		EXPECT_NEAR(-4.7959069906319129, (double)x.real(), error2);
		EXPECT_NEAR( 1.9998190261141024, (double)x.imag(), error2);
	}

	EXPECT_EQ(
		hamon::pow(hamon::complex<T1>(1, 2), hamon::complex<T2>(3, 0)),
		hamon::pow(hamon::complex<T1>(1, 2), T2(3)));

	EXPECT_EQ(
		hamon::pow(hamon::complex<T1>(2, 0), hamon::complex<T2>(3, 4)),
		hamon::pow(T1(2),                    hamon::complex<T2>(3, 4)));

#else

	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::pow(hamon::complex<T1>(1, 2), hamon::complex<T2>(3, 4));
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.12900959407446694,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.033924092905170011, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::pow(hamon::complex<T1>(-1.0, +0.0), T2{0.5});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, (double)x.imag(), error);
	}
	//{
	//	HAMON_CXX11_CONSTEXPR auto x = hamon::pow(hamon::complex<T1>(-1.0, -0.0), T2{0.5});
	//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)x.real(), error);
	//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0, (double)x.imag(), error);
	//}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::pow(T1{2}, hamon::complex<T2>{-3, 4});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.11658588460450894,  (double)x.real(), error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.045085823836147648, (double)x.imag(), error);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::pow(hamon::complex<T1>(1, 2), int{2});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.0, (double)x.real(), error1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4.0, (double)x.imag(), error1);
	}
	{
		HAMON_CXX11_CONSTEXPR auto x = hamon::pow(int{3}, hamon::complex<T2>{1.5, 2.5});
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-4.7959069906319129, (double)x.real(), error2);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.9998190261141024, (double)x.imag(), error2);
	}

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
		hamon::pow(hamon::complex<T1>(1, 2), hamon::complex<T2>(3, 0)),
		hamon::pow(hamon::complex<T1>(1, 2), T2(3)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
		hamon::pow(hamon::complex<T1>(2, 0), hamon::complex<T2>(3, 4)),
		hamon::pow(T1(2),                    hamon::complex<T2>(3, 4)));

#endif
}

GTEST_TEST(ComplexTest, PowTest)
{
	test<float, float>();
	test<float, double>();
	test<float, long double>();
	test<double, float>();
	test<double, double>();
	test<double, long double>();
	test<long double, float>();
	test<long double, double>();
	test<long double, long double>();
}

}	// namespace pow_test

}	// namespace hamon_complex_test
