/**
 *	@file	unit_test_priority_queue_top.cpp
 *
 *	@brief	top のテスト
 *
 *	constexpr const_reference top() const;
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <deque>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_priority_queue_test
{

namespace top_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;
		using ConstReference = typename Queue::const_reference;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue      &>().top()), ConstReference>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().top()), ConstReference>::value, "");

		static_assert( noexcept(hamon::declval<Queue      &>().top()) == noexcept(hamon::declval<Container      &>().front()), "");
		static_assert( noexcept(hamon::declval<Queue const&>().top()) == noexcept(hamon::declval<Container const&>().front()), "");

		Queue q;

		q.push(T{2});
		VERIFY(q.size() == 1);
		VERIFY(q.top() == T{2});

		q.push(T{7});
		VERIFY(q.size() == 2);
		VERIFY(q.top() == T{7});

		q.push(T{1});
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{7});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;
		using ConstReference = typename Queue::const_reference;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue      &>().top()), ConstReference>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().top()), ConstReference>::value, "");

		static_assert(noexcept(hamon::declval<Queue      &>().top()) == noexcept(hamon::declval<Container      &>().front()), "");
		static_assert(noexcept(hamon::declval<Queue const&>().top()) == noexcept(hamon::declval<Container const&>().front()), "");

		Queue q;

		q.push(T{2});
		VERIFY(q.size() == 1);
		VERIFY(q.top() == T{2});

		q.push(T{7});
		VERIFY(q.size() == 2);
		VERIFY(q.top() == T{2});

		q.push(T{1});
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{1});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, TopTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int>>()));
	EXPECT_TRUE((test<float, std::deque<float>>()));

	EXPECT_TRUE((test<int,   std::vector<int>>()));
	EXPECT_TRUE((test<float, std::vector<float>>()));
}

}	// namespace top_test

}	// namespace hamon_priority_queue_test
