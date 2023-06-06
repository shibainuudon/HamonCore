/**
 *	@file	unit_test_complex_conj.cpp
 *
 *	@brief	conj関数のテスト
 *
 *	template<class T> constexpr complex<T> conj(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/conj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace conj_test
{

template <typename T>
void test()
{
	static_assert(hamon::is_same<decltype(hamon::conj(hamon::complex<T>{})), hamon::complex<T>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::conj(T{})), hamon::complex<T>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::conj(int{})), hamon::complex<double>>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>( 0,  0), hamon::conj(hamon::complex<T>( 0,  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>( 1, -2), hamon::conj(hamon::complex<T>( 1,  2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(-3,  4), hamon::conj(hamon::complex<T>(-3, -4)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>( 0,  0), hamon::conj(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>( 1,  0), hamon::conj(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(-2,  0), hamon::conj(T(-2)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<double>( 0,  0), hamon::conj(int( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<double>(-1,  0), hamon::conj(int(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<double>( 2,  0), hamon::conj(int( 2)));
}

GTEST_TEST(ComplexTest, ConjTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace conj_test

}	// namespace hamon_complex_test
