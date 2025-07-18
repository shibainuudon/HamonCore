/**
 *	@file	unit_test_memory_detail_uninitialized_move_if_noexcept_n.cpp
 *
 *	@brief	detail::uninitialized_move_if_noexcept_n のテスト
 */

#include <hamon/memory/detail/uninitialized_move_if_noexcept_n.hpp>
#include <hamon/memory/allocator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_memory_test
{

namespace uninitialized_move_if_noexcept_n_test
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

template <bool NoexceptMove>
struct S3
{
	static int s_copy_ctor_count;
	static int s_move_ctor_count;

	int value;

	HAMON_CXX14_CONSTEXPR
	S3(int v)
		: value(v)
	{}

	S3(S3 const& x)
		: value(x.value)
	{
		++s_copy_ctor_count;
	}

	HAMON_CXX14_CONSTEXPR
	S3(S3&& x) HAMON_NOEXCEPT_IF(NoexceptMove)
		: value(x.value)
	{
		++s_move_ctor_count;
	}

	S3& operator=(S3 const&) = delete;
	S3& operator=(S3&&) = delete;
};

template <bool NoexceptMove>
int S3<NoexceptMove>::s_copy_ctor_count = 0;

template <bool NoexceptMove>
int S3<NoexceptMove>::s_move_ctor_count = 0;

template <bool NoexceptMove>
struct S4
{
	static int s_move_ctor_count;

	int value;

	HAMON_CXX14_CONSTEXPR
	S4(int v)
		: value(v)
	{}

	S4(S4 const& x) = delete;

	HAMON_CXX14_CONSTEXPR
	S4(S4&& x) HAMON_NOEXCEPT_IF(NoexceptMove)
		: value(x.value)
	{
		++s_move_ctor_count;
	}

	S4& operator=(S4 const&) = delete;
	S4& operator=(S4&&) = delete;
};

template <bool NoexceptMove>
int S4<NoexceptMove>::s_move_ctor_count = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T,
	template <typename> class InputIteratorWrapper,
	template <typename> class OutputIteratorWrapper>
MEMORY_TEST_CONSTEXPR bool test2()
{
	{
		using InputIterator  = InputIteratorWrapper<T>;
		using OutputIterator = OutputIteratorWrapper<T>;
		hamon::allocator<T> alloc;
		auto* p = alloc.allocate(10);
		T a[] = { T{10}, T{20}, T{30} };
		auto ret = hamon::detail::uninitialized_move_if_noexcept_n(InputIterator{a}, 3, OutputIterator{p});
		VERIFY(base(ret.first)  == a + 3);
		VERIFY(base(ret.second) == p + 3);
		VERIFY(p[0].value == 10);
		VERIFY(p[1].value == 20);
		VERIFY(p[2].value == 30);
		alloc.deallocate(p, 10);
	}
	return true;
}

template <typename T, template <typename> class InputIteratorWrapper>
MEMORY_TEST_CONSTEXPR bool test1()
{
	return
		test2<T, InputIteratorWrapper, forward_iterator_wrapper>() &&
		test2<T, InputIteratorWrapper, bidirectional_iterator_wrapper>() &&
		test2<T, InputIteratorWrapper, random_access_iterator_wrapper>() &&
		test2<T, InputIteratorWrapper, contiguous_iterator_wrapper>();
}

template <typename T>
MEMORY_TEST_CONSTEXPR bool test()
{
	return
		test1<T, input_iterator_wrapper>() &&
		test1<T, forward_iterator_wrapper>() &&
		test1<T, bidirectional_iterator_wrapper>() &&
		test1<T, random_access_iterator_wrapper>() &&
		test1<T, contiguous_iterator_wrapper>();
}

#undef VERIFY

GTEST_TEST(MemoryTest, UninitializedMoveIfNoexceptNTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S0>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test<S2>());

	{
		hamon::allocator<S1> alloc;
		auto* p = alloc.allocate(10);
		S1 a[] = { 10, 20, 0 };
		auto ret = hamon::detail::uninitialized_move_if_noexcept_n(a, 3, p);
		EXPECT_TRUE(ret.first  == a + 3);
		EXPECT_TRUE(ret.second == p + 3);
		EXPECT_TRUE(p[0].value == 10);
		EXPECT_TRUE(p[1].value == 20);
		EXPECT_TRUE(p[2].value ==  0);
		alloc.deallocate(p, 10);
	}
	{
		using S = S3<true>;
		hamon::allocator<S> alloc;
		auto* p = alloc.allocate(10);
		S a[] = { 10, 20, 0 };
		S::s_copy_ctor_count = 0;
		S::s_move_ctor_count = 0;
		auto ret = hamon::detail::uninitialized_move_if_noexcept_n(a, 3, p);
		EXPECT_TRUE(ret.first  == a + 3);
		EXPECT_TRUE(ret.second == p + 3);
		EXPECT_EQ(0, S::s_copy_ctor_count);
		EXPECT_EQ(3, S::s_move_ctor_count);
		alloc.deallocate(p, 10);
	}
	{
		using S = S3<false>;
		hamon::allocator<S> alloc;
		auto* p = alloc.allocate(10);
		S a[] = { 10, 20, 0 };
		S::s_copy_ctor_count = 0;
		S::s_move_ctor_count = 0;
		auto ret = hamon::detail::uninitialized_move_if_noexcept_n(a, 3, p);
		EXPECT_TRUE(ret.first  == a + 3);
		EXPECT_TRUE(ret.second == p + 3);
		EXPECT_EQ(3, S::s_copy_ctor_count);
		EXPECT_EQ(0, S::s_move_ctor_count);
		alloc.deallocate(p, 10);
	}
	{
		using S = S4<true>;
		hamon::allocator<S> alloc;
		auto* p = alloc.allocate(10);
		S a[] = { 10, 20, 0 };
		S::s_move_ctor_count = 0;
		auto ret = hamon::detail::uninitialized_move_if_noexcept_n(a, 3, p);
		EXPECT_TRUE(ret.first  == a + 3);
		EXPECT_TRUE(ret.second == p + 3);
		EXPECT_EQ(3, S::s_move_ctor_count);
		alloc.deallocate(p, 10);
	}
	{
		using S = S4<false>;
		hamon::allocator<S> alloc;
		auto* p = alloc.allocate(10);
		S a[] = { 10, 20, 0 };
		S::s_move_ctor_count = 0;
		auto ret = hamon::detail::uninitialized_move_if_noexcept_n(a, 3, p);
		EXPECT_TRUE(ret.first  == a + 3);
		EXPECT_TRUE(ret.second == p + 3);
		EXPECT_EQ(3, S::s_move_ctor_count);
		alloc.deallocate(p, 10);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::allocator<S2> alloc;
		auto* p = alloc.allocate(10);
		S2 a[] = { 10, 20, 0 };
		EXPECT_ANY_THROW(hamon::detail::uninitialized_move_if_noexcept_n(a, 3, p));
		alloc.deallocate(p, 10);
	}
#endif
}

#undef MEMORY_TEST_CONSTEXPR
#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace uninitialized_move_if_noexcept_n_test

}	// namespace hamon_memory_test
