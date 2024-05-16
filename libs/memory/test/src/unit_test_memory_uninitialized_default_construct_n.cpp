/**
 *	@file	unit_test_memory_uninitialized_default_construct_n.cpp
 *
 *	@brief	uninitialized_default_construct_n のテスト
 */

#include <hamon/memory/uninitialized_default_construct_n.hpp>
#include <hamon/memory/destroy.hpp>
#include <gtest/gtest.h>
#include <list>

namespace hamon_memory_test
{

namespace uninitialized_default_construct_n_test
{

struct X
{
	static int count;
	X() { count++; }
	~X() { count--; }
};

int X::count = 0;

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCtor
{
	static int count;
	static int count_limit;

	ThrowOnCtor()
	{
		if (count >= count_limit)
		{
			throw 0;
		}
		count++;
	}

	~ThrowOnCtor() { count--; }
};

int ThrowOnCtor::count = 0;
int ThrowOnCtor::count_limit = 100;
#endif

GTEST_TEST(MemoryTest, UninitializedDefaultConstructNTest)
{
	{
		X a[100] = {};
		hamon::destroy(a, a + 100);
		EXPECT_EQ( 0, X::count);

		hamon::uninitialized_default_construct_n(a, 10);
		EXPECT_EQ(10, X::count);

		hamon::destroy(a, a + 10);
		EXPECT_EQ( 0, X::count);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		ThrowOnCtor a[20] = {};
		hamon::destroy(a, a + 20);
		EXPECT_EQ( 0, ThrowOnCtor::count);

		hamon::uninitialized_default_construct_n(a, 10);
		EXPECT_EQ(10, ThrowOnCtor::count);

		hamon::destroy(a, a + 10);
		EXPECT_EQ( 0, ThrowOnCtor::count);

		ThrowOnCtor::count_limit = 5;
		EXPECT_ANY_THROW(hamon::uninitialized_default_construct_n(a, 10));
		EXPECT_EQ(0, ThrowOnCtor::count);

		EXPECT_NO_THROW(hamon::uninitialized_default_construct_n(a, 2));
		EXPECT_ANY_THROW(hamon::uninitialized_default_construct_n(a, 10));
		EXPECT_EQ(2, ThrowOnCtor::count);
	}
#endif
	{
		int a[30];
		hamon::uninitialized_default_construct_n(a, 11);
		hamon::destroy(a, a + 11);
	}
}

}	// namespace uninitialized_default_construct_n_test

}	// namespace hamon_memory_test
