/**
 *	@file	unit_test_array_at.cpp
 *
 *	@brief	at() のテスト
 *
 *	constexpr reference at(size_type n);
 *	constexpr const_reference at(size_type n) const;
 */

#include <hamon/array/array.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace at_test
{

template <typename T>
void AtTest()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0>>().at(hamon::declval<hamon::size_t>())), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1>>().at(hamon::declval<hamon::size_t>())), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2>>().at(hamon::declval<hamon::size_t>())), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3>>().at(hamon::declval<hamon::size_t>())), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0> const>().at(hamon::declval<hamon::size_t>())), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1> const>().at(hamon::declval<hamon::size_t>())), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2> const>().at(hamon::declval<hamon::size_t>())), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3> const>().at(hamon::declval<hamon::size_t>())), T const&>::value, "");

	HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::array<T, 0>>().at(hamon::declval<hamon::size_t>()));
	HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::array<T, 1>>().at(hamon::declval<hamon::size_t>()));
	HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::array<T, 2>>().at(hamon::declval<hamon::size_t>()));
	HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::array<T, 3>>().at(hamon::declval<hamon::size_t>()));
	HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::array<T, 0> const>().at(hamon::declval<hamon::size_t>()));
	HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::array<T, 1> const>().at(hamon::declval<hamon::size_t>()));
	HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::array<T, 2> const>().at(hamon::declval<hamon::size_t>()));
	HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<hamon::array<T, 3> const>().at(hamon::declval<hamon::size_t>()));

	{
		hamon::array<T, 3> a{ T(1), T(2), T(3) };
		EXPECT_EQ(T(1), a.at(0));
		EXPECT_EQ(T(2), a.at(1));
		EXPECT_EQ(T(3), a.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)a.at(3), hamon::out_of_range);
#endif
	}
	{
		hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		EXPECT_EQ(T(13), a.at(0));
		EXPECT_EQ(T(14), a.at(1));
		EXPECT_EQ(T(15), a.at(2));
		EXPECT_EQ(T(16), a.at(3));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)a.at(4), hamon::out_of_range);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a{ T(1), T(2), T(3) };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), a.at(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), a.at(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3), a.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)a.at(3), hamon::out_of_range);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(13), a.at(0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(14), a.at(1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(15), a.at(2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(16), a.at(3));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)a.at(4), hamon::out_of_range);
#endif
	}
}

GTEST_TEST(ArrayTest, AtTest)
{
	AtTest<char>();
	AtTest<int>();
	AtTest<float>();
	AtTest<double>();
}

}	// namespace at_test

}	// namespace hamon_array_test
