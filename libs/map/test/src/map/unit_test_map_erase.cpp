/**
 *	@file	unit_test_map_erase.cpp
 *
 *	@brief	erase のテスト
 */

#include <hamon/map/map.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_map_test
{

namespace erase_test
{

template <typename Key, typename T, typename C>
std::string ToString(const hamon::map<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

GTEST_TEST(MapTest, EraseTest)
{
	// https://en.cppreference.com/w/cpp/container/map/erase

	hamon::map<int, std::string> c =
	{
		{1, "one"}, {2, "two"}, {3, "three"},
		{4, "four"}, {5, "five"}, {6, "six"}
	};

	// erase all odd numbers from c
	for (auto it = c.begin(); it != c.end();)
	{
		if (it->first % 2 != 0)
		{
			it = c.erase(it);
		}
		else
		{
			++it;
		}
	}

	EXPECT_EQ("[2] = two, [4] = four, [6] = six, ", ToString(c));

	EXPECT_EQ(0u, c.erase(1));
	EXPECT_EQ(1u, c.erase(2));

	EXPECT_EQ("[4] = four, [6] = six, ", ToString(c));
}

}	// namespace erase_test

}	// namespace hamon_map_test
