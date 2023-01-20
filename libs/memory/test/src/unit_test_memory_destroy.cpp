/**
 *	@file	unit_test_memory_destroy.cpp
 *
 *	@brief	destroy のテスト
 */

#include <hamon/memory/destroy.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace destroy_test
{

struct X
{
	int value;
	static int destruct_count;
	~X()
	{
		++destruct_count;
	}
};

int X::destruct_count = 0;

GTEST_TEST(MemoryTest, DestroyTest)
{
	EXPECT_EQ(0, X::destruct_count);
	{
		X x[3] = {};
		hamon::destroy(x, x+3);
		EXPECT_EQ(3, X::destruct_count);
	}
	EXPECT_EQ(6, X::destruct_count);

	{
		int x[8] = {};
		hamon::destroy(x, x+8);
	}
}

}	// namespace destroy_test

}	// namespace hamon_memory_test
