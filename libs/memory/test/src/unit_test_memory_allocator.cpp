/**
 *	@file	unit_test_memory_allocator.cpp
 *
 *	@brief	allocator のテスト
 */

#include <hamon/memory/allocator.hpp>
#include <hamon/config.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/new.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace allocator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
HAMON_CXX20_CONSTEXPR
#endif
bool test()
{
	{
		hamon::allocator<int> alloc;
		hamon::size_t n = 3;
		auto p = alloc.allocate(n);
		VERIFY(p != nullptr);
		alloc.deallocate(p, n);
	}
	{
		hamon::allocator<int> alloc;
		auto ret = alloc.allocate_at_least(5);
		VERIFY(ret.ptr != nullptr);
		alloc.deallocate(ret.ptr, ret.count);
	}
	{
		hamon::allocator<int> a1;
		hamon::allocator<float> a2;
		VERIFY( (a1 == a2));
		VERIFY(!(a1 != a2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, AllocatorTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
#else
	EXPECT_TRUE(test());
#endif

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::allocator<int> alloc;
		EXPECT_THROW((void)alloc.allocate(hamon::size_t(-1)), hamon::bad_array_new_length);
	}
	{
		hamon::allocator<int> alloc;
		EXPECT_THROW((void)alloc.allocate_at_least(hamon::size_t(-1)), hamon::bad_array_new_length);
	}
#endif
}

}	// namespace allocator_test

}	// namespace hamon_memory_test
