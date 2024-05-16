/**
 *	@file	unit_test_memory_detail_uninitialized_fill_n_impl.cpp
 *
 *	@brief	detail::uninitialized_fill_n_impl のテスト
 */

#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_fill_n_impl_test
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

	S1(S1&&) = delete;
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
		if (value == 0)
		{
			throw 0;
		}
	}

	S2(S2&&) = delete;
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
		T const x{42};
		hamon::detail::uninitialized_fill_n_impl(p, 3, x);
		VERIFY(p[0].value == 42);
		VERIFY(p[1].value == 42);
		VERIFY(p[2].value == 42);
		alloc.deallocate(p, 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedFillNImplTest)
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
		S1 const x{0};
		hamon::detail::uninitialized_fill_n_impl(p, 3, x);
		EXPECT_TRUE(p[0].value == 0);
		EXPECT_TRUE(p[1].value == 0);
		EXPECT_TRUE(p[2].value == 0);
		alloc.deallocate(p, 10);
	}
	{
		std::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		S2 const x{0};
		EXPECT_ANY_THROW(hamon::detail::uninitialized_fill_n_impl(p, 3, x));
		alloc.deallocate(p, 10);
	}
}

}	// namespace uninitialized_fill_n_impl_test

}	// namespace hamon_memory_test
