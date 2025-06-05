/**
 *	@file	unit_test_flat_map_incomplete_type.cpp
 *
 *	@brief	不完全型のテスト
 */

#include <hamon/flat_map/flat_map.hpp>
#include <gtest/gtest.h>

namespace hamon_flat_map_test
{

namespace incomplete_type_test
{

// Check that std::flat_map and its iterators can be instantiated with an incomplete
// type.

struct A
{
	using Map = hamon::flat_map<A, A>;
	int data;
	Map m;
	Map::iterator it;
	Map::const_iterator cit;
};

// Implement the operator< required in order to instantiate flat_map<A, X>
constexpr bool operator<(A const& L, A const& R) { return L.data < R.data; }

GTEST_TEST(FlatMapTest, IncompleteTypeTest)
{
	A a;
}

}	// namespace incomplete_type_test

}	// namespace hamon_flat_map_test
