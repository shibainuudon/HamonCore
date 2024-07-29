/**
 *	@file	unit_test_memory_detail_uninitialized_move_impl.cpp
 *
 *	@brief	detail::uninitialized_move_impl のテスト
 */

#include <hamon/memory/detail/uninitialized_move_impl.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_move_impl_test
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

	S1(S1 const&) = delete;

	HAMON_CXX14_CONSTEXPR
	S1(S1&& x) HAMON_NOEXCEPT
		: value(x.value)
	{
	}

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

	S2(S2 const&) = delete;

	HAMON_CXX14_CONSTEXPR
	S2(S2&& x)
		: value(x.value)
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		if (value == 0)
		{
			throw 0;
		}
#endif
	}

	S2& operator=(S2 const&) = delete;
	S2& operator=(S2&&) = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T,
	template <typename> class InputRangeWrapper,
	template <typename> class OutputIteratorWrapper>
MEMORY_TEST_CONSTEXPR bool test2()
{
	{
		using InputRange  = InputRangeWrapper<T>;
		using OutputIterator = OutputIteratorWrapper<T>;
		std::allocator<T> alloc;
		auto* p = alloc.allocate(10);
		T a[] = { T{10}, T{20}, T{30} };
		InputRange r(a);
		auto ret = hamon::detail::uninitialized_move_impl(r.begin(), r.end(), OutputIterator{p});
		VERIFY(base(ret.in)  == a + 3);
		VERIFY(base(ret.out) == p + 3);
		VERIFY(p[0].value == 10);
		VERIFY(p[1].value == 20);
		VERIFY(p[2].value == 30);
		alloc.deallocate(p, 10);
	}
	return true;
}

template <typename T, template <typename> class InputRangeWrapper>
MEMORY_TEST_CONSTEXPR bool test1()
{
	return
		test2<T, InputRangeWrapper, forward_iterator_wrapper>() &&
		test2<T, InputRangeWrapper, bidirectional_iterator_wrapper>() &&
		test2<T, InputRangeWrapper, random_access_iterator_wrapper>() &&
		test2<T, InputRangeWrapper, contiguous_iterator_wrapper>();
}

template <typename T>
MEMORY_TEST_CONSTEXPR bool test()
{
	return
		test1<T, test_input_range>() &&
		test1<T, test_forward_range>() &&
		test1<T, test_bidirectional_range>() &&
		test1<T, test_random_access_range>() &&
		test1<T, test_contiguous_range>() &&
		test1<T, test_input_common_range>() &&
		test1<T, test_forward_common_range>() &&
		test1<T, test_bidirectional_common_range>() &&
		test1<T, test_random_access_common_range>() &&
		test1<T, test_contiguous_common_range>();
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedMoveImplTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S0>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S2>());

	{
		std::allocator<S1> alloc;
		auto* p = alloc.allocate(10);
		S1 a[] = { 10, 20, 0 };
		auto ret = hamon::detail::uninitialized_move_impl(a, a + 3, p);
		EXPECT_TRUE(ret.in  == a + 3);
		EXPECT_TRUE(ret.out == p + 3);
		EXPECT_TRUE(p[0].value == 10);
		EXPECT_TRUE(p[1].value == 20);
		EXPECT_TRUE(p[2].value ==  0);
		alloc.deallocate(p, 10);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		std::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		S2 a[] = { 10, 20, 0 };
		EXPECT_ANY_THROW(hamon::detail::uninitialized_move_impl(a, a + 3, p));
		alloc.deallocate(p, 10);
	}
#endif
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace uninitialized_move_impl_test

}	// namespace hamon_memory_test
