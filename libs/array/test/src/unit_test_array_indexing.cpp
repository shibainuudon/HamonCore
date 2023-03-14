/**
 *	@file	unit_test_array_indexing.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr reference operator[](size_type n);
 *	constexpr const_reference operator[](size_type n) const;
 */

#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace indexing_test
{

template <typename T>
void IndexingTest()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0>>()[hamon::declval<hamon::size_t>()]), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1>>()[hamon::declval<hamon::size_t>()]), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2>>()[hamon::declval<hamon::size_t>()]), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3>>()[hamon::declval<hamon::size_t>()]), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0> const>()[hamon::declval<hamon::size_t>()]), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1> const>()[hamon::declval<hamon::size_t>()]), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2> const>()[hamon::declval<hamon::size_t>()]), T const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3> const>()[hamon::declval<hamon::size_t>()]), T const&>::value, "");

#if !defined(HAMON_USE_STD_ARRAY)
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 0>>()[hamon::declval<hamon::size_t>()]);
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 1>>()[hamon::declval<hamon::size_t>()]);
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 2>>()[hamon::declval<hamon::size_t>()]);
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 3>>()[hamon::declval<hamon::size_t>()]);
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 0> const>()[hamon::declval<hamon::size_t>()]);
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 1> const>()[hamon::declval<hamon::size_t>()]);
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 2> const>()[hamon::declval<hamon::size_t>()]);
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 3> const>()[hamon::declval<hamon::size_t>()]);
#endif

	{
		hamon::array<T, 3> a{ T(1), T(2), T(3) };
		EXPECT_EQ(T(1), a[0]);
		EXPECT_EQ(T(2), a[1]);
		EXPECT_EQ(T(3), a[2]);
	}
	{
		hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		EXPECT_EQ(T(13), a[0]);
		EXPECT_EQ(T(14), a[1]);
		EXPECT_EQ(T(15), a[2]);
		EXPECT_EQ(T(16), a[3]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a{ T(1), T(2), T(3) };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(1), a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2), a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(3), a[2]);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(13), a[0]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(14), a[1]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(15), a[2]);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(16), a[3]);
	}
}

GTEST_TEST(ArrayTest, IndexingTest)
{
	IndexingTest<char>();
	IndexingTest<int>();
	IndexingTest<float>();
	IndexingTest<double>();
}

}	// namespace indexing_test

}	// namespace hamon_array_test
