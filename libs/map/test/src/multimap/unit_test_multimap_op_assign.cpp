/**
 *	@file	unit_test_multimap_op_assign.cpp
 *
 *	@brief	operator=のテスト
 */

#include <hamon/map/multimap.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_multimap_test
{

namespace op_assign_test
{

template <typename Key, typename T, typename C>
std::string ToString(const hamon::multimap<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

GTEST_TEST(MultimapTest, OpAssignTest)
{
	// https://en.cppreference.com/w/cpp/container/multimap/operator%3D

	using Map = hamon::multimap<int, int>;
	using Pair = typename Map::value_type;

	hamon::multimap<int, int> x {{1, 1}, {2, 2}, {3, 3}}, y, z;
	const auto w = {Pair{4, 4}, {5, 5}, {6, 6}, {7, 7}};

	// Initially
	EXPECT_EQ("[1] = 1, [2] = 2, [3] = 3, ", ToString(x));
	EXPECT_EQ("", ToString(y));
	EXPECT_EQ("", ToString(z));

	// Copy assignment copies data from x to y
	y = x;
	EXPECT_EQ("[1] = 1, [2] = 2, [3] = 3, ", ToString(x));
	EXPECT_EQ("[1] = 1, [2] = 2, [3] = 3, ", ToString(y));

	// Move assignment moves data from x to z, modifying both x and z
	z = hamon::move(x);
	EXPECT_EQ("", ToString(x));
	EXPECT_EQ("[1] = 1, [2] = 2, [3] = 3, ", ToString(z));

	// Assignment of initializer_list w to z
	z = w;
	EXPECT_EQ("[4] = 4, [5] = 5, [6] = 6, [7] = 7, ", ToString(z));
}

}	// namespace op_assign_test

}	// namespace hamon_multimap_test
