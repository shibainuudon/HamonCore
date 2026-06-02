/**
 *	@file	unit_test_flat_multimap_incomplete_type.cpp
 *
 *	@brief	不完全型のテスト
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <gtest/gtest.h>

namespace hamon_flat_multimap_test
{

namespace incomplete_type_test
{

HAMON_WARNING_PUSH()
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 160000)
HAMON_WARNING_DISABLE_GCC("-Wsfinae-incomplete")
#endif

// Check that std::flat_multimap and its iterators can be instantiated with an incomplete
// type.

struct A
{
	using Map = hamon::flat_multimap<A, A>;
	int data;
	Map m;
	Map::iterator it;
	Map::const_iterator cit;
};

HAMON_WARNING_POP()

// Implement the operator< required in order to instantiate flat_multimap<A, X>
constexpr bool operator<(A const& L, A const& R) { return L.data < R.data; }

GTEST_TEST(FlatMultimapTest, IncompleteTypeTest)
{
	A a;
}

}	// namespace incomplete_type_test

}	// namespace hamon_flat_multimap_test
