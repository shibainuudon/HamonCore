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
#include "constexpr_test.hpp"

namespace hamon_priority_queue_test
{

namespace size_test
{

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)
#define PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define PRIORITY_QUEUE_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define PRIORITY_QUEUE_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test()
{
	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;
		using SizeType = typename Queue::size_type;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue      &>().size()), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().size()), SizeType>::value, "");

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)
		static_assert(noexcept(hamon::declval<Queue      &>().size()) == noexcept(hamon::declval<Container      &>().size()), "");
		static_assert(noexcept(hamon::declval<Queue const&>().size()) == noexcept(hamon::declval<Container const&>().size()), "");
#endif

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

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)
		static_assert(noexcept(hamon::declval<Queue      &>().size()) == noexcept(hamon::declval<Container      &>().size()), "");
		static_assert(noexcept(hamon::declval<Queue const&>().size()) == noexcept(hamon::declval<Container const&>().size()), "");
#endif

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
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int>>()));
	EXPECT_TRUE((test<float, std::deque<float>>()));

	EXPECT_TRUE((test<int,   std::vector<int>>()));
	EXPECT_TRUE((test<float, std::vector<float>>()));
}

#undef RIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef RIORITY_QUEUE_TEST_CONSTEXPR

}	// namespace size_test

}	// namespace hamon_priority_queue_test
