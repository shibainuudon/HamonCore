/**
 *	@file	unit_test_memory_uninitialized_default_construct.cpp
 *
 *	@brief	uninitialized_default_construct のテスト
 */

#include <hamon/memory/uninitialized_default_construct.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/list.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace uninitialized_default_construct_test
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

GTEST_TEST(MemoryTest, UninitializedDefaultConstructTest)
{
	{
		X a[100] = {};
		hamon::destroy(hamon::begin(a), hamon::end(a));
		EXPECT_EQ( 0, X::count);

		hamon::uninitialized_default_construct(a, a + 10);
		EXPECT_EQ(10, X::count);

		hamon::destroy(a, a + 10);
		EXPECT_EQ( 0, X::count);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		ThrowOnCtor a[20] = {};
		hamon::destroy(hamon::begin(a), hamon::end(a));
		EXPECT_EQ( 0, ThrowOnCtor::count);

		hamon::uninitialized_default_construct(a, a + 10);
		EXPECT_EQ(10, ThrowOnCtor::count);

		hamon::destroy(a, a + 10);
		EXPECT_EQ( 0, ThrowOnCtor::count);

		ThrowOnCtor::count_limit = 5;
		EXPECT_ANY_THROW(hamon::uninitialized_default_construct(a, a + 10));
		EXPECT_EQ(0, ThrowOnCtor::count);

		EXPECT_NO_THROW(hamon::uninitialized_default_construct(a, a + 2));
		EXPECT_ANY_THROW(hamon::uninitialized_default_construct(a, a + 10));
		EXPECT_EQ(2, ThrowOnCtor::count);
	}
#endif
	{
		int a[30];
		hamon::uninitialized_default_construct(a, a + 11);
		hamon::destroy(a, a + 11);
	}
	{
		hamon::list<int> a = {1,2,3};
		hamon::uninitialized_default_construct(a.begin(), a.end());
	}
}

}	// namespace uninitialized_default_construct_test

}	// namespace hamon_memory_test
