/**
 *	@file	unit_test_stack_ctor_container_copy.cpp
 *
 *	@brief	const Container& を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit stack(const Container&);
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

namespace hamon_stack_test
{

namespace ctor_container_copy_test
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

	static_assert( hamon::is_constructible<Stack, Container const&>::value, "");
#if !defined(HAMON_USE_STD_STACK)
	static_assert(
		hamon::is_nothrow_constructible<Stack,     Container const&>::value ==
		hamon::is_nothrow_constructible<Container, Container const&>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<Stack, Container const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Stack, Container const&>::value, "");

	Container const c{T{10}, T{20}, T{30}};
	Stack const s(c);

	VERIFY(!s.empty());
	VERIFY(s.size() == 3);
	VERIFY(s.top() == T{30});

	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, CtorContainerCopyTest)
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

}	// namespace ctor_container_copy_test

}	// namespace hamon_stack_test
