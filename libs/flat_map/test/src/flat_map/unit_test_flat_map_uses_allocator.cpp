/**
 *	@file	unit_test_flat_map_uses_allocator.cpp
 *
 *	@brief	uses_allocator のテスト
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/less.hpp>
#include <gtest/gtest.h>
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace uses_allocator_test
{

GTEST_TEST(FlatMapTest, UsesAllocatorTest)
{
	using Map1 = hamon::flat_map<int, float, hamon::less<int>, UseAllocContainer<int>, UseAllocContainer<float>>;
	using Map2 = hamon::flat_map<int, float, hamon::less<int>, UseAllocContainer<int>, MinSequenceContainer<float>>;
	using Map3 = hamon::flat_map<int, float, hamon::less<int>, MinSequenceContainer<int>, UseAllocContainer<float>>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::uses_allocator<Map1, Alloc>::value, "");
	static_assert(!hamon::uses_allocator<Map2, Alloc>::value, "");
	static_assert(!hamon::uses_allocator<Map3, Alloc>::value, "");
}

}	// namespace uses_allocator_test

}	// namespace hamon_flat_map_test
