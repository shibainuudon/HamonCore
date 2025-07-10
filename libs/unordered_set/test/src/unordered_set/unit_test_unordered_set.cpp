/**
 *	@file	unit_test_unordered_set.cpp
 *
 *	@brief	unordered_set のテスト
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(UnorderedSetTest, UnorderedSetTest)
{
	hamon::unordered_set<hamon::string> us {"1st element", "2nd element", "3rd element", };
	EXPECT_TRUE(us.size() == 3);
	EXPECT_TRUE( us.contains("1st element"));
	EXPECT_TRUE( us.contains("2nd element"));
	EXPECT_TRUE( us.contains("3rd element"));
	EXPECT_TRUE(!us.contains("4th element"));

	us.emplace("4th element");
	EXPECT_TRUE(us.size() == 4);
	EXPECT_TRUE( us.contains("1st element"));
	EXPECT_TRUE( us.contains("2nd element"));
	EXPECT_TRUE( us.contains("3rd element"));
	EXPECT_TRUE( us.contains("4th element"));

	us.erase("2nd element");
	EXPECT_TRUE(us.size() == 3);
	EXPECT_TRUE( us.contains("1st element"));
	EXPECT_TRUE(!us.contains("2nd element"));
	EXPECT_TRUE( us.contains("3rd element"));
	EXPECT_TRUE( us.contains("4th element"));
}
