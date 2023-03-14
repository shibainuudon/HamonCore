/**
 *	@file	unit_test_array_to_array.cpp
 *
 *	@brief	to_array 関数のテスト
 *
 *	template <class T, size_t N>
 *	constexpr array<remove_cv_t<T>, N> to_array(T (&a)[N]);
 *
 *	template <class T, size_t N>
 *	constexpr array<remove_cv_t<T>, N> to_array(T (&&a)[N]);
 */

#include <hamon/array/to_array.hpp>
#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_array_test
{

namespace to_array_test
{

GTEST_TEST(ArrayTest, ToArrayTest)
{
	{
		HAMON_CXX11_CONSTEXPR auto a = hamon::to_array({1, 2, 3});
		static_assert(hamon::is_same<decltype(a), hamon::array<int, 3> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, a[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR auto a = hamon::to_array({4.0f, 5.0f, 6.0f, 7.0f});
		static_assert(hamon::is_same<decltype(a), hamon::array<float, 4> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4.0f, a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5.0f, a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6.0f, a[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7.0f, a[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR auto a = hamon::to_array("hello");
		static_assert(hamon::is_same<decltype(a), hamon::array<char, 6> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ('h', a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ('e', a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ('l', a[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ('l', a[3]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ('o', a[4]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ('\0', a[5]);
	}
	{
		HAMON_CXX11_CONSTEXPR int a1[] {2, 3, 4};
		HAMON_CXX11_CONSTEXPR auto a2 = hamon::to_array(a1);
		static_assert(hamon::is_same<decltype(a2), hamon::array<int, 3> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a2.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, a2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, a2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, a2[2]);
	}
	{
		int a1[] {2, 3, 4};
		auto a2 = hamon::to_array(a1);
		static_assert(hamon::is_same<decltype(a2), hamon::array<int, 3>>::value, "");
		EXPECT_EQ(3u, a2.size());
		EXPECT_EQ(2, a2[0]);
		EXPECT_EQ(3, a2[1]);
		EXPECT_EQ(4, a2[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR double a1[] {3, 4, 5, 6};
		HAMON_CXX11_CONSTEXPR auto a2 = hamon::to_array(a1);
		static_assert(hamon::is_same<decltype(a2), hamon::array<double, 4> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, a2.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, a2[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, a2[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, a2[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, a2[3]);
	}
	{
		double a1[] {3, 4, 5, 6};
		auto a2 = hamon::to_array(hamon::move(a1));
		static_assert(hamon::is_same<decltype(a2), hamon::array<double, 4>>::value, "");
		EXPECT_EQ(4u, a2.size());
		EXPECT_EQ(3, a2[0]);
		EXPECT_EQ(4, a2[1]);
		EXPECT_EQ(5, a2[2]);
		EXPECT_EQ(6, a2[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR auto a = hamon::to_array<long>({1, 2, 3});
		static_assert(hamon::is_same<decltype(a), hamon::array<long, 3> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, a[2]);
	}
	{
		double a1[] {3, 4, 5, 6};
		auto a2 = hamon::to_array<const double>(a1);
		static_assert(hamon::is_same<decltype(a2), hamon::array<double, 4>>::value, "");
		EXPECT_EQ(4u, a2.size());
		EXPECT_EQ(3, a2[0]);
		EXPECT_EQ(4, a2[1]);
		EXPECT_EQ(5, a2[2]);
		EXPECT_EQ(6, a2[3]);
	}
}

}	// namespace to_array_test

}	// namespace hamon_array_test
