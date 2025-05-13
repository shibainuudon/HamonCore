/**
 *	@file	unit_test_priority_queue_ctor_range_comp_alloc.cpp
 *
 *	@brief	range と Compare と Alloc を引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<T> R, class Alloc>
 *	constexpr priority_queue(from_range_t, R&& rg, const Compare&, const Alloc&);
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "priority_queue_test_helper.hpp"

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))

namespace hamon_priority_queue_test
{

namespace ctor_range_comp_alloc_test
{

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)
#define PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define PRIORITY_QUEUE_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define PRIORITY_QUEUE_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, template <typename> class RangeWrapper>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test_impl()
{
	using Range = RangeWrapper<T>;
	using Alloc = TestAllocator<T>;

	T v[] = { T{5}, T{4}, T{3}, };

	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, hamon::from_range_t, Range, Compare const&, Alloc const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, hamon::from_range_t, Range, Compare const&, Alloc const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, hamon::from_range_t, Range, Compare const&, Alloc const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, hamon::from_range_t, Range, Compare const&, Alloc const&>::value, "");

		Range const r(v);
		Queue const q(hamon::from_range, r, Compare{}, Alloc{});
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{5});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, hamon::from_range_t, Range, Compare const&, Alloc const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, hamon::from_range_t, Range, Compare const&, Alloc const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, hamon::from_range_t, Range, Compare const&, Alloc const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, hamon::from_range_t, Range, Compare const&, Alloc const&>::value, "");

		Range const r(v);
		Queue const q(hamon::from_range, r, Compare{}, Alloc{});
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{3});
	}

	return true;
}

template <typename T, typename Container>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test()
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

GTEST_TEST(PriorityQueueTest, CtorRangeCompAllocTest)
{
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::deque<float, hamon::allocator<float>>>()));

	EXPECT_TRUE((test<int,   std::vector<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::vector<float, hamon::allocator<float>>>()));
}

#undef RIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef RIORITY_QUEUE_TEST_CONSTEXPR

}	// namespace ctor_range_comp_alloc_test

}	// namespace hamon_priority_queue_test

#endif
