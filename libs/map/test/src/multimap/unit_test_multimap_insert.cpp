/**
 *	@file	unit_test_multimap_insert.cpp
 *
 *	@brief	insert のテスト
 */

#include <hamon/map/multimap.hpp>
#include <gtest/gtest.h>
#include <functional>
#include <string>
#include <sstream>

namespace hamon_multimap_test
{

namespace insert_test
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

GTEST_TEST(MultimapTest, InsertTest)
{
	// https://en.cppreference.com/w/cpp/container/multimap/insert

	using Map = hamon::multimap<int, std::string, std::greater<int>>;
	using Pair = typename Map::value_type;

	// list-initialize
	Map mmap{{2, "foo"}, {2, "bar"}, {3, "baz"}, {1, "abc"}, {5, "def"}};
	EXPECT_EQ("[5] = def, [3] = baz, [2] = foo, [2] = bar, [1] = abc, ", ToString(mmap));

	// insert using value_type
	mmap.insert(decltype(mmap)::value_type(5, "pqr"));
	EXPECT_EQ("[5] = def, [5] = pqr, [3] = baz, [2] = foo, [2] = bar, [1] = abc, ", ToString(mmap));

	// insert using pair
	mmap.insert(Pair{6, "uvw"});
	EXPECT_EQ("[6] = uvw, [5] = def, [5] = pqr, [3] = baz, [2] = foo, [2] = bar, [1] = abc, ", ToString(mmap));

	mmap.insert({7, "xyz"});
	EXPECT_EQ("[7] = xyz, [6] = uvw, [5] = def, [5] = pqr, [3] = baz, [2] = foo, [2] = bar, [1] = abc, ", ToString(mmap));

	// insert using initializer_list
	mmap.insert({{5, "one"}, {5, "two"}});
	EXPECT_EQ("[7] = xyz, [6] = uvw, [5] = def, [5] = pqr, [5] = one, [5] = two, [3] = baz, [2] = foo, [2] = bar, [1] = abc, ", ToString(mmap));

	// insert using a pair of iterators
	mmap.clear();
	const auto il = {Pair{1, "a"}, {2, "b"}, {2, "c"}, {3, "d"}};
	mmap.insert(il.begin(), il.end());
	EXPECT_EQ("[3] = d, [2] = b, [2] = c, [1] = a, ", ToString(mmap));
}

}	// namespace insert_test

}	// namespace hamon_multimap_test
