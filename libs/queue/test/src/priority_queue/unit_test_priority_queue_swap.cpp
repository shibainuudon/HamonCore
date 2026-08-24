/**
 *	@file	unit_test_priority_queue_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(priority_queue& q)
 *		noexcept(is_nothrow_swappable_v<Container> && is_nothrow_swappable_v<Compare>);
 *
 *	template<class T, class Container, class Compare>
 *	constexpr void swap(priority_queue<T, Container, Compare>& x,
 *						priority_queue<T, Container, Compare>& y) noexcept(noexcept(x.swap(y)));
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_priority_queue_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().swap(hamon::declval<Queue&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(hamon::declval<Queue&>(), hamon::declval<Queue&>())), void>::value, "");

//		static_assert(noexcept(hamon::declval<Queue&>().swap(hamon::declval<Queue&>())), "");
		static_assert(noexcept(swap(hamon::declval<Queue&>(), hamon::declval<Queue&>())), "");

		Queue q1;
		q1.push(T{1});
		q1.push(T{2});
		q1.push(T{3});

		Queue q2;
		q2.push(T{4});
		q2.push(T{5});

		q1.swap(q2);

		VERIFY(q1.size() == 2);
		VERIFY(q1.top() == T{5});
		VERIFY(q2.size() == 3);
		VERIFY(q2.top() == T{3});

		swap(q1, q2);

		VERIFY(q1.size() == 3);
		VERIFY(q1.top() == T{3});
		VERIFY(q2.size() == 2);
		VERIFY(q2.top() == T{5});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().swap(hamon::declval<Queue&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(hamon::declval<Queue&>(), hamon::declval<Queue&>())), void>::value, "");

//		static_assert(noexcept(hamon::declval<Queue&>().swap(hamon::declval<Queue&>())), "");
		static_assert(noexcept(swap(hamon::declval<Queue&>(), hamon::declval<Queue&>())), "");

		Queue q1;
		q1.push(T{1});
		q1.push(T{2});
		q1.push(T{3});

		Queue q2;
		q2.push(T{4});
		q2.push(T{5});

		q1.swap(q2);

		VERIFY(q1.size() == 2);
		VERIFY(q1.top() == T{4});
		VERIFY(q2.size() == 3);
		VERIFY(q2.top() == T{1});

		swap(q1, q2);

		VERIFY(q1.size() == 3);
		VERIFY(q1.top() == T{1});
		VERIFY(q2.size() == 2);
		VERIFY(q2.top() == T{4});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

	//EXPECT_TRUE((test<int,   std::deque<int>>()));
	//EXPECT_TRUE((test<float, std::deque<float>>()));

	//EXPECT_TRUE((test<int,   std::vector<int>>()));
	//EXPECT_TRUE((test<float, std::vector<float>>()));
}

}	// namespace swap_test

}	// namespace hamon_priority_queue_test
