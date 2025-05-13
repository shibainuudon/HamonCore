/**
 *	@file	unit_test_queue_push_range.cpp
 *
 *	@brief	push_range のテスト
 *
 *	template<container-compatible-range<T> R> constexpr void push_range(R&& rg);
 */

#include <hamon/queue/queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if !defined(HAMON_USE_STD_QUEUE) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_queue_test
{

namespace push_range_test
{

#if !defined(HAMON_USE_STD_QUEUE) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define QUEUE_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define QUEUE_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, template <typename> class RangeWrapper>
QUEUE_TEST_CONSTEXPR bool test_impl()
{
	using Queue = hamon::queue<T, Container>;
	using Range = RangeWrapper<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().push_range(hamon::declval<Range const&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().push_range(hamon::declval<Range&&>())), void>::value, "");

	static_assert(!noexcept(hamon::declval<Queue&>().push_range(hamon::declval<Range const&>())), "");
	static_assert(!noexcept(hamon::declval<Queue&>().push_range(hamon::declval<Range&&>())), "");

	Queue q;
	VERIFY(q.empty());

	{
		T v[] = { T{1}, T{2}, T{3}, };
		Range const r(v);
		q.push_range(r);
	}

	VERIFY(q.size()  == 3);
	VERIFY(q.front() == T{1});
	VERIFY(q.back()  == T{3});

	{
		T v[] = { T{4}, T{5}, };
		q.push_range(Range{v});
	}

	VERIFY(q.size()  == 5);
	VERIFY(q.front() == T{1});
	VERIFY(q.back()  == T{5});

	return true;
}

template <typename T, typename Container>
QUEUE_TEST_CONSTEXPR bool test()
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

GTEST_TEST(QueueTest, PushRangeTest)
{
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int>>()));
	EXPECT_TRUE((test<float, std::deque<float>>()));

	EXPECT_TRUE((test<int,   std::list<int>>()));
	EXPECT_TRUE((test<float, std::list<float>>()));
}

#undef QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef QUEUE_TEST_CONSTEXPR

}	// namespace push_range_test

}	// namespace hamon_queue_test

#endif
