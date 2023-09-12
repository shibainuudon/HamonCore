/**
 *	@file	unit_test_iterator_end.cpp
 *
 *	@brief	end のテスト
 */

#include <hamon/iterator/end.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, EndTest)
{
	HAMON_STATIC_CONSTEXPR int a[] = {0,1,2};
	std::vector<float> v {3,1,4,1,5};
	hamon::array<float, 2> a2{{0.5f, 1.5f}};

	{
		HAMON_CONSTEXPR auto it = hamon::end(a);
		(void)it;
	}
	{
		auto it = hamon::end(v);
		(void)it;
	}
	{
		auto it = hamon::end(a2);
		(void)it;
	}

	//HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::end(a) == &a[3]);
	EXPECT_TRUE(hamon::end(v) == v.end());
	EXPECT_TRUE(hamon::end(a2) == a2.end());

	{
		auto it = hamon::begin(a);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it != hamon::end(a));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != hamon::end(a));
		++it;
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it != hamon::end(a));
		++it;
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		auto it = hamon::begin(v);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it != hamon::end(v));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != hamon::end(v));
		++it;
		EXPECT_EQ(4, *it);
		EXPECT_TRUE(it != hamon::end(v));
		++it;
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != hamon::end(v));
		++it;
		EXPECT_EQ(5, *it);
		EXPECT_TRUE(it != hamon::end(v));
		++it;
		EXPECT_TRUE(it == hamon::end(v));
	}
	{
		auto it = hamon::begin(a2);
		EXPECT_EQ(0.5f, *it);
		EXPECT_TRUE(it != hamon::end(a2));
		++it;
		EXPECT_EQ(1.5f, *it);
		EXPECT_TRUE(it != hamon::end(a2));
		++it;
		EXPECT_TRUE(it == hamon::end(a2));
	}
}
