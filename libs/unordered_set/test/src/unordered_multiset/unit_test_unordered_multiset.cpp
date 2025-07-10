/**
 *	@file	unit_test_unordered_multiset.cpp
 *
 *	@brief	unordered_multiset のテスト
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(UnorderedMultisetTest, UnorderedMultisetTest)
{
	hamon::unordered_multiset<hamon::string> ums {"1st element", "2nd element", "3rd element", };
	EXPECT_TRUE(ums.size() == 3);
	EXPECT_TRUE(ums.count("1st element") == 1);
	EXPECT_TRUE(ums.count("2nd element") == 1);
	EXPECT_TRUE(ums.count("3rd element") == 1);
	EXPECT_TRUE(ums.count("4th element") == 0);

	ums.insert({"2nd element", "4th element"});
	EXPECT_TRUE(ums.size() == 5);
	EXPECT_TRUE(ums.count("1st element") == 1);
	EXPECT_TRUE(ums.count("2nd element") == 2);
	EXPECT_TRUE(ums.count("3rd element") == 1);
	EXPECT_TRUE(ums.count("4th element") == 1);

	ums.erase("2nd element");
	EXPECT_TRUE(ums.size() == 3);
	EXPECT_TRUE(ums.count("1st element") == 1);
	EXPECT_TRUE(ums.count("2nd element") == 0);
	EXPECT_TRUE(ums.count("3rd element") == 1);
	EXPECT_TRUE(ums.count("4th element") == 1);
}
