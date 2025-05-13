/**
 *	@file	unit_test_queue_size.cpp
 *
 *	@brief	size のテスト
 *
 *	constexpr size_type size() const;
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

namespace size_test
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
	using SizeType = typename Queue::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().size()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().size()), SizeType>::value, "");

#if !defined(HAMON_USE_STD_QUEUE)
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

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, SizeTest)
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

}	// namespace size_test

}	// namespace hamon_queue_test
