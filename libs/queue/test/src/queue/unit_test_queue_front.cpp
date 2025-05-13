/**
 *	@file	unit_test_queue_front.cpp
 *
 *	@brief	front のテスト
 *
 *	constexpr reference       front();
 *	constexpr const_reference front() const;
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

namespace front_test
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
	using Reference = typename Queue::reference;
	using ConstReference = typename Queue::const_reference;

	static_assert(hamon::is_same<decltype(hamon::declval<Queue      &>().front()), Reference>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().front()), ConstReference>::value, "");

#if !defined(HAMON_USE_STD_QUEUE)
	static_assert(noexcept(hamon::declval<Queue      &>().front()) == noexcept(hamon::declval<Container      &>().front()), "");
	static_assert(noexcept(hamon::declval<Queue const&>().front()) == noexcept(hamon::declval<Container const&>().front()), "");
#endif

	{
		Queue q;

		q.push(T{10});
		VERIFY(q.size() == 1);
		VERIFY(q.front() == T{10});

		q.front() = T{20};
		VERIFY(q.size() == 1);
		VERIFY(q.front() == T{20});

		q.push(T{30});
		VERIFY(q.size() == 2);
		VERIFY(q.front() == T{20});

		q.pop();
		VERIFY(q.size() == 1);
		VERIFY(q.front() == T{30});
	}
	{
		Container const c{T{10}, T{20}, T{30}};
		Queue const q{c};
		VERIFY(q.size() == 3);
		VERIFY(q.front() == T{10});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, FrontTest)
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

}	// namespace front_test

}	// namespace hamon_queue_test
