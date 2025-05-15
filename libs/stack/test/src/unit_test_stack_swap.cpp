/**
 *	@file	unit_test_stack_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(stack& s)
 *		noexcept(is_nothrow_swappable_v<Container>);
 *
 *	template<class T, class Container>
 *	constexpr void swap(stack<T, Container>& x, stack<T, Container>& y)
 *		noexcept(noexcept(x.swap(y)));
 */

#include <hamon/stack/stack.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_stack_test
{

namespace swap_test
{

#if !defined(HAMON_USE_STD_STACK)
#define STACK_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define STACK_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define STACK_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define STACK_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
STACK_TEST_CONSTEXPR bool test()
{
	using Stack = hamon::stack<T, Container>;

	static_assert(hamon::is_same<decltype(hamon::declval<Stack&>().swap(hamon::declval<Stack&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<Stack&>(), hamon::declval<Stack&>())), void>::value, "");

	static_assert(noexcept(hamon::declval<Stack&>().swap(hamon::declval<Stack&>())), "");
	static_assert(noexcept(swap(hamon::declval<Stack&>(), hamon::declval<Stack&>())), "");

	Stack s1;
	s1.push(T{1});
	s1.push(T{2});
	s1.push(T{3});

	Stack s2;
	s2.push(T{4});
	s2.push(T{5});

	s1.swap(s2);

	VERIFY(s1.size() == 2);
	VERIFY(s1.top() == T{5});
	VERIFY(s2.size() == 3);
	VERIFY(s2.top() == T{3});

	swap(s1, s2);

	VERIFY(s1.size() == 3);
	VERIFY(s1.top() == T{3});
	VERIFY(s2.size() == 2);
	VERIFY(s2.top() == T{5});

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, SwapTest)
{
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));
#else
	EXPECT_TRUE((test<int,   hamon::list<int>>()));
	EXPECT_TRUE((test<float, hamon::list<float>>()));
#endif

	EXPECT_TRUE((test<int,   std::deque<int>>()));
	EXPECT_TRUE((test<float, std::deque<float>>()));

	EXPECT_TRUE((test<int,   std::vector<int>>()));
	EXPECT_TRUE((test<float, std::vector<float>>()));

	EXPECT_TRUE((test<int,   std::list<int>>()));
	EXPECT_TRUE((test<float, std::list<float>>()));
}

#undef STACK_TEST_CONSTEXPR_EXPECT_TRUE
#undef STACK_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_stack_test
