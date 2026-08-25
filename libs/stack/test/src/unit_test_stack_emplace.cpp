/**
 *	@file	unit_test_stack_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args>
 *	constexpr decltype(auto) emplace(Args&&... args);
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

namespace emplace_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Stack = hamon::stack<T, Container>;

	using Reference = typename Stack::reference;
	static_assert(hamon::is_same<decltype(hamon::declval<Stack&>().emplace()), Reference>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack&>().emplace(hamon::declval<T>())), Reference>::value, "");

	static_assert(!noexcept(hamon::declval<Stack&>().emplace()), "");
	static_assert(!noexcept(hamon::declval<Stack&>().emplace(hamon::declval<T>())), "");

	Stack s;

	{
		auto& r = s.emplace(T{1});
		VERIFY(r == T{1});
	}

	VERIFY(s.size() == 1);
	VERIFY(s.top() == T{1});

	{
		auto& r = s.emplace(T{2});
		VERIFY(r == T{2});
	}

	VERIFY(s.size() == 2);
	VERIFY(s.top() == T{2});

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, EmplaceTest)
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

	//EXPECT_TRUE((test<int,   std::deque<int>>()));
	//EXPECT_TRUE((test<float, std::deque<float>>()));

	//EXPECT_TRUE((test<int,   std::vector<int>>()));
	//EXPECT_TRUE((test<float, std::vector<float>>()));

	//EXPECT_TRUE((test<int,   std::list<int>>()));
	//EXPECT_TRUE((test<float, std::list<float>>()));
}

}	// namespace emplace_test

}	// namespace hamon_stack_test
