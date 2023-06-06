/**
 *	@file	unit_test_complex_arg.cpp
 *
 *	@brief	arg関数のテスト
 *
 *	template<class T> T arg(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/arg.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace hamon_complex_test
{

namespace arg_test
{

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 1e-7;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 1e-30;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-30;
}

template <typename T>
void test()
{
	static_assert(hamon::is_same<decltype(hamon::arg(hamon::complex<T>{})), T>::value, "");
	static_assert(hamon::is_same<decltype(hamon::arg(T{})), T>::value, "");
	static_assert(hamon::is_same<decltype(hamon::arg(int{})), double>::value, "");

#if defined(HAMON_USE_STD_COMPLEX)

	EXPECT_EQ(0.0, hamon::arg(hamon::complex<T>{0, 0}));
	EXPECT_EQ(0.0, hamon::arg(hamon::complex<T>{1, 0}));
	EXPECT_NEAR( 1.5707963267948966, (double)hamon::arg(hamon::complex<T>{ 0,  1}), get_error<T>());
	EXPECT_NEAR( 0.78539816339744828,(double)hamon::arg(hamon::complex<T>{ 1,  1}), get_error<T>());
	EXPECT_NEAR( 3.1415926535897931, (double)hamon::arg(hamon::complex<T>{-1,  0}), get_error<T>());
	EXPECT_NEAR(-1.5707963267948966, (double)hamon::arg(hamon::complex<T>{ 0, -1}), get_error<T>());
	EXPECT_NEAR(-2.3561944901923448, (double)hamon::arg(hamon::complex<T>{-1, -1}), get_error<T>());

	EXPECT_EQ(0.0, hamon::arg(T{0}));
	EXPECT_EQ(0.0, hamon::arg(T{1}));
	EXPECT_EQ(0.0, hamon::arg(T{2}));
	EXPECT_NEAR(3.1415926535897931, (double)hamon::arg(T{-1}), get_error<T>());
	EXPECT_NEAR(3.1415926535897931, (double)hamon::arg(T{-2}), get_error<T>());

	EXPECT_EQ(0.0, hamon::arg(int{0}));
	EXPECT_EQ(0.0, hamon::arg(int{1}));
	EXPECT_EQ(0.0, hamon::arg(int{2}));
	EXPECT_NEAR(3.1415926535897931, (double)hamon::arg(int{-1}), get_error<T>());
	EXPECT_NEAR(3.1415926535897931, (double)hamon::arg(int{-2}), get_error<T>());

#else

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::arg(hamon::complex<T>{0, 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::arg(hamon::complex<T>{1, 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267948966, (double)hamon::arg(hamon::complex<T>{ 0,  1}), get_error<T>());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.78539816339744828,(double)hamon::arg(hamon::complex<T>{ 1,  1}), get_error<T>());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.1415926535897931, (double)hamon::arg(hamon::complex<T>{-1,  0}), get_error<T>());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267948966, (double)hamon::arg(hamon::complex<T>{ 0, -1}), get_error<T>());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.3561944901923448, (double)hamon::arg(hamon::complex<T>{-1, -1}), get_error<T>());

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::arg(T{0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::arg(T{1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::arg(T{2}));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.1415926535897931, (double)hamon::arg(T{-1}), get_error<T>());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.1415926535897931, (double)hamon::arg(T{-2}), get_error<T>());

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::arg(int{0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::arg(int{1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::arg(int{2}));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.1415926535897931, (double)hamon::arg(int{-1}), get_error<T>());
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.1415926535897931, (double)hamon::arg(int{-2}), get_error<T>());

#endif
}

GTEST_TEST(ComplexTest, ArgTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace arg_test

}	// namespace hamon_complex_test
