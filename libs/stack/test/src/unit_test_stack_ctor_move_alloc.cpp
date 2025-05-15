/**
 *	@file	unit_test_stack_ctor_move_alloc.cpp
 *
 *	@brief	stack&& と Alloc を引数に取るコンストラクタのテスト
 *
 *	template<class Alloc> constexpr stack(stack&&, const Alloc&);
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
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "stack_test_helper.hpp"

namespace hamon_stack_test
{

namespace ctor_move_alloc_test
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
	using Alloc = TestAllocator<T>;

	static_assert( hamon::is_constructible<Stack, Stack&&, Alloc const&>::value, "");
#if !defined(HAMON_USE_STD_STACK)
	static_assert(
		hamon::is_nothrow_constructible<Stack,     Stack&&,     Alloc const&>::value ==
		hamon::is_nothrow_constructible<Container, Container&&, Alloc const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Stack, Stack&&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Stack, Stack&&, Alloc const&>::value, "");

	Container const c{T{2}, T{3}, T{1}};
	Stack s1(c);

	Alloc a{};
	Stack const s2(hamon::move(s1), a);

	VERIFY(!s2.empty());
	VERIFY(s2.size()  == 3);
	VERIFY(s2.top() == T{1});

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, CtorMoveAllocTest)
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

	EXPECT_TRUE((test<int,   std::deque<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::deque<float, hamon::allocator<float>>>()));

	EXPECT_TRUE((test<int,   std::vector<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::vector<float, hamon::allocator<float>>>()));

	EXPECT_TRUE((test<int,   std::list<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::list<float, hamon::allocator<float>>>()));
}

#undef STACK_TEST_CONSTEXPR_EXPECT_TRUE
#undef STACK_TEST_CONSTEXPR

}	// namespace ctor_move_alloc_test

}	// namespace hamon_stack_test
