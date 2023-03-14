/**
 *	@file	unit_test_array_max_size.cpp
 *
 *	@brief	constexpr size_type max_size() const noexcept のテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace max_size_test
{

struct Empty {};

struct Trivial { int i; int j; };

struct NonTrivial
{
	int i;
	int j;
	HAMON_CXX11_CONSTEXPR NonTrivial()
		: i(42), j(13) {}
};

template <typename T>
void MaxSizeTest()
{
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, a.max_size());
		static_assert(hamon::is_same<decltype(a.max_size()), typename hamon::array<T, 0>::size_type>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.max_size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 1> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, a.max_size());
		static_assert(hamon::is_same<decltype(a.max_size()), typename hamon::array<T, 0>::size_type>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.max_size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 2> a{T()};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, a.max_size());
		static_assert(hamon::is_same<decltype(a.max_size()), typename hamon::array<T, 0>::size_type>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.max_size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a{T(), T(), T()};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.max_size());
		static_assert(hamon::is_same<decltype(a.max_size()), typename hamon::array<T, 0>::size_type>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.max_size());
	}
}

GTEST_TEST(ArrayTest, MaxSizeTest)
{
	MaxSizeTest<char>();
	MaxSizeTest<int>();
	MaxSizeTest<float>();
	MaxSizeTest<double>();
	MaxSizeTest<Empty>();
	MaxSizeTest<Trivial>();
	MaxSizeTest<NonTrivial>();
}

}	// namespace max_size_test

}	// namespace hamon_array_test
