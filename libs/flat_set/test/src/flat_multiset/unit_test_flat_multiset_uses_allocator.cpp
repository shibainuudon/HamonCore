/**
 *	@file	unit_test_flat_multiset_uses_allocator.cpp
 *
 *	@brief	uses_allocator のテスト
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional/less.hpp>
#include <gtest/gtest.h>
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace uses_allocator_test
{

GTEST_TEST(FlatMultisetTest, UsesAllocatorTest)
{
	using Set1 = hamon::flat_multiset<int, hamon::less<int>, UseAllocContainer<int>>;
	using Set2 = hamon::flat_multiset<int, hamon::less<int>, MinSequenceContainer<int>>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::uses_allocator<Set1, Alloc>::value, "");
	static_assert(!hamon::uses_allocator<Set2, Alloc>::value, "");
}

}	// namespace uses_allocator_test

}	// namespace hamon_flat_multiset_test
