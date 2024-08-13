/**
 *	@file	unit_test_memory_destroy_n.cpp
 *
 *	@brief	destroy_n のテスト
 */

#include <hamon/memory/destroy_n.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace destroy_n_test
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
	constexpr std::size_t num = 3;
	hamon::allocator<S> alloc;
	S* p = alloc.allocate(num);
	bool destructed[num] = {false, false, false};
	for (std::size_t i = 0; i < num; ++i)
	{
		hamon::construct_at(&p[i], &destructed[i]);
	}
	VERIFY(!destructed[0]);
	VERIFY(!destructed[1]);
	VERIFY(!destructed[2]);
	auto ret = hamon::destroy_n(p, num);
	VERIFY(ret == p + num);
	VERIFY( destructed[0]);
	VERIFY( destructed[1]);
	VERIFY( destructed[2]);
	alloc.deallocate(p, num);
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, DestroyNTest)
{
	EXPECT_EQ(0, X::destruct_count);
	{
		X x[3] = {};
		auto ret = hamon::destroy_n(x, 3);
		EXPECT_TRUE(ret == x+3);
		EXPECT_EQ(3, X::destruct_count);
	}
	EXPECT_EQ(6, X::destruct_count);

	{
		int x[8] = {};
		auto ret = hamon::destroy_n(x, 8);
		EXPECT_TRUE(ret == x+8);
	}

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(constexpr_test());
#else
	EXPECT_TRUE(constexpr_test());
#endif
}

}	// namespace destroy_n_test

}	// namespace hamon_memory_test
