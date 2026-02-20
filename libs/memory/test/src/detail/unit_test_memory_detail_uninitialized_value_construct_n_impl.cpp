/**
 *	@file	unit_test_memory_detail_uninitialized_value_construct_n_impl.cpp
 *
 *	@brief	detail::uninitialized_value_construct_n_impl のテスト
 */

#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/memory/allocator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_value_construct_n_impl_test
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
MEMORY_TEST_CONSTEXPR bool test1_impl()
{
	{
		using Iterator = IteratorWrapper<S0>;
		hamon::allocator<S0> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_value_construct_n_impl(Iterator{p}, 2);
		VERIFY(base(ret) == p + 2);
		VERIFY(p[0].value == 0);
		VERIFY(p[1].value == 0);
		alloc.deallocate(p, 10);
	}
	{
		using Iterator = IteratorWrapper<S1>;
		hamon::allocator<S1> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_value_construct_n_impl(Iterator{p}, 3);
		VERIFY(base(ret) == p + 3);
		VERIFY(p[0].value == 42);
		VERIFY(p[1].value == 42);
		VERIFY(p[2].value == 42);
		alloc.deallocate(p, 10);
	}
	{
		using Iterator = IteratorWrapper<S2>;
		hamon::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		auto ret = hamon::detail::uninitialized_value_construct_n_impl(Iterator{p}, 4);
		VERIFY(base(ret) == p + 4);
		VERIFY(p[0].value == 43);
		VERIFY(p[1].value == 43);
		VERIFY(p[2].value == 43);
		VERIFY(p[3].value == 43);
		alloc.deallocate(p, 10);
	}
	return true;
}

MEMORY_TEST_CONSTEXPR bool test1()
{
	return
		test1_impl<forward_iterator_wrapper>() &&
		test1_impl<bidirectional_iterator_wrapper>() &&
		test1_impl<random_access_iterator_wrapper>() &&
		test1_impl<contiguous_iterator_wrapper>();
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		T buf[5]{};
		auto ret = hamon::detail::uninitialized_value_construct_n_impl(buf, 5);
		VERIFY(ret == buf + 5);
		VERIFY(buf[0] == T{});
		VERIFY(buf[1] == T{});
		VERIFY(buf[2] == T{});
		VERIFY(buf[3] == T{});
		VERIFY(buf[4] == T{});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedValueConstructNImplTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test1());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<short>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<int>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::allocator<S3> alloc;
		auto* p = alloc.allocate(10);
		EXPECT_ANY_THROW(hamon::detail::uninitialized_value_construct_n_impl(p, 3));
		alloc.deallocate(p, 10);
	}
#endif
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace uninitialized_value_construct_n_impl_test

}	// namespace hamon_memory_test
