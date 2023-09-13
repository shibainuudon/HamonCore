/**
 *	@file	unit_test_iterator_empty.cpp
 *
 *	@brief	empty のテスト
 */

#include <hamon/iterator/empty.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, EmptyTest)
{
	{
		HAMON_CONSTEXPR int a[3] {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::empty(a));
	}
	{
		HAMON_CONSTEXPR float a[4] {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::empty(a));
	}
	{
		hamon::vector<int> a{};
		EXPECT_EQ(true, hamon::empty(a));
		a.push_back(10);
		EXPECT_EQ(false, hamon::empty(a));
		a.push_back(20);
		EXPECT_EQ(false, hamon::empty(a));
	}
	{
		HAMON_CONSTEXPR hamon::array<char, 5> a {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::empty(a));
	}
	{
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(false, hamon::empty({1,2,3}));
	}
}
