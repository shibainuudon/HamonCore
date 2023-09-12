/**
 *	@file	unit_test_iterator_ssize.cpp
 *
 *	@brief	ssize のテスト
 */

#include <hamon/iterator/ssize.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, SSizeTest)
{
	{
		HAMON_CONSTEXPR int a[3] {};
		static_assert(hamon::is_signed<decltype(hamon::ssize(a))>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, hamon::ssize(a));
	}
	{
		HAMON_CONSTEXPR float a[4] {};
		static_assert(hamon::is_signed<decltype(hamon::ssize(a))>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, hamon::ssize(a));
	}
	{
		std::vector<int> a{};
		static_assert(hamon::is_signed<decltype(hamon::ssize(a))>::value, "");
		EXPECT_EQ(0, hamon::ssize(a));
		a.push_back(10);
		EXPECT_EQ(1, hamon::ssize(a));
		a.push_back(20);
		EXPECT_EQ(2, hamon::ssize(a));
	}
	{
		HAMON_CONSTEXPR hamon::array<char, 5> a {};
		static_assert(hamon::is_signed<decltype(hamon::ssize(a))>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, hamon::ssize(a));
	}
	{
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, hamon::ssize({1,2,3}));
		static_assert(hamon::is_signed<decltype(hamon::ssize({1,2,3}))>::value, "");
	}
}
