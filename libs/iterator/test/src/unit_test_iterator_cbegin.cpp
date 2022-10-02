/**
 *	@file	unit_test_iterator_cbegin.cpp
 *
 *	@brief	cbegin のテスト
 */

#include <hamon/iterator/cbegin.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, CBeginTest)
{
	HAMON_STATIC_CONSTEXPR int a[] = {0,1,2};
	std::vector<float> v {3,1,4,1,5};
	std::array<float, 2> a2{{0.5f, 1.5f}};

	{
		HAMON_CONSTEXPR auto it = hamon::cbegin(a);
		(void)it;
	}
	{
		auto it = hamon::cbegin(v);
		(void)it;
	}
	{
		auto it = hamon::cbegin(a2);
		(void)it;
	}

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::cbegin(a) == &a[0]);
	EXPECT_TRUE(hamon::cbegin(v) == v.cbegin());
	EXPECT_TRUE(hamon::cbegin(a2) == a2.cbegin());

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, *hamon::cbegin(a));
	EXPECT_EQ(3, *hamon::cbegin(v));
	EXPECT_EQ(0.5f, *hamon::cbegin(a2));

	{
		auto it = hamon::cbegin(a);
		EXPECT_EQ(0, *it);
		++it;
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_EQ(2, *it);
		++it;
	}
	{
		auto it = hamon::cbegin(v);
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
		auto it = hamon::cbegin(a2);
		EXPECT_EQ(0.5f, *it);
		++it;
		EXPECT_EQ(1.5f, *it);
		++it;
	}
}
