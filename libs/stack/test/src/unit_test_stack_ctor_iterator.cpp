/**
 *	@file	unit_test_stack_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr stack(InputIterator first, InputIterator last);
 */

#include <hamon/stack/stack.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

#if !defined(HAMON_USE_STD_STACK) || \
	(defined(__cpp_lib_adaptor_iterator_pair_constructor) && (__cpp_lib_adaptor_iterator_pair_constructor >= 202106L))

namespace hamon_stack_test
{

namespace ctor_iterator_test
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

	static_assert( hamon::is_constructible<Stack, Iterator, Iterator>::value, "");
#if !defined(HAMON_USE_STD_STACK)
	static_assert(
		hamon::is_nothrow_constructible<Stack,     Iterator, Iterator>::value ==
		hamon::is_nothrow_constructible<Container, Iterator, Iterator>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Stack, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Stack, Iterator, Iterator>::value, "");

	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	Stack const s(Iterator{v}, Iterator{v+4});
	VERIFY(!s.empty());
	VERIFY(s.size()  == 4);
	VERIFY(s.top()  == T{3});

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

GTEST_TEST(StackTest, CtorIteratorTest)
{
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int>>()));
	EXPECT_TRUE((test<float, std::deque<float>>()));

	EXPECT_TRUE((test<int,   std::vector<int>>()));
	EXPECT_TRUE((test<float, std::vector<float>>()));

	EXPECT_TRUE((test<int,   std::list<int>>()));
	EXPECT_TRUE((test<float, std::list<float>>()));
}

#undef STACK_TEST_CONSTEXPR_EXPECT_TRUE
#undef STACK_TEST_CONSTEXPR

}	// namespace ctor_iterator_test

}	// namespace hamon_stack_test

#endif
