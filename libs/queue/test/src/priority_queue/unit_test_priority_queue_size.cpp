/**
 *	@file	unit_test_priority_queue_size.cpp
 *
 *	@brief	size のテスト
 *
 *	constexpr size_type size() const;
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

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;
		using SizeType = typename Queue::size_type;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue      &>().size()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().size()), SizeType>::value, "");

		static_assert(noexcept(hamon::declval<Queue      &>().size()) == noexcept(hamon::declval<Container      &>().size()), "");
		static_assert(noexcept(hamon::declval<Queue const&>().size()) == noexcept(hamon::declval<Container const&>().size()), "");

		Queue q;
		VERIFY(q.size() == 0);
		q.push(T{1});
		VERIFY(q.size() == 1);
		q.push(T{1});
		VERIFY(q.size() == 2);
		q.push(T{1});
		VERIFY(q.size() == 3);
		q.pop();
		VERIFY(q.size() == 2);
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;
		using SizeType = typename Queue::size_type;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue      &>().size()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().size()), SizeType>::value, "");

		static_assert(noexcept(hamon::declval<Queue      &>().size()) == noexcept(hamon::declval<Container      &>().size()), "");
		static_assert(noexcept(hamon::declval<Queue const&>().size()) == noexcept(hamon::declval<Container const&>().size()), "");

		Queue q;
		VERIFY(q.size() == 0);
		q.push(T{1});
		VERIFY(q.size() == 1);
		q.push(T{1});
		VERIFY(q.size() == 2);
		q.push(T{1});
		VERIFY(q.size() == 3);
		q.pop();
		VERIFY(q.size() == 2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, SizeTest)
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

}	// namespace size_test

}	// namespace hamon_priority_queue_test
