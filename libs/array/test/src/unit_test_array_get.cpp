/**
 *	@file	unit_test_array_get.cpp
 *
 *	@brief	get 関数のテスト
 *
 *	template <size_t I, class T, size_t N>
 *	constexpr T& get(array<T, N>& a) noexcept;
 *
 *	template <size_t I, class T, size_t N>
 *	constexpr T&& get(array<T, N>&& a) noexcept;
 *
 *	template <size_t I, class T, size_t N>
 *	constexpr const T& get(const array<T, N>& a) noexcept;
 *
 *	template <size_t I, class T, size_t N>
 *	constexpr const T&& get(const array<T, N>&& a) noexcept;
 */

#include <hamon/array/get.hpp>
#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_array_test
{

namespace get_test
{

GTEST_TEST(ArrayTest, GetTest)
{
	using std::get;

	// const lvalue reference
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 3> a = {1, 2, 3};
		static_assert(hamon::is_same<decltype(get<0>(a)), int const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, get<0>(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, get<1>(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, get<2>(a));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<double, 4> a = {3, 4, 5, 6};
		static_assert(hamon::is_same<decltype(get<0>(a)), double const&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, get<0>(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, get<1>(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, get<2>(a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, get<3>(a));
	}

	// const rvalue reference
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 3> a = {1, 2, 3};
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(a))), int const&&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, get<0>(hamon::move(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, get<1>(hamon::move(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, get<2>(hamon::move(a)));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<double, 4> a = {3, 4, 5, 6};
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(a))), double const&&>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, get<0>(hamon::move(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, get<1>(hamon::move(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, get<2>(hamon::move(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(6, get<3>(hamon::move(a)));
	}

	// lvalue reference
	{
		hamon::array<int, 3> a = {1, 2, 3};
		static_assert(hamon::is_same<decltype(get<0>(a)), int&>::value, "");
		EXPECT_EQ(1, get<0>(a));
		EXPECT_EQ(2, get<1>(a));
		EXPECT_EQ(3, get<2>(a));
		get<0>(a) = 99;
		EXPECT_EQ(99, get<0>(a));
		EXPECT_EQ( 2, get<1>(a));
		EXPECT_EQ( 3, get<2>(a));
	}
	{
		hamon::array<double, 4> a = {3, 4, 5, 6};
		static_assert(hamon::is_same<decltype(get<0>(a)), double&>::value, "");
		EXPECT_EQ(3, get<0>(a));
		EXPECT_EQ(4, get<1>(a));
		EXPECT_EQ(5, get<2>(a));
		EXPECT_EQ(6, get<3>(a));
		get<1>(a) = 42;
		EXPECT_EQ( 3, get<0>(a));
		EXPECT_EQ(42, get<1>(a));
		EXPECT_EQ( 5, get<2>(a));
		EXPECT_EQ( 6, get<3>(a));
	}

	// rvalue reference
	{
		hamon::array<int, 3> a = {1, 2, 3};
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(a))), int&&>::value, "");
		EXPECT_EQ(1, get<0>(hamon::move(a)));
		EXPECT_EQ(2, get<1>(hamon::move(a)));
		EXPECT_EQ(3, get<2>(hamon::move(a)));
	}
	{
		hamon::array<double, 4> a = {3, 4, 5, 6};
		static_assert(hamon::is_same<decltype(get<0>(hamon::move(a))), double&&>::value, "");
		EXPECT_EQ(3, get<0>(hamon::move(a)));
		EXPECT_EQ(4, get<1>(hamon::move(a)));
		EXPECT_EQ(5, get<2>(hamon::move(a)));
		EXPECT_EQ(6, get<3>(hamon::move(a)));
	}
}

}	// namespace get_test

}	// namespace hamon_array_test
