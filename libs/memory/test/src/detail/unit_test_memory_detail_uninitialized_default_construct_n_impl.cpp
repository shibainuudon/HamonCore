/**
 *	@file	unit_test_memory_detail_uninitialized_default_construct_n_impl.cpp
 *
 *	@brief	detail::uninitialized_default_construct_n_impl のテスト
 */

#include <hamon/memory/detail/uninitialized_default_construct_n_impl.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_default_construct_n_impl_test
{

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

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
HAMON_CXX20_CONSTEXPR
#endif
bool test()
{
	{
		std::allocator<S0> alloc;
		auto* p = alloc.allocate(10);
		hamon::detail::uninitialized_default_construct_n_impl(p, 3);
		alloc.deallocate(p, 10);
	}
	{
		std::allocator<S1> alloc;
		auto* p = alloc.allocate(10);
		hamon::detail::uninitialized_default_construct_n_impl(p, 3);
		VERIFY(p[0].value == 42);
		VERIFY(p[1].value == 42);
		VERIFY(p[2].value == 42);
		alloc.deallocate(p, 10);
	}
	{
		std::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		hamon::detail::uninitialized_default_construct_n_impl(p, 3);
		VERIFY(p[0].value == 43);
		VERIFY(p[1].value == 43);
		VERIFY(p[2].value == 43);
		alloc.deallocate(p, 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedDefaultConstructNImplTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
#else
	EXPECT_TRUE(test());
#endif

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<S3> alloc;
		auto* p = alloc.allocate(10);
		EXPECT_ANY_THROW(hamon::detail::uninitialized_default_construct_n_impl(p, 3));
		alloc.deallocate(p, 10);
	}
#endif
}

}	// namespace uninitialized_default_construct_n_impl_test

}	// namespace hamon_memory_test
