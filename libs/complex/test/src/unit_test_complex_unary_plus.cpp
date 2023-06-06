/**
 *	@file	unit_test_complex_unary_plus.cpp
 *
 *	@brief	単項+演算子のテスト
 *
 *	template<class T> constexpr complex<T> operator+(const complex<T>& lhs);
 */

#include <hamon/complex/complex.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace unary_plus_test
{

template <typename T>
void test()
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((+hamon::complex<T>{ 1.5, -2.5} == hamon::complex<T>{ 1.5, -2.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((+hamon::complex<T>{-2.5,  3.5} == hamon::complex<T>{-2.5,  3.5}));
}

GTEST_TEST(ComplexTest, UnaryPlusTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace unary_plus_test

}	// namespace hamon_complex_test
