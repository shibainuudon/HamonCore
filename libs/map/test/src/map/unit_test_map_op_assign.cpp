/**
 *	@file	unit_test_map_op_assign.cpp
 *
 *	@brief	operator=のテスト
 */

#include <hamon/map/map.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_map_test
{

namespace op_assign_test
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

GTEST_TEST(MapTest, OpAssignTest)
{
	// https://en.cppreference.com/w/cpp/container/map/operator%3D

	hamon::map<int, int> x {{1, 1}, {2, 2}, {3, 3}}, y, z;
	using Pair = typename hamon::map<int, int>::value_type;
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

}	// namespace hamon_map_test
