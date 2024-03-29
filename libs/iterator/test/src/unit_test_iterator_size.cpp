﻿/**
 *	@file	unit_test_iterator_size.cpp
 *
 *	@brief	size のテスト
 */

#include <hamon/iterator/size.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, SizeTest)
{
	{
		HAMON_CONSTEXPR int a[3] {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, hamon::size(a));
	}
	{
		HAMON_CONSTEXPR float a[4] {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, hamon::size(a));
	}
	{
		hamon::vector<int> a{};
		EXPECT_EQ(0u, hamon::size(a));
		a.push_back(10);
		EXPECT_EQ(1u, hamon::size(a));
		a.push_back(20);
		EXPECT_EQ(2u, hamon::size(a));
	}
	{
		HAMON_CONSTEXPR hamon::array<char, 5> a {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, hamon::size(a));
	}
	{
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3u, hamon::size({1,2,3}));
	}
}
