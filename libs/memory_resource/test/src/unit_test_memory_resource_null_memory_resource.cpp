/**
 *	@file	unit_test_memory_resource_null_memory_resource.cpp
 *
 *	@brief	null_memory_resource のテスト
 */

#include <hamon/memory_resource/null_memory_resource.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryResourceTest, NullMemoryResourceTest)
{
	auto* mr1 = hamon::pmr::null_memory_resource();
	auto* mr2 = hamon::pmr::null_memory_resource();
	EXPECT_TRUE(mr1 == mr2);
}
