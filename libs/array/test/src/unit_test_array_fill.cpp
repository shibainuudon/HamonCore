/**
 *	@file	unit_test_array_fill.cpp
 *
 *	@brief	constexpr void fill(T const& u) のテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_array_test
{

namespace fill_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool FillTest()
{
	{
		hamon::array<T, 3> a{};
		a.fill(T(42));
		VERIFY(a.size() == 3u);
		VERIFY(a[0] == T(42));
		VERIFY(a[1] == T(42));
		VERIFY(a[2] == T(42));
	}
	{
		hamon::array<T, 5> a{T(1), T(2), T(3), T(4), T(5)};
		a.fill(T(43));
		VERIFY(a.size() == 5u);
		VERIFY(a[0] == T(43));
		VERIFY(a[1] == T(43));
		VERIFY(a[2] == T(43));
		VERIFY(a[3] == T(43));
		VERIFY(a[4] == T(43));
	}
	{
		hamon::array<T, 0> a{};
		a.fill(T(44));
		VERIFY(a.size() == 0u);
	}

	return true;
}

GTEST_TEST(ArrayTest, FillTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FillTest<char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FillTest<int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FillTest<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FillTest<double>());
}

}	// namespace fill_test

}	// namespace hamon_array_test
