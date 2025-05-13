/**
 *	@file	unit_test_priority_queue_ctor_comp_container_move_alloc.cpp
 *
 *	@brief	Compare と Container&& と Alloc を引数に取るコンストラクタのテスト
 *
 *	template<class Alloc> constexpr priority_queue(const Compare&, Container&&, const Alloc&);
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "priority_queue_test_helper.hpp"

namespace hamon_priority_queue_test
{

namespace ctor_comp_container_move_alloc_test
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
	using Alloc = TestAllocator<T>;

	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, Compare const&, Container&&, Alloc const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, Compare const&, Container&&, Alloc const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, Compare const&, Container&&, Alloc const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, Compare const&, Container&&, Alloc const&>::value, "");

		Container c{T{3}, T{1}, T{4},};
		Alloc const a{};
		Queue const q(Compare{}, hamon::move(c), a);
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{4});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, Compare const&, Container&&, Alloc const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, Compare const&, Container&&, Alloc const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, Compare const&, Container&&, Alloc const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, Compare const&, Container&&, Alloc const&>::value, "");

		Container c{T{3}, T{1}, T{4},};
		Alloc const a{};
		Queue const q(Compare{}, hamon::move(c), a);
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{1});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, CtorCompContainerMoveAllocTest)
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

}	// namespace ctor_comp_container_move_alloc_test

}	// namespace hamon_priority_queue_test
