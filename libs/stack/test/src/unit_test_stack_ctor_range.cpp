/**
 *	@file	unit_test_stack_ctor_range.cpp
 *
 *	@brief	range を引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr stack(from_range_t, R&& rg);
 */

#include <hamon/stack/stack.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_STACK) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_stack_test
{

namespace ctor_range_test
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

	static_assert( hamon::is_constructible<Stack, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Stack, hamon::from_range_t, Range>::value, "");
	static_assert( hamon::is_implicitly_constructible<Stack, hamon::from_range_t, Range>::value, "");
	static_assert(!hamon::is_trivially_constructible<Stack, hamon::from_range_t, Range>::value, "");

	T v[] = { T{1}, T{2}, T{3}, T{4}, T{5}, };
	Range r(v);
	Stack const s(hamon::from_range, r);
	VERIFY(!s.empty());
	VERIFY(s.size()  == 5);
	VERIFY(s.top()  == T{5});

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

GTEST_TEST(StackTest, CtorRangeTest)
{
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

#if defined(HAMON_GCC)
	// 原因はわからないが、gccでconstexprにするとコンパイルエラーになる
	EXPECT_TRUE((test<int,   hamon::list<int>>()));
	EXPECT_TRUE((test<float, hamon::list<float>>()));
#else
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	STACK_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));
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

}	// namespace ctor_range_test

}	// namespace hamon_stack_test

#endif
