/**
 *	@file	unit_test_array_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listからのコンストラクタのテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_array_test
{

namespace ctor_initializer_list_test
{

template <typename T>
void CtorInitializerListTest()
{
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a = {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(),  a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(),  a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(),  a[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a = {T(1)};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(),  a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(),  a[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a = {T(1), T(2)};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(),  a[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a = {T(1), T(2), T(3)};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.max_size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3), a[2]);
	}
}

GTEST_TEST(ArrayTest, CtorInitializerListTest)
{
	CtorInitializerListTest<char>();
	CtorInitializerListTest<int>();
	CtorInitializerListTest<float>();
	CtorInitializerListTest<double>();
}

}	// namespace ctor_initializer_list_test

}	// namespace hamon_array_test
