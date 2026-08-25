/**
 *	@file	unit_test_priority_queue_ctor_range.cpp
 *
 *	@brief	range を引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr priority_queue(from_range_t, R&& rg, const Compare& x = Compare());
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include <deque>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_priority_queue_test
{

namespace ctor_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Range = RangeWrapper<T>;

	T v[] = { T{5}, T{4}, T{3}, };

	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, hamon::from_range_t, Range>::value, "");
		static_assert( hamon::is_constructible<Queue, hamon::from_range_t, Range, Compare const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, hamon::from_range_t, Range>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, hamon::from_range_t, Range, Compare const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, hamon::from_range_t, Range>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, hamon::from_range_t, Range, Compare const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, hamon::from_range_t, Range>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, hamon::from_range_t, Range, Compare const&>::value, "");

		{
			Range const r(v);
			Queue const q(hamon::from_range, r);
			VERIFY(q.size() == 3);
			VERIFY(q.top() == T{5});
		}
		{
			Queue const q(hamon::from_range, Range{v}, Compare{});
			VERIFY(q.size() == 3);
			VERIFY(q.top() == T{5});
		}
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, hamon::from_range_t, Range>::value, "");
		static_assert( hamon::is_constructible<Queue, hamon::from_range_t, Range, Compare const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, hamon::from_range_t, Range>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, hamon::from_range_t, Range, Compare const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, hamon::from_range_t, Range>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, hamon::from_range_t, Range, Compare const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, hamon::from_range_t, Range>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, hamon::from_range_t, Range, Compare const&>::value, "");

		{
			Queue const q(hamon::from_range, Range{v});
			VERIFY(q.size() == 3);
			VERIFY(q.top() == T{3});
		}
		{
			Range const r(v);
			Queue const q(hamon::from_range, r, Compare{});
			VERIFY(q.size() == 3);
			VERIFY(q.top() == T{3});
		}
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

GTEST_TEST(PriorityQueueTest, CtorRangeTest)
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

}	// namespace ctor_range_test

}	// namespace hamon_priority_queue_test
