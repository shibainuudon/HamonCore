/**
 *	@file	unit_test_memory_detail_uninitialized_default_construct_n_impl.cpp
 *
 *	@brief	detail::uninitialized_default_construct_n_impl のテスト
 */

#include <hamon/memory/detail/uninitialized_default_construct_n_impl.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_default_construct_n_impl_test
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

template <template <typename> class IteratorWrapper>
MEMORY_TEST_CONSTEXPR bool test1()
{
	{
		using Iterator = IteratorWrapper<S0>;
		std::allocator<S0> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_default_construct_n_impl(Iterator{p}, 2);
		VERIFY(base(ret) == p + 2);
		alloc.deallocate(p, 10);
	}
	{
		using Iterator = IteratorWrapper<S1>;
		std::allocator<S1> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_default_construct_n_impl(Iterator{p}, 3);
		VERIFY(base(ret) == p + 3);
		VERIFY(p[0].value == 42);
		VERIFY(p[1].value == 42);
		VERIFY(p[2].value == 42);
		alloc.deallocate(p, 10);
	}
	{
		using Iterator = IteratorWrapper<S2>;
		std::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_default_construct_n_impl(Iterator{p}, 4);
		VERIFY(base(ret) == p + 4);
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
		test1<forward_iterator_wrapper>() &&
		test1<bidirectional_iterator_wrapper>() &&
		test1<random_access_iterator_wrapper>() &&
		test1<contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedDefaultConstructNImplTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<S3> alloc;
		auto* p = alloc.allocate(10);
		EXPECT_ANY_THROW(hamon::detail::uninitialized_default_construct_n_impl(p, 3));
		alloc.deallocate(p, 10);
	}
#endif
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace uninitialized_default_construct_n_impl_test

}	// namespace hamon_memory_test
