﻿/**
 *	@file	unit_test_iterator_crbegin.cpp
 *
 *	@brief	crbegin のテスト
 */

#include <hamon/iterator/crbegin.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, CRBeginTest)
{
	{
		std::vector<float> v;
		{
			auto it = hamon::crbegin(v);
			(void)it;
		}
	}
	{
		std::list<int> l;
		{
			auto it = hamon::crbegin(l);
			(void)it;
		}
	}

	HAMON_STATIC_CONSTEXPR int a[] = {0,1,2};
	HAMON_STATIC_CONSTEXPR std::array<float, 2> a2{{0.5f, 1.5f}};
	std::vector<float> v {3, 1, 4, 1, 5};
	std::list<int> l {6, 7, 8};

	EXPECT_TRUE(&*hamon::crbegin(a) == &a[2]);
	EXPECT_TRUE(hamon::crbegin(a2) == a2.crbegin());
	EXPECT_TRUE(hamon::crbegin(v) == v.crbegin());
	EXPECT_TRUE(hamon::crbegin(l) == l.crbegin());

	{
		auto it = hamon::crbegin(a);
		EXPECT_EQ(2, *it);
	}
	{
		auto it = hamon::crbegin(a2);
		EXPECT_EQ(1.5f, *it);
	}
	{
		auto it = hamon::crbegin(v);
		EXPECT_EQ(5, *it);
	}
	{
		auto it = hamon::crbegin(l);
		EXPECT_EQ(8, *it);
	}
}