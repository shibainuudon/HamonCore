/**
 *	@file	unit_test_stack_top.cpp
 *
 *	@brief	top のテスト
 *
 *	constexpr reference       top();
 *	constexpr const_reference top() const;
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

namespace top_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Stack = hamon::stack<T, Container>;
	using Reference = typename Stack::reference;
	using ConstReference = typename Stack::const_reference;

	static_assert(hamon::is_same<decltype(hamon::declval<Stack      &>().top()), Reference>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack const&>().top()), ConstReference>::value, "");

	static_assert(noexcept(hamon::declval<Stack      &>().top()) == noexcept(hamon::declval<Container      &>().back()), "");
	static_assert(noexcept(hamon::declval<Stack const&>().top()) == noexcept(hamon::declval<Container const&>().back()), "");

	{
		Stack s;
		s.push(T{3});
		VERIFY(s.top() == T{3});
		s.top() = T{4};
		s.push(T{5});
		VERIFY(s.top() == T{5});
		s.pop();
		VERIFY(s.top() == T{4});
	}
	{
		Container c{T{3}, T{1}, T{4}};
		Stack const s(c);
		VERIFY(s.top() == T{4});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, TopTest)
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

}	// namespace top_test

}	// namespace hamon_stack_test
