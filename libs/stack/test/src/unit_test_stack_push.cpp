/**
 *	@file	unit_test_stack_push.cpp
 *
 *	@brief	push のテスト
 *
 *	constexpr void push(const value_type& x);
 *	constexpr void push(value_type&& x);
 */

#include <hamon/stack/stack.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <deque>
#include <list>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_stack_test
{

namespace push_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Stack = hamon::stack<T, Container>;
	using ValueType = typename Stack::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Stack&>().push(hamon::declval<ValueType const&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack&>().push(hamon::declval<ValueType&&>())), void>::value, "");

	static_assert(!noexcept(hamon::declval<Stack&>().push(hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Stack&>().push(hamon::declval<ValueType&&>())), "");

	Stack s;
	VERIFY(s.empty());
	s.push(T{10});
	VERIFY(s.size() == 1);
	VERIFY(s.top() == T{10});
	T const x{20};
	s.push(x);
	VERIFY(s.size() == 2);
	VERIFY(s.top() == T{20});

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, PushTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));
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

}	// namespace push_test

}	// namespace hamon_stack_test
