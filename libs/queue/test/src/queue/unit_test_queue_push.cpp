/**
 *	@file	unit_test_queue_push.cpp
 *
 *	@brief	push のテスト
 *
 *	constexpr void push(const value_type& x);
 *	constexpr void push(value_type&& x);
 */

#include <hamon/queue/queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_queue_test
{

namespace push_test
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

template <typename T, typename Container>
QUEUE_TEST_CONSTEXPR bool test()
{
	using Queue = hamon::queue<T, Container>;
	using ValueType = typename Queue::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().push(hamon::declval<ValueType const&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().push(hamon::declval<ValueType&&>())), void>::value, "");

	static_assert(!noexcept(hamon::declval<Queue&>().push(hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Queue&>().push(hamon::declval<ValueType&&>())), "");

	{
		Container const c{T{10}, T{20}, T{30}};
		Queue q{c};
		VERIFY(q.size()  == 3);
		VERIFY(q.front() == T{10});
		VERIFY(q.back()  == T{30});

		q.push(T{40});
		VERIFY(q.size()  == 4);
		VERIFY(q.front() == T{10});
		VERIFY(q.back()  == T{40});

		T const x{50};
		q.push(x);
		VERIFY(q.size()  == 5);
		VERIFY(q.front() == T{10});
		VERIFY(q.back()  == T{50});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, PushTest)
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

}	// namespace push_test

}	// namespace hamon_queue_test
