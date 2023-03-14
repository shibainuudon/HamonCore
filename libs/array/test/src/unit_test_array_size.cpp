/**
 *	@file	unit_test_array_size.cpp
 *
 *	@brief	constexpr size_type size() const noexcept のテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace size_test
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
void SizeTest()
{
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, a.size());
		static_assert(hamon::is_same<decltype(a.size()), typename hamon::array<T, 0>::size_type>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 1> a{T()};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, a.size());
		static_assert(hamon::is_same<decltype(a.size()), typename hamon::array<T, 0>::size_type>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 2> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, a.size());
		static_assert(hamon::is_same<decltype(a.size()), typename hamon::array<T, 0>::size_type>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.size());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a{T(), T()};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, a.size());
		static_assert(hamon::is_same<decltype(a.size()), typename hamon::array<T, 0>::size_type>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.size());
	}
}

GTEST_TEST(ArrayTest, SizeTest)
{
	SizeTest<char>();
	SizeTest<int>();
	SizeTest<float>();
	SizeTest<double>();
	SizeTest<Empty>();
	SizeTest<Trivial>();
	SizeTest<NonTrivial>();
}

}	// namespace size_test

}	// namespace hamon_array_test
