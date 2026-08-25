/**
 *	@file	unit_test_stack_pop.cpp
 *
 *	@brief	pop のテスト
 *
 *	constexpr void pop();
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

namespace pop_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Stack = hamon::stack<T, Container>;

	static_assert(hamon::is_same<decltype(hamon::declval<Stack&>().pop()), void>::value, "");

	static_assert(noexcept(hamon::declval<Stack&>().pop()) == noexcept(hamon::declval<Container&>().pop_back()), "");

	Container const c{T{10}, T{20}, T{30}};
	Stack s{c};
	VERIFY(s.size()  == 3);
	VERIFY(s.top()  == T{30});

	s.pop();
	VERIFY(s.size()  == 2);
	VERIFY(s.top()  == T{20});

	s.pop();
	VERIFY(s.size()  == 1);
	VERIFY(s.top()  == T{10});

	s.pop();
	VERIFY(s.size() == 0);
	VERIFY(s.empty());

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, PopTest)
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

}	// namespace pop_test

}	// namespace hamon_stack_test
