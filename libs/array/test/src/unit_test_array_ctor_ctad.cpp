/**
 *	@file	unit_test_array_ctor_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_array_test
{

namespace ctor_ctad_test
{

template <typename T>
void CtorCTADTest()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

	// explicit deduction guide
	{
		hamon::array a{T(42)};
		static_assert(hamon::is_same<decltype(a), hamon::array<T, 1>>::value, "");
		EXPECT_EQ(T(42), a[0]);
	}
	{
		hamon::array a{T(1),T(2)};
		static_assert(hamon::is_same<decltype(a), hamon::array<T, 2>>::value, "");
		EXPECT_EQ(T(1), a[0]);
		EXPECT_EQ(T(2), a[1]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array a{T(42)};
		static_assert(hamon::is_same<decltype(a), hamon::array<T, 1> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(42), a[0]);
	}
	{
		HAMON_CXX11_CONSTEXPR T x(2);
		HAMON_CXX11_CONSTEXPR hamon::array a{T(1),x,T(3)};
		static_assert(hamon::is_same<decltype(a), hamon::array<T, 3> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3), a[2]);
	}

	// implicit deduction guide
	{
		hamon::array<T, 2> a1{T(4), T(5)};
		hamon::array a2(a1);
		static_assert(hamon::is_same<decltype(a1), decltype(a2)>::value, "");
		EXPECT_EQ(T(4), a2[0]);
		EXPECT_EQ(T(5), a2[1]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a1{T(3), T(4), T(5)};
		HAMON_CXX11_CONSTEXPR hamon::array a2(a1);
		static_assert(hamon::is_same<decltype(a1), decltype(a2)>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3), a2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(4), a2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(5), a2[2]);
	}

#endif
}

GTEST_TEST(ArrayTest, CtorCTADTest)
{
	CtorCTADTest<char>();
	CtorCTADTest<int>();
	CtorCTADTest<float>();
	CtorCTADTest<double>();
}

}	// namespace ctor_ctad_test

}	// namespace hamon_array_test
