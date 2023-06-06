/**
 *	@file	unit_test_complex_assign_scalar.cpp
 *
 *	@brief	スカラーの代入演算子のテスト
 *
 *	constexpr complex& operator=(const T&);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace assign_scalar_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename X>
inline HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::complex<T> c;
	VERIFY(c.real() == 0.0);
	VERIFY(c.imag() == 0.0);

	c = X(1.5);
	VERIFY(c.real() == 1.5);
	VERIFY(c.imag() == 0.0);

	auto& r = (c = X(-2.5));
	static_assert(hamon::is_same<decltype(r), hamon::complex<T>&>::value, "");
	VERIFY(&r == &c);
	VERIFY(c.real() == -2.5);
	VERIFY(c.imag() ==  0.0);

	return true;
}

#undef VERIFY

GTEST_TEST(ComplexTest, AssignScalarTest)
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

}	// namespace assign_scalar_test

}	// namespace hamon_complex_test
