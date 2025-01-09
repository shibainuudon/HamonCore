/**
 *	@file	unit_test_memory_resource_pool_options.cpp
 *
 *	@brief	pool_options のテスト
 */

#include <hamon/memory_resource/pool_options.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryResourceTest, PoolOptionsTest)
{
	static_assert(hamon::is_same<hamon::size_t, decltype(hamon::pmr::pool_options::max_blocks_per_chunk)>::value, "");
	static_assert(hamon::is_same<hamon::size_t, decltype(hamon::pmr::pool_options::largest_required_pool_block)>::value, "");
}
