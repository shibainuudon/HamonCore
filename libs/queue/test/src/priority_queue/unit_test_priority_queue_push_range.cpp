/**
 *	@file	unit_test_priority_queue_push_range.cpp
 *
 *	@brief	push_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr void push_range(R&& rg);
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
#include "ranges_test.hpp"

namespace hamon_priority_queue_test
{

namespace push_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Range = RangeWrapper<T>;
	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().push_range(hamon::declval<Range const&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().push_range(hamon::declval<Range&&>())), void>::value, "");

		static_assert(!noexcept(hamon::declval<Queue&>().push_range(hamon::declval<Range const&>())), "");
		static_assert(!noexcept(hamon::declval<Queue&>().push_range(hamon::declval<Range&&>())), "");

		Queue q;
		VERIFY(q.empty());

		{
			T v[] = { T{1}, T{2}, T{3}, };
			Range const r(v);
			q.push_range(r);
		}
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{3});

		{
			T v[] = { T{0}, T{4}, };
			Range const r(v);
			q.push_range(r);
		}
		VERIFY(q.size() == 5);
		VERIFY(q.top() == T{4});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().push_range(hamon::declval<Range const&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().push_range(hamon::declval<Range&&>())), void>::value, "");

		static_assert(!noexcept(hamon::declval<Queue&>().push_range(hamon::declval<Range const&>())), "");
		static_assert(!noexcept(hamon::declval<Queue&>().push_range(hamon::declval<Range&&>())), "");

		Queue q;
		VERIFY(q.empty());

		{
			T v[] = { T{1}, T{2}, T{3}, };
			Range const r(v);
			q.push_range(r);
		}
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{1});

		{
			T v[] = { T{0}, T{4}, };
			Range const r(v);
			q.push_range(r);
		}
		VERIFY(q.size() == 5);
		VERIFY(q.top() == T{0});
	}

	return true;
}

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, Container, test_input_range>()));
	VERIFY((test_impl<T, Container, test_forward_range>()));
	VERIFY((test_impl<T, Container, test_bidirectional_range>()));
	VERIFY((test_impl<T, Container, test_random_access_range>()));
	VERIFY((test_impl<T, Container, test_contiguous_range>()));
	VERIFY((test_impl<T, Container, test_input_sized_range>()));
	VERIFY((test_impl<T, Container, test_forward_sized_range>()));
	VERIFY((test_impl<T, Container, test_bidirectional_sized_range>()));
	VERIFY((test_impl<T, Container, test_random_access_sized_range>()));
	VERIFY((test_impl<T, Container, test_contiguous_sized_range>()));
	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, PushRangeTest)
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

}	// namespace push_range_test

}	// namespace hamon_priority_queue_test
