/**
 *	@file	unit_test_array_front.cpp
 *
 *	@brief	front() のテスト
 *
 *	constexpr reference front();
 *	constexpr const_reference front() const;
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

namespace front_test
{

template <typename T>
void FrontTest()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0>>().front()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1>>().front()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2>>().front()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3>>().front()), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0> const>().front()), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1> const>().front()), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2> const>().front()), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3> const>().front()), T const&>::value, "");

#if !defined(HAMON_USE_STD_ARRAY)
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 0>>().front());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 1>>().front());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 2>>().front());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 3>>().front());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 0> const>().front());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 1> const>().front());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 2> const>().front());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 3> const>().front());
#endif

	{
		hamon::array<T, 3> a{ T(1), T(2), T(3) };
		EXPECT_EQ(T(1), a.front());
	}
	{
		hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		EXPECT_EQ(T(13), a.front());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a{ T(1), T(2), T(3) };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), a.front());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(13), a.front());
	}
}

GTEST_TEST(ArrayTest, FrontTest)
{
	FrontTest<char>();
	FrontTest<int>();
	FrontTest<float>();
	FrontTest<double>();
}

}	// namespace front_test

}	// namespace hamon_array_test
