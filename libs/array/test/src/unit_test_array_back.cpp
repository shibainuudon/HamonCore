/**
 *	@file	unit_test_array_back.cpp
 *
 *	@brief	back() のテスト
 *
 *	constexpr reference back();
 *	constexpr const_reference back() const;
 */

#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace back_test
{

template <typename T>
void BackTest()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0>>().back()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1>>().back()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2>>().back()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3>>().back()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0> const>().back()), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1> const>().back()), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2> const>().back()), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3> const>().back()), T const&>::value, "");

#if !defined(HAMON_USE_STD_ARRAY)
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 0>>().back());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 1>>().back());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 2>>().back());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 3>>().back());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 0> const>().back());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 1> const>().back());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 2> const>().back());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 3> const>().back());
#endif

	{
		hamon::array<T, 3> a{ T(1), T(2), T(3) };
		EXPECT_EQ(T(3), a.back());
	}
	{
		hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		EXPECT_EQ(T(16), a.back());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a{ T(1), T(2), T(3) };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3), a.back());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(16), a.back());
	}
}

GTEST_TEST(ArrayTest, BackTest)
{
	BackTest<char>();
	BackTest<int>();
	BackTest<float>();
	BackTest<double>();
}

}	// namespace back_test

}	// namespace hamon_array_test
