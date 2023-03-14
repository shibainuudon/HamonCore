/**
 *	@file	unit_test_array_empty.cpp
 *
 *	@brief	[[nodiscard]] constexpr bool empty() const noexcept のテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace empty_test
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
void EmptyTest()
{
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 0> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true, a.empty());
		static_assert(hamon::is_same<decltype(a.empty()), bool>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 1> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
		static_assert(hamon::is_same<decltype(a.empty()), bool>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 2> a{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
		static_assert(hamon::is_same<decltype(a.empty()), bool>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.empty());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<T, 3> a{T(), T(), T()};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, a.empty());
		static_assert(hamon::is_same<decltype(a.empty()), bool>::value, "");
		HAMON_ASSERT_NOEXCEPT_TRUE(a.empty());
	}
}

GTEST_TEST(ArrayTest, EmptyTest)
{
	EmptyTest<char>();
	EmptyTest<int>();
	EmptyTest<float>();
	EmptyTest<double>();
	EmptyTest<Empty>();
	EmptyTest<Trivial>();
	EmptyTest<NonTrivial>();
}

}	// namespace empty_test

}	// namespace hamon_array_test
