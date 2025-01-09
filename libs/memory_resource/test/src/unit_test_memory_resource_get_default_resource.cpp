/**
 *	@file	unit_test_memory_resource_get_default_resource.cpp
 *
 *	@brief	get_default_resource のテスト
 */

#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/memory_resource/new_delete_resource.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryResourceTest, GetDefaultResourceTest)
{
	EXPECT_TRUE(hamon::pmr::get_default_resource() == hamon::pmr::new_delete_resource());
}
