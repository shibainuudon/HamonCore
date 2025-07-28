/**
 *	@file	unit_test_flat_set_incomplete_type.cpp
 *
 *	@brief	不完全型のテスト
 */

#include <hamon/flat_set/flat_set.hpp>
#include <gtest/gtest.h>

namespace hamon_flat_set_test
{

namespace incomplete_type_test
{

// Check that std::flat_set and its iterators can be instantiated with an incomplete
// type.

struct A
{
	using Set = hamon::flat_set<A>;
	int data;
	Set m;
	Set::iterator it;
	Set::const_iterator cit;
};

// Implement the operator< required in order to instantiate flat_set<A>
constexpr bool operator<(A const& L, A const& R) { return L.data < R.data; }

GTEST_TEST(FlatSetTest, IncompleteTypeTest)
{
	A a;
}

}	// namespace incomplete_type_test

}	// namespace hamon_flat_set_test
