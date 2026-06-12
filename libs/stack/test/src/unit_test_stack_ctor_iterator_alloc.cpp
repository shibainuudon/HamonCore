/**
 *	@file	unit_test_stack_ctor_iterator_alloc.cpp
 *
 *	@brief	イテレータと Alloc を引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr stack(InputIterator first, InputIterator last, const Alloc&);
 */

#include <hamon/stack/stack.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "stack_test_helper.hpp"

#if !defined(HAMON_USE_STD_STACK) || \
	(defined(__cpp_lib_adaptor_iterator_pair_constructor) && (__cpp_lib_adaptor_iterator_pair_constructor >= 202106L))

namespace hamon_stack_test
{

namespace ctor_iterator_alloc_test
{

#if !defined(HAMON_USE_STD_STACK) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define STACK_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define STACK_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define STACK_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define STACK_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, template <typename> class IteratorWrapper>
STACK_TEST_CONSTEXPR bool test_impl()
{
	using Stack = hamon::stack<T, Container>;
	using Iterator = IteratorWrapper<T>;
	using Alloc = TestAllocator<T>;

	static_assert( hamon::is_constructible<Stack, Iterator, Iterator, Alloc const&>::value, "");
#if !defined(HAMON_USE_STD_STACK)
	static_assert(
		hamon::is_nothrow_constructible<Stack,     Iterator, Iterator, Alloc const&>::value ==
		hamon::is_nothrow_constructible<Container, Iterator, Iterator, Alloc const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Stack, Iterator, Iterator, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Stack, Iterator, Iterator, Alloc const&>::value, "");

	T v[] = { T{10}, T{9}, T{8}, T{7}, };
	Alloc a{};
	Stack const s(Iterator{v}, Iterator{v+4}, a);

	VERIFY(!s.empty());
	VERIFY(s.size() == 4);
	VERIFY(s.top() == T{7});

	return true;
}

template <typename T, typename Container>
STACK_TEST_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, Container, cpp17_input_iterator_wrapper>()));
//	VERIFY((test_impl<T, Container, input_iterator_wrapper>()));
	VERIFY((test_impl<T, Container, forward_iterator_wrapper>()));
	VERIFY((test_impl<T, Container, bidirectional_iterator_wrapper>()));
	VERIFY((test_impl<T, Container, random_access_iterator_wrapper>()));
	VERIFY((test_impl<T, Container, contiguous_iterator_wrapper>()));
	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, CtorIteratorAllocTest)
{
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::deque<float, hamon::allocator<float>>>()));

	EXPECT_TRUE((test<int,   std::vector<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::vector<float, hamon::allocator<float>>>()));

	EXPECT_TRUE((test<int,   std::list<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::list<float, hamon::allocator<float>>>()));
}

#undef STACK_TEST_CONSTEXPR_EXPECT_TRUE
#undef STACK_TEST_CONSTEXPR

}	// namespace ctor_iterator_alloc_test

}	// namespace hamon_stack_test

#endif
