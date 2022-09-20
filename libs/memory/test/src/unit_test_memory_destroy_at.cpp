/**
 *	@file	unit_test_memory_destroy_at.cpp
 *
 *	@brief	destroy_at のテスト
 */

#include <hamon/memory/destroy_at.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace destroy_at_test
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

GTEST_TEST(MemoryTest, DestroyAtTest)
{
	X::destruct_count = 0;
	{
		alignas(X) unsigned char buf[sizeof(X)];
		new (buf) X();
		hamon::destroy_at(reinterpret_cast<X*>(buf));
		EXPECT_EQ(1, X::destruct_count);
	}
	EXPECT_EQ(1, X::destruct_count);

	X::destruct_count = 0;
	{
		X x[4] = {};
		hamon::destroy_at(&x);
		EXPECT_EQ(4, X::destruct_count);
	}
	EXPECT_EQ(8, X::destruct_count);

	{
		int x = {};
		hamon::destroy_at(&x);
	}
}

}	// namespace destroy_at_test

}	// namespace hamon_memory_test
