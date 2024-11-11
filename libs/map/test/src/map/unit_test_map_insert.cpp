/**
 *	@file	unit_test_map_insert.cpp
 *
 *	@brief	insert のテスト
 */

#include <hamon/map/map.hpp>
#include <hamon/iterator.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_map_test
{

namespace insert_test
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

GTEST_TEST(MapTest, InsertTest)
{
	// https://en.cppreference.com/w/cpp/container/map/insert

	hamon::map<std::string, float> heights;

	// Overload 3: insert from rvalue reference
	const auto r = heights.insert({std::string("Hinata"), 162.8f});
	EXPECT_TRUE(r.first->first == "Hinata");
	EXPECT_TRUE(r.first->second == 162.8f);
	EXPECT_TRUE(r.second);
	auto it_hinata = r.first;

	{
		// Overload 1: insert from lvalue reference
		const auto r2 = heights.insert(*it_hinata);
		EXPECT_TRUE(r2.first->first == "Hinata");
		EXPECT_TRUE(r2.first->second == 162.8f);
		EXPECT_FALSE(r2.second);
	}
	{
		// Overload 2: insert via forwarding to emplace
		const auto r2 = heights.insert(std::pair<std::string, float>{"Kageyama", 180.6f});
		EXPECT_TRUE(r2.first->first == "Kageyama");
		EXPECT_TRUE(r2.first->second == 180.6f);
		EXPECT_TRUE(r2.second);
	}
	{
		// Overload 6: insert from rvalue reference with positional hint
		const auto n = hamon::size(heights);
		const auto it = heights.insert(it_hinata, {std::string("Azumane"), 184.7f});
		EXPECT_TRUE(it->first == "Azumane");
		EXPECT_TRUE(it->second == 184.7f);
		EXPECT_TRUE(hamon::size(heights) != n);
	}
	{
		// Overload 4: insert from lvalue reference with positional hint
		const auto n = hamon::size(heights);
		const auto it = heights.insert(it_hinata, *it_hinata);
		EXPECT_TRUE(it->first == "Hinata");
		EXPECT_TRUE(it->second == 162.8f);
		EXPECT_FALSE(hamon::size(heights) != n);
	}
	{
		// Overload 5: insert via forwarding to emplace with positional hint
		const auto n = hamon::size(heights);
		const auto it = heights.insert(it_hinata, std::pair<std::string, float>{"Tsukishima", 188.3f});
		EXPECT_TRUE(it->first == "Tsukishima");
		EXPECT_TRUE(it->second == 188.3f);
		EXPECT_TRUE(hamon::size(heights) != n);
	}

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

	auto node_hinata = heights.extract(it_hinata);
	hamon::map<std::string, float> heights2;

	// Overload 7: insert from iterator range
	heights2.insert(hamon::begin(heights), hamon::end(heights));

	// Overload 8: insert from initializer_list
	heights2.insert({{std::string("Kozume"), 169.2f}, {"Kuroo", 187.7f}});

	// Overload 9: insert node
	const auto status = heights2.insert(hamon::move(node_hinata));
	EXPECT_TRUE(status.position->first == "Hinata");
	EXPECT_TRUE(status.position->second == 162.8f);
	EXPECT_TRUE(status.inserted);

	node_hinata = heights2.extract(status.position);
	{
		// Overload 10: insert node with positional hint
		const auto n = hamon::size(heights2);
		const auto it = heights2.insert(hamon::begin(heights2), hamon::move(node_hinata));
		EXPECT_TRUE(it->first == "Hinata");
		EXPECT_TRUE(it->second == 162.8f);
		EXPECT_TRUE(hamon::size(heights2) != n);
	}

	// Print resulting map
	EXPECT_EQ("[Azumane] = 184.7, [Hinata] = 162.8, [Kageyama] = 180.6, [Kozume] = 169.2, [Kuroo] = 187.7, [Tsukishima] = 188.3, ", ToString(heights2));

#endif
}

}	// namespace insert_test

}	// namespace hamon_map_test
