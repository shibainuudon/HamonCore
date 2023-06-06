/**
 *	@file	unit_test_complex_div_assign.cpp
 *
 *	@brief	除算代入演算子のテスト
 *
 *	template<class X> constexpr complex& operator/=(const complex<X>& rhs);
 *	constexpr complex& operator/=(const T& rhs);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace div_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename X>
inline HAMON_CXX14_CONSTEXPR bool test()
{
	// complex /= complex
	{
		hamon::complex<T> c{-11.5, 3.5};
		VERIFY(c.real() == -11.5);
		VERIFY(c.imag() ==   3.5);

		c /= hamon::complex<X>{1, 1};
		VERIFY(c.real() == -4.0);
		VERIFY(c.imag() ==  7.5);

		hamon::complex<X> const c2{2, 0.5};
		auto& r = (c /= c2);
		static_assert(hamon::is_same<decltype(r), hamon::complex<T>&>::value, "");
		VERIFY(&r == &c);
		VERIFY(c.real() == -1.0);
		VERIFY(c.imag() ==  4.0);
	}

	// complex /= scalar
	{
		hamon::complex<T> c{1,2};
		VERIFY(c.real() == 1.0);
		VERIFY(c.imag() == 2.0);

		c /= X(2);
		VERIFY(c.real() == 0.5);
		VERIFY(c.imag() == 1.0);

		auto& r = (c /= X(-2.0));
		static_assert(hamon::is_same<decltype(r), hamon::complex<T>&>::value, "");
		VERIFY(&r == &c);
		VERIFY(c.real() == -0.25);
		VERIFY(c.imag() == -0.5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ComplexTest, DivAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, long double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, long double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long double, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long double, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long double, long double>()));
}

}	// namespace div_assign_test

}	// namespace hamon_complex_test
