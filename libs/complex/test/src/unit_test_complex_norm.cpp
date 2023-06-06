/**
 *	@file	unit_test_complex_norm.cpp
 *
 *	@brief	norm関数のテスト
 *
 *	template<class T> constexpr T norm(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/norm.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace norm_test
{

template <typename T>
void test()
{
	static_assert(hamon::is_same<decltype(hamon::norm(hamon::complex<T>{})), T>::value, "");
	static_assert(hamon::is_same<decltype(hamon::norm(T{})), T>::value, "");
	static_assert(hamon::is_same<decltype(hamon::norm(int{})), double>::value, "");

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::norm(hamon::complex<T>{ 0,  0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5.0, hamon::norm(hamon::complex<T>{ 1,  2}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(13.0, hamon::norm(hamon::complex<T>{-2,  3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16.0, hamon::norm(hamon::complex<T>{ 4,  0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(25.0, hamon::norm(hamon::complex<T>{ 0, -5}));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::norm(T{  0 }));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::norm(T{  1 }));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0, hamon::norm(T{ -2 }));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::norm(int{  0 }));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::norm(int{  1 }));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4.0, hamon::norm(int{ -2 }));
}

GTEST_TEST(ComplexTest, NormTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace norm_test

}	// namespace hamon_complex_test
