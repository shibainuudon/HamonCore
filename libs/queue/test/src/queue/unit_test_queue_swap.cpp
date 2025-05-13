/**
 *	@file	unit_test_queue_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(queue& q);
 *
 *	template<class T, class Container>
 *	constexpr void swap(queue<T, Container>& x, queue<T, Container>& y);
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

namespace swap_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().swap(hamon::declval<Queue&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<Queue&>(), hamon::declval<Queue&>())), void>::value, "");

	static_assert(noexcept(hamon::declval<Queue&>().swap(hamon::declval<Queue&>())), "");
	static_assert(noexcept(swap(hamon::declval<Queue&>(), hamon::declval<Queue&>())), "");

	Queue q1;
	q1.push(T{1});
	q1.push(T{2});
	q1.push(T{3});

	Queue q2;
	q2.push(T{4});
	q2.push(T{5});

	q1.swap(q2);

	VERIFY(q1.size()  == 2);
	VERIFY(q1.front() == T{4});
	VERIFY(q1.back()  == T{5});
	VERIFY(q2.size()  == 3);
	VERIFY(q2.front() == T{1});
	VERIFY(q2.back()  == T{3});

	swap(q1, q2);

	VERIFY(q1.size()  == 3);
	VERIFY(q1.front() == T{1});
	VERIFY(q1.back()  == T{3});
	VERIFY(q2.size()  == 2);
	VERIFY(q2.front() == T{4});
	VERIFY(q2.back()  == T{5});

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, SwapTest)
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

}	// namespace swap_test

}	// namespace hamon_queue_test
