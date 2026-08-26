/**
 *	@file	unit_test_complex_abs.cpp
 *
 *	@brief	abs関数のテスト
 *
 *	template<class T> T abs(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/abs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace abs_test
{

template <typename T>
void test()
{
	static_assert(hamon::is_same<decltype(hamon::abs(hamon::complex<T>{})), T>::value, "");

	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> x{3, 4};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5.0, hamon::abs(x));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::complex<T> x{12, 5};
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(13.0, (double)hamon::abs(x), 1e-14);
	}
}

GTEST_TEST(ComplexTest, AbsTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace abs_test

}	// namespace hamon_complex_test
