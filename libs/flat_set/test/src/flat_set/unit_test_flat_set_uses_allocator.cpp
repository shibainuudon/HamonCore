/**
 *	@file	unit_test_flat_set_uses_allocator.cpp
 *
 *	@brief	uses_allocator のテスト
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/less.hpp>
#include <gtest/gtest.h>
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace uses_allocator_test
{

GTEST_TEST(FlatSetTest, UsesAllocatorTest)
{
	using Set1 = hamon::flat_set<int, hamon::less<int>, UseAllocContainer<int>>;
	using Set2 = hamon::flat_set<int, hamon::less<int>, MinSequenceContainer<int>>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::uses_allocator<Set1, Alloc>::value, "");
	static_assert(!hamon::uses_allocator<Set2, Alloc>::value, "");
}

}	// namespace uses_allocator_test

}	// namespace hamon_flat_set_test
