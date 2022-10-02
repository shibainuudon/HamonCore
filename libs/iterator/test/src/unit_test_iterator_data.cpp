/**
 *	@file	unit_test_iterator_data.cpp
 *
 *	@brief	data のテスト
 */

#include <hamon/iterator/data.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, DataTest)
{
	{
		HAMON_CONSTEXPR int a[3] {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(&a[0], hamon::data(a));
	}
	{
		HAMON_CONSTEXPR float a[4] {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(&a[0], hamon::data(a));
	}
	{
		std::vector<int> a{};
		EXPECT_EQ(nullptr, hamon::data(a));
		a.push_back(10);
		EXPECT_EQ(&a[0], hamon::data(a));
		a.push_back(20);
		EXPECT_EQ(&a[0], hamon::data(a));
	}
	{
		HAMON_CONSTEXPR std::array<char, 5> a {};
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(&a[0], hamon::data(a));
	}
	{
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(1, *hamon::data({1,2,3}));
	}
}
