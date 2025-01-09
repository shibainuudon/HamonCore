/**
 *	@file	unit_test_memory_resource_set_default_resource.cpp
 *
 *	@brief	set_default_resource のテスト
 */

#include <hamon/memory_resource/set_default_resource.hpp>
#include <hamon/memory_resource/get_default_resource.hpp>
#include <hamon/memory_resource/new_delete_resource.hpp>
#include <hamon/memory_resource/null_memory_resource.hpp>
#include <gtest/gtest.h>

GTEST_TEST(MemoryResourceTest, SetDefaultResourceTest)
{
	EXPECT_TRUE(hamon::pmr::get_default_resource() == hamon::pmr::new_delete_resource());

	auto mr1 = hamon::pmr::set_default_resource(hamon::pmr::null_memory_resource());
	EXPECT_TRUE(mr1 == hamon::pmr::new_delete_resource());
	EXPECT_TRUE(hamon::pmr::get_default_resource() != hamon::pmr::new_delete_resource());

	auto mr2 = hamon::pmr::set_default_resource(mr1);
	EXPECT_TRUE(mr2 == hamon::pmr::null_memory_resource());
	EXPECT_TRUE(hamon::pmr::get_default_resource() == hamon::pmr::new_delete_resource());

	auto mr3 = hamon::pmr::set_default_resource(nullptr);
	EXPECT_TRUE(mr3 == hamon::pmr::new_delete_resource());
	EXPECT_TRUE(hamon::pmr::get_default_resource() == hamon::pmr::new_delete_resource());
}
