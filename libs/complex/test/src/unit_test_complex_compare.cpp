/**
 *	@file	unit_test_complex_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T> constexpr bool operator==(const complex<T>& lhs, const complex<T>& rhs);
 *	template<class T> constexpr bool operator==(const complex<T>& lhs, const T& rhs);
 *
 *	// 上記2つから以下が自動導出される
 *	template<class T> constexpr bool operator==(const T& lhs, const complex<T>& rhs);
 *	template<class T> constexpr bool operator!=(const complex<T>& lhs, const complex<T>& rhs);
 *	template<class T> constexpr bool operator!=(const complex<T>& lhs, const T& rhs);
 *	template<class T> constexpr bool operator!=(const T& lhs, const complex<T>& rhs);
 */

#include <hamon/complex/complex.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace compare_test
{

template <typename T>
void test()
{
	// complex == complex
	// complex != complex
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{1.5, 2.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{1.5, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs != rhs);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{1.5,  2.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{1.5, -2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs != rhs);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{1.5, 2.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{2.5, 2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs != rhs);
	}

	// complex == scalar
	// complex != scalar
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{1.5, 0.0};
		HAMON_CXX11_CONSTEXPR T rhs{1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs != rhs);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{1.5, 0.0};
		HAMON_CXX11_CONSTEXPR T rhs{2.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs != rhs);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{0.0, 1.5};
		HAMON_CXX11_CONSTEXPR T rhs{1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs != rhs);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> lhs{1.5, 1.5};
		HAMON_CXX11_CONSTEXPR T rhs{1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs != rhs);
	}

	// scalar == complex
	// scalar != complex
	{
		HAMON_CXX11_CONSTEXPR T lhs{1.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{1.5, 0.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs != rhs);
	}
	{
		HAMON_CXX11_CONSTEXPR T lhs{2.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{1.5, 0.0};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs != rhs);
	}
	{
		HAMON_CXX11_CONSTEXPR T lhs{1.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{0.0, 1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs != rhs);
	}
	{
		HAMON_CXX11_CONSTEXPR T lhs{1.5};
		HAMON_CXX11_CONSTEXPR hamon::complex<T> rhs{1.5, 1.5};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(lhs == rhs);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (lhs != rhs);
	}
}

GTEST_TEST(ComplexTest, CompareTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace compare_test

}	// namespace hamon_complex_test
