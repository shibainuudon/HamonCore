/**
 *	@file	unit_test_complex_proj.cpp
 *
 *	@brief	proj関数のテスト
 *
 *	template<class T> complex<T> proj(const complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/complex/proj.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace proj_test
{

template <typename T>
void test()
{
	static_assert(hamon::is_same<decltype(hamon::proj(hamon::complex<T>{})), hamon::complex<T>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::proj(T{})), hamon::complex<T>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::proj(int{})), hamon::complex<double>>::value, "");

	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

#if defined(HAMON_USE_STD_COMPLEX)

	EXPECT_EQ(hamon::complex<T>(0, 0), hamon::proj(hamon::complex<T>{0, 0}));
	EXPECT_EQ(hamon::complex<T>(-1, 2), hamon::proj(hamon::complex<T>{-1, 2}));
	EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(hamon::complex<T>{inf, 0}));
	EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(hamon::complex<T>{-inf, 1}));
	EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(hamon::complex<T>{-2, inf}));
	EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(hamon::complex<T>{3, -inf}));

	EXPECT_EQ(hamon::complex<T>( 0, 0), hamon::proj(T{ 0}));
	EXPECT_EQ(hamon::complex<T>( 1, 0), hamon::proj(T{ 1}));
	EXPECT_EQ(hamon::complex<T>(-2, 0), hamon::proj(T{-2}));
	EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(T{inf}));
	EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(T{-inf}));

	EXPECT_EQ(hamon::complex<double>( 0, 0), hamon::proj(int{ 0}));
	EXPECT_EQ(hamon::complex<double>( 1, 0), hamon::proj(int{ 1}));
	EXPECT_EQ(hamon::complex<double>(-2, 0), hamon::proj(int{-2}));

#else

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(0, 0), hamon::proj(hamon::complex<T>{0, 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(-1, 2), hamon::proj(hamon::complex<T>{-1, 2}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(hamon::complex<T>{inf, 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(hamon::complex<T>{-inf, 1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(hamon::complex<T>{-2, inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(hamon::complex<T>{3, -inf}));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>( 0, 0), hamon::proj(T{ 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>( 1, 0), hamon::proj(T{ 1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(-2, 0), hamon::proj(T{-2}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(T{inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<T>(inf, 0), hamon::proj(T{-inf}));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<double>( 0, 0), hamon::proj(int{ 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<double>( 1, 0), hamon::proj(int{ 1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(hamon::complex<double>(-2, 0), hamon::proj(int{-2}));

#endif
}

GTEST_TEST(ComplexTest, ProjTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace proj_test

}	// namespace hamon_complex_test
