/**
 *	@file	unit_test_queue_ctor_container_copy.cpp
 *
 *	@brief	const Container& を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit queue(const Container&);
 */

#include <hamon/queue/queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_queue_test
{

namespace ctor_container_copy_test
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

	static_assert( hamon::is_constructible<Queue, Container const&>::value, "");
#if !defined(HAMON_USE_STD_QUEUE)
	static_assert(
		hamon::is_nothrow_constructible<Queue,     Container const&>::value ==
		hamon::is_nothrow_constructible<Container, Container const&>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<Queue, Container const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Queue, Container const&>::value, "");

	Container const c{T{10}, T{20}, T{30}};
	Queue const q(c);

	VERIFY(!q.empty());
	VERIFY(q.size()  == 3);
	VERIFY(q.front() == T{10});
	VERIFY(q.back()  == T{30});

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, CtorContainerCopyTest)
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

}	// namespace ctor_container_copy_test

}	// namespace hamon_queue_test
