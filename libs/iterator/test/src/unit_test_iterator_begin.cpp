/**
 *	@file	unit_test_iterator_begin.cpp
 *
 *	@brief	begin のテスト
 */

#include <hamon/iterator/begin.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, BeginTest)
{
	HAMON_STATIC_CONSTEXPR int a[] = {0,1,2};
	hamon::vector<float> v {3,1,4,1,5};
	hamon::array<float, 2> a2{{0.5f, 1.5f}};

	{
		HAMON_CONSTEXPR auto it = hamon::begin(a);
		(void)it;
	}
	{
		auto it = hamon::begin(v);
		(void)it;
	}
	{
		auto it = hamon::begin(a2);
		(void)it;
	}

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::begin(a) == &a[0]);
	EXPECT_TRUE(hamon::begin(v) == v.begin());
	EXPECT_TRUE(hamon::begin(a2) == a2.begin());

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, *hamon::begin(a));
	EXPECT_EQ(3, *hamon::begin(v));
	EXPECT_EQ(0.5f, *hamon::begin(a2));

	{
		auto it = hamon::begin(a);
		EXPECT_EQ(0, *it);
		++it;
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(2, *it);
		++it;
	}
	{
		auto it = hamon::begin(v);
		EXPECT_EQ(3, *it);
		++it;
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(4, *it);
		++it;
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(5, *it);
		++it;
	}
	{
		auto it = hamon::begin(a2);
		EXPECT_EQ(0.5f, *it);
		++it;
		EXPECT_EQ(1.5f, *it);
		++it;
	}
}
