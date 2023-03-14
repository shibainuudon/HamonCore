/**
 *	@file	unit_test_array_data.cpp
 *
 *	@brief	data() のテスト
 *
 *	constexpr T* data() noexcept;
 *	constexpr T const* data() const noexcept;
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

namespace data_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool DataTest()
{
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0>>().data()), T*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1>>().data()), T*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2>>().data()), T*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3>>().data()), T*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 0> const>().data()), T const*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 1> const>().data()), T const*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 2> const>().data()), T const*>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<hamon::array<T, 3> const>().data()), T const*>::value, "");

	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 0>>().data());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 1>>().data());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 2>>().data());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 3>>().data());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 0> const>().data());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 1> const>().data());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 2> const>().data());
	HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<hamon::array<T, 3> const>().data());

	{
		hamon::array<T, 3> a{ T(1), T(2), T(3) };
		T* p = a.data();
		VERIFY(T(1) == p[0]);
		VERIFY(T(2) == p[1]);
		VERIFY(T(3) == p[2]);
	}
	{
		hamon::array<T, 4> a{ T(13), T(14), T(15), T(16) };
		T* p = a.data();
		VERIFY(T(13) == p[0]);
		VERIFY(T(14) == p[1]);
		VERIFY(T(15) == p[2]);
		VERIFY(T(16) == p[3]);
	}
	{
		hamon::array<T, 3> const a{ T(1), T(2), T(3) };
		T const* p = a.data();
		VERIFY(T(1) == p[0]);
		VERIFY(T(2) == p[1]);
		VERIFY(T(3) == p[2]);
	}
	{
		hamon::array<T, 4> const a{ T(13), T(14), T(15), T(16) };
		T const* p = a.data();
		VERIFY(T(13) == p[0]);
		VERIFY(T(14) == p[1]);
		VERIFY(T(15) == p[2]);
		VERIFY(T(16) == p[3]);
	}
	{
		hamon::array<T, 0> a{};
		T* p = a.data();
		(void)p;
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a{};
		HAMON_CXX11_CONSTEXPR T const* p = a.data();
		(void)p;
	}

	return true;
}

GTEST_TEST(ArrayTest, DataTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<double>());
}

}	// namespace data_test

}	// namespace hamon_array_test
