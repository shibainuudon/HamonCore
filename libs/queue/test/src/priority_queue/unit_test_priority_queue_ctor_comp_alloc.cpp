﻿/**
 *	@file	unit_test_priority_queue_ctor_comp_alloc.cpp
 *
 *	@brief	Compare と Alloc を引数に取るコンストラクタのテスト
 *
 *	template<class Alloc> constexpr priority_queue(const Compare&, const Alloc&);
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "priority_queue_test_helper.hpp"

namespace hamon_priority_queue_test
{

namespace ctor_comp_alloc_test
{

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)
#define PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define PRIORITY_QUEUE_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define PRIORITY_QUEUE_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, typename Compare>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test_impl()
{
	using Queue = hamon::priority_queue<T, Container, Compare>;
	using Alloc = TestAllocator<T>;

	static_assert( hamon::is_constructible<Queue, Compare const&, Alloc const&>::value, "");
#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)
	static_assert(
		hamon::is_nothrow_constructible<Queue, Compare const&, Alloc const&>::value ==
		hamon::is_nothrow_constructible<Container, Alloc const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Queue, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Queue, Compare const&, Alloc const&>::value, "");

	Compare const comp{};
	Alloc const a{};
	Queue q(comp, a);
	VERIFY(q.empty());
	VERIFY(q.size() == 0);

	return true;
}

template <typename T, typename Container>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, Container, hamon::less<T>>()));
	VERIFY((test_impl<T, Container, hamon::greater<T>>()));
	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, CtorCompAllocTest)
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

}	// namespace ctor_comp_alloc_test

}	// namespace hamon_priority_queue_test
