/**
 *	@file	unit_test_queue_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	constexpr bool empty() const;
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

namespace empty_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().empty()), bool>::value, "");

#if !defined(HAMON_USE_STD_QUEUE)
	static_assert(noexcept(hamon::declval<Queue      &>().empty()) == noexcept(hamon::declval<Container      &>().empty()), "");
	static_assert(noexcept(hamon::declval<Queue const&>().empty()) == noexcept(hamon::declval<Container const&>().empty()), "");
#endif

	{
		Container const c{T{10}, T{20}, T{30}};
		Queue const q(c);
		VERIFY(!q.empty());
	}
	{
		Container const c{};
		Queue const q(c);
		VERIFY(q.empty());
	}
	{
		Queue const q;
		VERIFY(q.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, EmptyTest)
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

}	// namespace empty_test

}	// namespace hamon_queue_test
