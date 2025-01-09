/**
 *	@file	unit_test_memory_resource_new_delete_resource.cpp
 *
 *	@brief	new_delete_resource のテスト
 */

#include <hamon/memory_resource/new_delete_resource.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryResourceTest, NewDeleteResourceTest)
{
	auto* mr1 = hamon::pmr::new_delete_resource();
	auto* mr2 = hamon::pmr::new_delete_resource();
	EXPECT_TRUE(mr1 == mr2);
}
