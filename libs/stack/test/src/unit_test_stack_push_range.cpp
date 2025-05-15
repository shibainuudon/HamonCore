/**
 *	@file	unit_test_stack_push_range.cpp
 *
 *	@brief	push_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr void push_range(R&& rg);
 */

#include <hamon/stack/stack.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_STACK) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_stack_test
{

namespace push_range_test
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

template <typename T, typename Container, template <typename> class RangeWrapper>
STACK_TEST_CONSTEXPR bool test_impl()
{
	using Stack = hamon::stack<T, Container>;
	using Range = RangeWrapper<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Stack&>().push_range(hamon::declval<Range const&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Stack&>().push_range(hamon::declval<Range&&>())), void>::value, "");

#if !defined(HAMON_USE_STD_STACK)
	static_assert(!noexcept(hamon::declval<Stack&>().push_range(hamon::declval<Range const&>())), "");
	static_assert(!noexcept(hamon::declval<Stack&>().push_range(hamon::declval<Range&&>())), "");
#endif

	Stack s;
	VERIFY(s.empty());

	{
		T v[] = { T{1}, T{2}, T{3}, };
		Range const r(v);
		s.push_range(r);
	}

	VERIFY(s.size() == 3);
	VERIFY(s.top() == T{3});

	{
		T v[] = { T{4}, T{5}, };
		s.push_range(Range{v});
	}

	VERIFY(s.size() == 5);
	VERIFY(s.top() == T{5});

	return true;
}

template <typename T, typename Container>
STACK_TEST_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, Container, test_input_range>()));
	VERIFY((test_impl<T, Container, test_forward_range>()));
	VERIFY((test_impl<T, Container, test_bidirectional_range>()));
	VERIFY((test_impl<T, Container, test_random_access_range>()));
	VERIFY((test_impl<T, Container, test_contiguous_range>()));
	VERIFY((test_impl<T, Container, test_input_sized_range>()));
	VERIFY((test_impl<T, Container, test_forward_sized_range>()));
	VERIFY((test_impl<T, Container, test_bidirectional_sized_range>()));
	VERIFY((test_impl<T, Container, test_random_access_sized_range>()));
	VERIFY((test_impl<T, Container, test_contiguous_sized_range>()));
	return true;
}

#undef VERIFY

GTEST_TEST(StackTest, PushRangeTest)
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

}	// namespace push_range_test

}	// namespace hamon_stack_test

#endif
