/**
 *	@file	unit_test_iterator_rend.cpp
 *
 *	@brief	rend のテスト
 */

#include <hamon/iterator/rend.hpp>
#include <hamon/iterator/rbegin.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, REndTest)
{
	{
		hamon::vector<float> v;
		{
			auto it1 = hamon::rbegin(v);
			auto it2 = hamon::rend(v);
			EXPECT_TRUE(it1 == it2);
		}
	}
	{
		hamon::list<int> l;
		{
			auto it1 = hamon::rbegin(l);
			auto it2 = hamon::rend(l);
			EXPECT_TRUE(it1 == it2);
		}
	}

	HAMON_STATIC_CONSTEXPR int a[] = {0,1,2};
	HAMON_STATIC_CONSTEXPR hamon::array<float, 2> a2{{0.5f, 1.5f}};
	hamon::vector<float> v {3,1,4,1,5};
	hamon::list<int> l {6, 7, 8};

//	EXPECT_TRUE(&*hamon::rend(a) == &a[-1]);
	EXPECT_TRUE(hamon::rend(a2) == a2.rend());
	EXPECT_TRUE(hamon::rend(v) == v.rend());
	EXPECT_TRUE(hamon::rend(l) == l.rend());

	{
		auto it = hamon::rbegin(a);
		EXPECT_TRUE(it != hamon::rend(a));
		++it;
		EXPECT_TRUE(it != hamon::rend(a));
		++it;
		EXPECT_TRUE(it != hamon::rend(a));
		++it;
		EXPECT_TRUE(it == hamon::rend(a));
	}
	{
		auto it = hamon::rbegin(a2);
		EXPECT_TRUE(it != hamon::rend(a2));
		++it;
		EXPECT_TRUE(it != hamon::rend(a2));
		++it;
		EXPECT_TRUE(it == hamon::rend(a2));
	}
	{
		auto it = hamon::rbegin(v);
		EXPECT_TRUE(it != hamon::rend(v));
		++it;
		EXPECT_TRUE(it != hamon::rend(v));
		++it;
		EXPECT_TRUE(it != hamon::rend(v));
		++it;
		EXPECT_TRUE(it != hamon::rend(v));
		++it;
		EXPECT_TRUE(it != hamon::rend(v));
		++it;
		EXPECT_TRUE(it == hamon::rend(v));
	}
	{
		auto it = hamon::rbegin(l);
		EXPECT_TRUE(it != hamon::rend(l));
		++it;
		EXPECT_TRUE(it != hamon::rend(l));
		++it;
		EXPECT_TRUE(it != hamon::rend(l));
		++it;
		EXPECT_TRUE(it == hamon::rend(l));
	}
}
