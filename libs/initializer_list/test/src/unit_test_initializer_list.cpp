/**
 *	@file	unit_test_initializer_list.cpp
 *
 *	@brief	initializer_list のテスト
 */

#include <hamon/initializer_list.hpp>
#include <gtest/gtest.h>

GTEST_TEST(InitializerListTest, InitializerListTest)
{
	hamon::initializer_list<int> il{1,2,3};
	EXPECT_EQ(3, il.size());

	auto it = il.begin();
	EXPECT_EQ(1, *it);
	EXPECT_TRUE(it != il.end());
	++it;
	EXPECT_EQ(2, *it);
	EXPECT_TRUE(it != il.end());
	++it;
	EXPECT_EQ(3, *it);
	EXPECT_TRUE(it != il.end());
	++it;
	EXPECT_TRUE(it == il.end());
}
