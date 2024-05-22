﻿/**
 *	@file	unit_test_memory_detail_uninitialized_copy_impl.cpp
 *
 *	@brief	detail::uninitialized_copy_impl のテスト
 */

#include <hamon/memory/detail/uninitialized_copy_impl.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_copy_impl_test
{

struct S0
{
	int value;
};

struct S1
{
	int value;

	HAMON_CXX14_CONSTEXPR
	S1(int v)
		: value(v)
	{}

	HAMON_CXX14_CONSTEXPR
	S1(S1 const& x) HAMON_NOEXCEPT
		: value(x.value)
	{
	}

	//S1(S1&&) = delete;
	S1& operator=(S1 const&) = delete;
	S1& operator=(S1&&) = delete;
};

struct S2
{
	int value;

	HAMON_CXX14_CONSTEXPR
	S2(int v)
		: value(v)
	{}

	HAMON_CXX14_CONSTEXPR
	S2(S2 const& x)
		: value(x.value)
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		if (value == 0)
		{
			throw 0;
		}
#endif
	}

	//S2(S2&&) = delete;
	S2& operator=(S2 const&) = delete;
	S2& operator=(S2&&) = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
HAMON_CXX20_CONSTEXPR
#endif
bool test()
{
	{
		std::allocator<T> alloc;
		auto* p = alloc.allocate(10);
		T const a[] = { T{10}, T{20}, T{30} };
		auto ret = hamon::detail::uninitialized_copy_impl(a, a + 3, p);
		VERIFY(ret == p + 3);
		VERIFY(p[0].value == 10);
		VERIFY(p[1].value == 20);
		VERIFY(p[2].value == 30);
		alloc.deallocate(p, 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedCopyImplTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S0>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
#else
	EXPECT_TRUE(test<S0>());
	EXPECT_TRUE(test<S1>());
	EXPECT_TRUE(test<S2>());
#endif

	{
		std::allocator<S1> alloc;
		auto* p = alloc.allocate(10);
		S1 const a[] = { 10, 20, 0 };
		auto ret = hamon::detail::uninitialized_copy_impl(a, a + 3, p);
		EXPECT_TRUE(ret == p + 3);
		EXPECT_TRUE(p[0].value == 10);
		EXPECT_TRUE(p[1].value == 20);
		EXPECT_TRUE(p[2].value ==  0);
		alloc.deallocate(p, 10);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		S2 const a[] = { 10, 20, 0 };
		EXPECT_ANY_THROW(hamon::detail::uninitialized_copy_impl(a, a + 3, p));
		alloc.deallocate(p, 10);
	}
#endif
}

}	// namespace uninitialized_copy_impl_test

}	// namespace hamon_memory_test