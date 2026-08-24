/**
 *	@file	unit_test_priority_queue_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args> constexpr void emplace(Args&&... args);
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_priority_queue_test
{

namespace emplace_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().emplace()), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().emplace(hamon::declval<T>())), void>::value, "");

		static_assert(!noexcept(hamon::declval<Queue&>().emplace()), "");
		static_assert(!noexcept(hamon::declval<Queue&>().emplace(hamon::declval<T>())), "");

		Queue q;

		q.emplace(T{3});

		VERIFY(q.size() == 1);
		VERIFY(q.top() == T{3});

		q.emplace(T{1});

		VERIFY(q.size() == 2);
		VERIFY(q.top() == T{3});

		q.emplace(T{4});

		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{4});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().emplace()), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().emplace(hamon::declval<T>())), void>::value, "");

		static_assert(!noexcept(hamon::declval<Queue&>().emplace()), "");
		static_assert(!noexcept(hamon::declval<Queue&>().emplace(hamon::declval<T>())), "");

		Queue q;

		q.emplace(T{3});

		VERIFY(q.size() == 1);
		VERIFY(q.top() == T{3});

		q.emplace(T{1});

		VERIFY(q.size() == 2);
		VERIFY(q.top() == T{1});

		q.emplace(T{4});

		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{1});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, EmplaceTest)
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

}	// namespace emplace_test

}	// namespace hamon_priority_queue_test
