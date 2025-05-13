/**
 *	@file	unit_test_queue_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args>
 *	constexpr decltype(auto) emplace(Args&&... args);
 */

#include <hamon/queue/queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/list.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_queue_test
{

namespace emplace_test
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

#if defined(HAMON_USE_STD_QUEUE) && (HAMON_CXX_STANDARD < 17)
	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().emplace()), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().emplace(hamon::declval<T>())), void>::value, "");
#else
	using Reference = typename Queue::reference;
	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().emplace()), Reference>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Queue&>().emplace(hamon::declval<T>())), Reference>::value, "");
#endif

	static_assert(!noexcept(hamon::declval<Queue&>().emplace()), "");
	static_assert(!noexcept(hamon::declval<Queue&>().emplace(hamon::declval<T>())), "");

	Queue q;

#if defined(HAMON_USE_STD_QUEUE) && (HAMON_CXX_STANDARD < 17)
	q.emplace(T{1});
#else
	{
		auto& r = q.emplace(T{1});
		VERIFY(r == T{1});
	}
#endif

	VERIFY(q.size() == 1);
	VERIFY(q.front() == T{1});
	VERIFY(q.back() == T{1});

#if defined(HAMON_USE_STD_QUEUE) && (HAMON_CXX_STANDARD < 17)
	q.emplace(T{2});
#else
	{
		auto& r = q.emplace(T{2});
		VERIFY(r == T{2});
	}
#endif

	VERIFY(q.size() == 2);
	VERIFY(q.front() == T{1});
	VERIFY(q.back() == T{2});

	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, EmplaceTest)
{
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::list<int>>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::list<float>>()));

	//EXPECT_TRUE((test<int,   std::deque<int>>()));
	//EXPECT_TRUE((test<float, std::deque<float>>()));

	//EXPECT_TRUE((test<int,   std::list<int>>()));
	//EXPECT_TRUE((test<float, std::list<float>>()));

	{
		hamon::queue<hamon::pair<int, hamon::string>> q;

#if defined(HAMON_USE_STD_QUEUE) && (HAMON_CXX_STANDARD < 17)
		q.emplace(3, "aaa");
#else
		{
			auto& r = q.emplace(3, "aaa");
			EXPECT_TRUE(r.first == 3);
			EXPECT_TRUE(r.second == "aaa");
		}
#endif

		EXPECT_TRUE(q.size() == 1);
		EXPECT_TRUE(q.front().first == 3);
		EXPECT_TRUE(q.front().second == "aaa");
		EXPECT_TRUE(q.back().first == 3);
		EXPECT_TRUE(q.back().second == "aaa");

#if defined(HAMON_USE_STD_QUEUE) && (HAMON_CXX_STANDARD < 17)
		q.emplace(1, "bbb");
#else
		{
			auto& r = q.emplace(1, "bbb");
			EXPECT_TRUE(r.first == 1);
			EXPECT_TRUE(r.second == "bbb");
		}
#endif

		EXPECT_TRUE(q.size() == 2);
		EXPECT_TRUE(q.front().first == 3);
		EXPECT_TRUE(q.front().second == "aaa");
		EXPECT_TRUE(q.back().first == 1);
		EXPECT_TRUE(q.back().second == "bbb");

#if defined(HAMON_USE_STD_QUEUE) && (HAMON_CXX_STANDARD < 17)
		q.emplace(4, "ccc");
#else
		{
			auto& r = q.emplace(4, "ccc");
			EXPECT_TRUE(r.first == 4);
			EXPECT_TRUE(r.second == "ccc");
		}
#endif

		EXPECT_TRUE(q.size() == 3);
		EXPECT_TRUE(q.front().first == 3);
		EXPECT_TRUE(q.front().second == "aaa");
		EXPECT_TRUE(q.back().first == 4);
		EXPECT_TRUE(q.back().second == "ccc");
	}
}

#undef QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef QUEUE_TEST_CONSTEXPR

}	// namespace emplace_test

}	// namespace hamon_queue_test
