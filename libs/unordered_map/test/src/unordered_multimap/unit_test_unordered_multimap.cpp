/**
 *	@file	unit_test_unordered_multimap.cpp
 *
 *	@brief	unordered_multimap のテスト
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(UnorderedMultimapTest, UnorderedMultimapTest)
{
	hamon::unordered_multimap<hamon::string, int> um {{"1st", 1}, {"2nd", 2}, {"3rd", 3}, };

	EXPECT_TRUE(um.size() == 3);

	um.emplace("4th", 4);
	EXPECT_TRUE(um.size() == 4);

	um.insert({{"5th", 5}, {"2nd", 6}});
	EXPECT_TRUE(um.size() == 6);

	um.erase("2nd");
	EXPECT_TRUE(um.size() == 4);
}
