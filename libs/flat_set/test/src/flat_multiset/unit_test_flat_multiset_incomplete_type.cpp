/**
 *	@file	unit_test_flat_multiset_incomplete_type.cpp
 *
 *	@brief	不完全型のテスト
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <gtest/gtest.h>

namespace hamon_flat_multiset_test
{

namespace incomplete_type_test
{

// Check that std::flat_multiset and its iterators can be instantiated with an incomplete
// type.

struct A
{
	using Set = hamon::flat_multiset<A>;
	int data;
	Set m;
	Set::iterator it;
	Set::const_iterator cit;
};

// Implement the operator< required in order to instantiate flat_multiset<A>
constexpr bool operator<(A const& L, A const& R) { return L.data < R.data; }

GTEST_TEST(FlatMultisetTest, IncompleteTypeTest)
{
	A a;
}

}	// namespace incomplete_type_test

}	// namespace hamon_flat_multiset_test
