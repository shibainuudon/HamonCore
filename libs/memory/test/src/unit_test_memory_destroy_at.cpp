/**
 *	@file	unit_test_memory_destroy_at.cpp
 *
 *	@brief	destroy_at のテスト
 */

#include <hamon/memory/destroy_at.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/allocator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

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

struct S
{
	bool* m_destructed;

	constexpr S(bool* p) : m_destructed(p) {}

	HAMON_CXX20_CONSTEXPR ~S() { *m_destructed = true; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
HAMON_CXX20_CONSTEXPR
#endif
bool constexpr_test()
{
	hamon::allocator<S> alloc;
	S* p = alloc.allocate(1);
	bool destructed = false;
	hamon::construct_at(p, &destructed);
	VERIFY(!destructed);
	hamon::destroy_at(p);
	VERIFY( destructed);
	alloc.deallocate(p, 1);
	return true;
}

#undef VERIFY

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

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(constexpr_test());
#else
	EXPECT_TRUE(constexpr_test());
#endif
}

}	// namespace destroy_at_test

}	// namespace hamon_memory_test
