/**
 *	@file	unit_test_iterator_crend.cpp
 *
 *	@brief	crend のテスト
 */

#include <hamon/iterator/crend.hpp>
#include <hamon/iterator/crbegin.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, CREndTest)
{
	{
		std::vector<float> v;
		{
			auto it1 = hamon::crbegin(v);
			auto it2 = hamon::crend(v);
			EXPECT_TRUE(it1 == it2);
		}
	}
	{
		std::list<int> l;
		{
			auto it1 = hamon::crbegin(l);
			auto it2 = hamon::crend(l);
			EXPECT_TRUE(it1 == it2);
		}
	}

	HAMON_STATIC_CONSTEXPR int a[] = {0,1,2};
	HAMON_STATIC_CONSTEXPR std::array<float, 2> a2{{0.5f, 1.5f}};
	std::vector<float> v {3,1,4,1,5};
	std::list<int> l {6, 7, 8};

//	EXPECT_TRUE(&*hamon::crend(a) == &a[-1]);
	EXPECT_TRUE(hamon::crend(a2) == a2.crend());
	EXPECT_TRUE(hamon::crend(v) == v.crend());
	EXPECT_TRUE(hamon::crend(l) == l.crend());

	{
		auto it = hamon::crbegin(a);
		EXPECT_TRUE(it != hamon::crend(a));
		++it;
		EXPECT_TRUE(it != hamon::crend(a));
		++it;
		EXPECT_TRUE(it != hamon::crend(a));
		++it;
		EXPECT_TRUE(it == hamon::crend(a));
	}
	{
		auto it = hamon::crbegin(a2);
		EXPECT_TRUE(it != hamon::crend(a2));
		++it;
		EXPECT_TRUE(it != hamon::crend(a2));
		++it;
		EXPECT_TRUE(it == hamon::crend(a2));
	}
	{
		auto it = hamon::crbegin(v);
		EXPECT_TRUE(it != hamon::crend(v));
		++it;
		EXPECT_TRUE(it != hamon::crend(v));
		++it;
		EXPECT_TRUE(it != hamon::crend(v));
		++it;
		EXPECT_TRUE(it != hamon::crend(v));
		++it;
		EXPECT_TRUE(it != hamon::crend(v));
		++it;
		EXPECT_TRUE(it == hamon::crend(v));
	}
	{
		auto it = hamon::crbegin(l);
		EXPECT_TRUE(it != hamon::crend(l));
		++it;
		EXPECT_TRUE(it != hamon::crend(l));
		++it;
		EXPECT_TRUE(it != hamon::crend(l));
		++it;
		EXPECT_TRUE(it == hamon::crend(l));
	}
}
