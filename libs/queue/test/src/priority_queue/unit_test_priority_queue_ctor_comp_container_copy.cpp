/**
 *	@file	unit_test_priority_queue_ctor_comp_container_copy.cpp
 *
 *	@brief	Compare と Container const& を引数に取るコンストラクタのテスト
 *
 *	constexpr priority_queue(const Compare& x, const Container&);
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_priority_queue_test
{

namespace ctor_comp_container_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
{
	Container const c{T{3}, T{1}, T{4},};

	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, Compare const&, Container const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, Compare const&, Container const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, Compare const&, Container const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, Compare const&, Container const&>::value, "");

		Queue const q(Compare{}, c);
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{4});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, Compare const&, Container const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, Compare const&, Container const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, Compare const&, Container const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, Compare const&, Container const&>::value, "");

		Queue const q(Compare{}, c);
		VERIFY(q.size() == 3);
		VERIFY(q.top() == T{1});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, CtorCompContainerCopyTest)
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

}	// namespace ctor_comp_container_copy_test

}	// namespace hamon_priority_queue_test
