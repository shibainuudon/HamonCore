/**
 *	@file	unit_test_queue_ctor_alloc.cpp
 *
 *	@brief	Alloc を引数に取るコンストラクタのテスト
 *
 *	template<class Alloc> constexpr explicit queue(const Alloc&);
 */

#include <hamon/queue/queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "queue_test_helper.hpp"

namespace hamon_queue_test
{

namespace ctor_alloc_test
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
	using Alloc = TestAllocator<T>;

	static_assert( hamon::is_constructible<Queue, Alloc const&>::value, "");
#if !defined(HAMON_USE_STD_QUEUE)
	static_assert(
		hamon::is_nothrow_constructible<Queue,     Alloc const&>::value ==
		hamon::is_nothrow_constructible<Container, Alloc const&>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<Queue, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Queue, Alloc const&>::value, "");

	Alloc a{};
	Queue const q(a);

	VERIFY(q.empty());
	VERIFY(q.size() == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, CtorAllocTest)
{
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::deque<float, hamon::allocator<float>>>()));

	EXPECT_TRUE((test<int,   std::list<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::list<float, hamon::allocator<float>>>()));
}

#undef QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef QUEUE_TEST_CONSTEXPR

}	// namespace ctor_alloc_test

}	// namespace hamon_queue_test
