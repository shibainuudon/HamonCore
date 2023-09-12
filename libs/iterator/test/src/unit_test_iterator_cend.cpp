/**
 *	@file	unit_test_iterator_cend.cpp
 *
 *	@brief	cend のテスト
 */

#include <hamon/iterator/cend.hpp>
#include <hamon/iterator/cbegin.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, CEndTest)
{
	HAMON_STATIC_CONSTEXPR int a[] = {0,1,2};
	std::vector<float> v {3,1,4,1,5};
	hamon::array<float, 2> a2{{0.5f, 1.5f}};

	{
		HAMON_CONSTEXPR auto it = hamon::cend(a);
		(void)it;
	}
	{
		auto it = hamon::cend(v);
		(void)it;
	}
	{
		auto it = hamon::cend(a2);
		(void)it;
	}

	//HAMON_CONSTEXPR_EXPECT_TRUE(hamon::cend(a) == &a[3]);
	EXPECT_TRUE(hamon::cend(v) == v.cend());
	EXPECT_TRUE(hamon::cend(a2) == a2.cend());

	{
		auto it = hamon::cbegin(a);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it != hamon::cend(a));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != hamon::cend(a));
		++it;
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it != hamon::cend(a));
		++it;
		EXPECT_TRUE(it == hamon::cend(a));
	}
	{
		auto it = hamon::cbegin(v);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it != hamon::cend(v));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != hamon::cend(v));
		++it;
		EXPECT_EQ(4, *it);
		EXPECT_TRUE(it != hamon::cend(v));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != hamon::cend(v));
		++it;
		EXPECT_EQ(5, *it);
		EXPECT_TRUE(it != hamon::cend(v));
		++it;
		EXPECT_TRUE(it == hamon::cend(v));
	}
	{
		auto it = hamon::cbegin(a2);
		EXPECT_EQ(0.5f, *it);
		EXPECT_TRUE(it != hamon::cend(a2));
		++it;
		EXPECT_EQ(1.5f, *it);
		EXPECT_TRUE(it != hamon::cend(a2));
		++it;
		EXPECT_TRUE(it == hamon::cend(a2));
	}
}
