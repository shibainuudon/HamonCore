/**
 *	@file	unit_test_iterator_rbegin.cpp
 *
 *	@brief	rbegin のテスト
 */

#include <hamon/iterator/rbegin.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, RBeginTest)
{
	{
		std::vector<float> v;
		{
			auto it = hamon::rbegin(v);
			(void)it;
		}
	}
	{
		std::list<int> l;
		{
			auto it = hamon::rbegin(l);
			(void)it;
		}
	}

	HAMON_STATIC_CONSTEXPR int a[] = {0,1,2};
	HAMON_STATIC_CONSTEXPR hamon::array<float, 2> a2{{0.5f, 1.5f}};
	std::vector<float> v {3, 1, 4, 1, 5};
	std::list<int> l {6, 7, 8};

	EXPECT_TRUE(&*hamon::rbegin(a) == &a[2]);
	EXPECT_TRUE(hamon::rbegin(a2) == a2.rbegin());
	EXPECT_TRUE(hamon::rbegin(v) == v.rbegin());
	EXPECT_TRUE(hamon::rbegin(l) == l.rbegin());

	{
		auto it = hamon::rbegin(a);
		EXPECT_EQ(2, *it);
	}
	{
		auto it = hamon::rbegin(a2);
		EXPECT_EQ(1.5f, *it);
	}
	{
		auto it = hamon::rbegin(v);
		EXPECT_EQ(5, *it);
	}
	{
		auto it = hamon::rbegin(l);
		EXPECT_EQ(8, *it);
	}
}
