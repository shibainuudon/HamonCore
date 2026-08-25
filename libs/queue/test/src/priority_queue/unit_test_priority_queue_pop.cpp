/**
 *	@file	unit_test_priority_queue_pop.cpp
 *
 *	@brief	pop のテスト
 *
 *	constexpr void pop();
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

namespace pop_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().pop()), void>::value, "");
		static_assert(!noexcept(hamon::declval<Queue&>().pop()), "");

		Container const c{T{10}, T{20}, T{30}};
		Queue q{Compare{}, c};
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{30});

		q.pop();
		VERIFY(q.size() == 2);
		VERIFY(q.top() == T{20});

		q.pop();
		VERIFY(q.size() == 1);
		VERIFY(q.top() == T{10});

		q.pop();
		VERIFY(q.size() == 0);
		VERIFY(q.empty());
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().pop()), void>::value, "");
		static_assert(!noexcept(hamon::declval<Queue&>().pop()), "");

		Container const c{T{3}, T{1}, T{4}, T{1}};
		Queue q{Compare{}, c};
		VERIFY(q.size() == 4);
		VERIFY(q.top() == T{1});

		q.pop();
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{1});

		q.pop();
		VERIFY(q.size() == 2);
		VERIFY(q.top() == T{3});

		q.pop();
		VERIFY(q.size() == 1);
		VERIFY(q.top() == T{4});

		q.pop();
		VERIFY(q.size() == 0);
		VERIFY(q.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, PopTest)
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

}	// namespace pop_test

}	// namespace hamon_priority_queue_test
