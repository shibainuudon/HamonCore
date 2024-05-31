/**
 *	@file	unit_test_memory_detail_uninitialized_fill_n_impl.cpp
 *
 *	@brief	detail::uninitialized_fill_n_impl のテスト
 */

#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_fill_n_impl_test
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
#if !defined(HAMON_NO_EXCEPTIONS)
		if (value == 0)
		{
			throw 0;
		}
#endif
	}

	S2(S2&&) = delete;
	S2& operator=(S2 const&) = delete;
	S2& operator=(S2&&) = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class IteratorWrapper>
MEMORY_TEST_CONSTEXPR bool test1()
{
	{
		using Iterator = IteratorWrapper<T>;
		std::allocator<T> alloc;
		auto* p = alloc.allocate(10);
		T const x{42};
		auto ret = hamon::detail::uninitialized_fill_n_impl(Iterator{p}, 3, x);
		VERIFY(base(ret) == p + 3);
		VERIFY(p[0].value == 42);
		VERIFY(p[1].value == 42);
		VERIFY(p[2].value == 42);
		alloc.deallocate(p, 10);
	}
	return true;
}

template <typename T>
MEMORY_TEST_CONSTEXPR bool test()
{
	return
		test1<T, forward_iterator_wrapper>() &&
		test1<T, bidirectional_iterator_wrapper>() &&
		test1<T, random_access_iterator_wrapper>() &&
		test1<T, contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedFillNImplTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S0>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S2>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		S2 const x{0};
		EXPECT_ANY_THROW(hamon::detail::uninitialized_fill_n_impl(p, 3, x));
		alloc.deallocate(p, 10);
	}
#endif
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace uninitialized_fill_n_impl_test

}	// namespace hamon_memory_test
