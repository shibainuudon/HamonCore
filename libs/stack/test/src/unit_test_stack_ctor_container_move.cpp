/**
 *	@file	unit_test_stack_ctor_container_move.cpp
 *
 *	@brief	Container&& を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit stack(Container&&);
 */

#include <hamon/stack/stack.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include <deque>
#include <list>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_stack_test
{

namespace ctor_container_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Stack = hamon::stack<T, Container>;

	static_assert( hamon::is_constructible<Stack, Container&&>::value, "");
	static_assert(
		hamon::is_nothrow_constructible<Stack,     Container&&>::value ==
		hamon::is_nothrow_constructible<Container, Container&&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Stack, Container&&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Stack, Container&&>::value, "");

	Container c{T{10}, T{20}, T{30}};
	Stack const s(hamon::move(c));

	VERIFY(!s.empty());
	VERIFY(s.size() == 3);
	VERIFY(s.top() == T{30});

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, CtorContainerMoveTest)
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

}	// namespace ctor_container_move_test

}	// namespace hamon_stack_test
