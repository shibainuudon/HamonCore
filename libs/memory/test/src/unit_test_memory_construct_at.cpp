/**
 *	@file	unit_test_memory_construct_at.cpp
 *
 *	@brief	construct_at のテスト
 */

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace construct_at_test
{

struct S
{
	int x;
	float y;
	double z;

	static int construct_count;
	static int destruct_count;

	S() : x{}, y{}, z{}
	{
		++construct_count;
	}

	S(int x_, float y_, double z_)
		: x{ x_ }, y{ y_ }, z{ z_ }
	{
		++construct_count;
	}

	~S()
	{
		++destruct_count;
	}
};

int S::construct_count = 0;
int S::destruct_count  = 0;

GTEST_TEST(MemoryTest, ConstructAtTest)
{
	S::construct_count = 0;
	S::destruct_count  = 0;
	{
		alignas(S) unsigned char buf[sizeof(S)];
		EXPECT_EQ(0, S::construct_count);
		EXPECT_EQ(0, S::destruct_count);
		S* ptr = hamon::construct_at(reinterpret_cast<S*>(buf));
		EXPECT_EQ(0,    ptr->x);
		EXPECT_EQ(0.0f, ptr->y);
		EXPECT_EQ(0.0,  ptr->z);
		EXPECT_EQ(1, S::construct_count);
		EXPECT_EQ(0, S::destruct_count);
		hamon::destroy_at(ptr);
		EXPECT_EQ(1, S::construct_count);
		EXPECT_EQ(1, S::destruct_count);
	}
	EXPECT_EQ(1, S::construct_count);
	EXPECT_EQ(1, S::destruct_count);

	S::construct_count = 0;
	S::destruct_count  = 0;
	{
		alignas(S) unsigned char buf[sizeof(S)];
		EXPECT_EQ(0, S::construct_count);
		EXPECT_EQ(0, S::destruct_count);
		S* ptr = hamon::construct_at(reinterpret_cast<S*>(buf), 1, 0.5f, -2.5);
		EXPECT_EQ(1,    ptr->x);
		EXPECT_EQ(0.5f, ptr->y);
		EXPECT_EQ(-2.5, ptr->z);
		EXPECT_EQ(1, S::construct_count);
		EXPECT_EQ(0, S::destruct_count);
		hamon::destroy_at(ptr);
		EXPECT_EQ(1, S::construct_count);
		EXPECT_EQ(1, S::destruct_count);
	}
	EXPECT_EQ(1, S::construct_count);
	EXPECT_EQ(1, S::destruct_count);

	{
		int x = {};
		hamon::construct_at(&x, 17);
		EXPECT_EQ(x, 17);
		hamon::destroy_at(&x);
	}
}

}	// namespace construct_at_test

}	// namespace hamon_memory_test
