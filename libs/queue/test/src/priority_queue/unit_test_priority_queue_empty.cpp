/**
 *	@file	unit_test_priority_queue_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	constexpr bool empty() const;
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

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, typename Compare>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Queue = hamon::priority_queue<T, Container, Compare>;

	static_assert(hamon::is_same<decltype(hamon::declval<Queue      &>().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue const&>().empty()), bool>::value, "");

	static_assert(noexcept(hamon::declval<Queue      &>().empty()) == noexcept(hamon::declval<Container      &>().empty()), "");
	static_assert(noexcept(hamon::declval<Queue const&>().empty()) == noexcept(hamon::declval<Container const&>().empty()), "");

	{
		Container const c{T{10}, T{20}, T{30}};
		Queue const q(Compare{}, c);
		VERIFY(!q.empty());
	}
	{
		Queue const q;
		VERIFY(q.empty());
	}

	return true;
}

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, Container, hamon::less<T>>()));
	VERIFY((test_impl<T, Container, hamon::greater<T>>()));
	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, EmptyTest)
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

}	// namespace empty_test

}	// namespace hamon_priority_queue_test
