﻿/**
 *	@file	unit_test_memory_detail_uninitialized_default_construct_impl.cpp
 *
 *	@brief	detail::uninitialized_default_construct_impl のテスト
 */

#include <hamon/memory/detail/uninitialized_default_construct_impl.hpp>
#include <hamon/memory/allocator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_default_construct_impl_test
{

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
#define MEMORY_TEST_CONSTEXPR				constexpr
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

struct S0
{
	int value;
};

struct S1
{
	int value;

	HAMON_CXX14_CONSTEXPR
	S1() HAMON_NOEXCEPT : value(42) {}
};

struct S2
{
	int value;

	HAMON_CXX14_CONSTEXPR
	S2() : value(43) {}
};

#if !defined(HAMON_NO_EXCEPTIONS)
struct S3
{
	S3()
	{
		throw 0;
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
MEMORY_TEST_CONSTEXPR bool test1()
{
	{
		using Range = RangeWrapper<S0>;
		using Iter = typename Range::iterator;
		using Sent = typename Range::sentinel;
		hamon::allocator<S0> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_default_construct_impl(Iter{p}, Sent{p + 2});
		VERIFY(ret == Iter{p + 2});
		alloc.deallocate(p, 10);
	}
	{
		using Range = RangeWrapper<S1>;
		using Iter = typename Range::iterator;
		using Sent = typename Range::sentinel;
		hamon::allocator<S1> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_default_construct_impl(Iter{p}, Sent{p + 3});
		VERIFY(ret == Iter{p + 3});
		VERIFY(p[0].value == 42);
		VERIFY(p[1].value == 42);
		VERIFY(p[2].value == 42);
		alloc.deallocate(p, 10);
	}
	{
		using Range = RangeWrapper<S2>;
		using Iter = typename Range::iterator;
		using Sent = typename Range::sentinel;
		hamon::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_default_construct_impl(Iter{p}, Sent{p + 4});
		VERIFY(ret == Iter{p + 4});
		VERIFY(p[0].value == 43);
		VERIFY(p[1].value == 43);
		VERIFY(p[2].value == 43);
		VERIFY(p[3].value == 43);
		alloc.deallocate(p, 10);
	}
	return true;
}

MEMORY_TEST_CONSTEXPR bool test()
{
	return
		test1<test_forward_range>() &&
		test1<test_bidirectional_range>() &&
		test1<test_random_access_range>() &&
		test1<test_contiguous_range>() &&
		test1<test_forward_common_range>() &&
		test1<test_bidirectional_common_range>() &&
		test1<test_random_access_common_range>() &&
		test1<test_contiguous_common_range>();
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedDefaultConstructImplTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::allocator<S3> alloc;
		auto* p = alloc.allocate(10);
		EXPECT_ANY_THROW(hamon::detail::uninitialized_default_construct_impl(p, p + 3));
		alloc.deallocate(p, 10);
	}
#endif
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace uninitialized_default_construct_impl_test

}	// namespace hamon_memory_test
