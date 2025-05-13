/**
 *	@file	unit_test_priority_queue_ctor_iterator_container_copy.cpp
 *
 *	@brief	イテレータ と Container const& を引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	constexpr priority_queue(InputIterator first, InputIterator last, const Compare& x, const Container&);
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
#include "iterator_test.hpp"

namespace hamon_priority_queue_test
{

namespace ctor_iterator_container_copy_test
{

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)
#define PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define PRIORITY_QUEUE_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define PRIORITY_QUEUE_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, template <typename> class IteratorWrapper>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test_impl()
{
	using Iterator = IteratorWrapper<T>;

	Container const c{T{3}, T{1}, T{4},};
	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, Iterator, Iterator, Compare const&, Container const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, Iterator, Iterator, Compare const&, Container const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, Iterator, Iterator, Compare const&, Container const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, Iterator, Iterator, Compare const&, Container const&>::value, "");

		Queue const q(Iterator{v}, Iterator{v+4}, Compare{}, c);
		VERIFY(q.size() == 7);
		VERIFY(q.top() == T{4});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, Iterator, Iterator, Compare const&, Container const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, Iterator, Iterator, Compare const&, Container const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, Iterator, Iterator, Compare const&, Container const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, Iterator, Iterator, Compare const&, Container const&>::value, "");

		Queue const q(Iterator{v}, Iterator{v+4}, Compare{}, c);
		VERIFY(q.size() == 7);
		VERIFY(q.top() == T{0});
	}

	return true;
}

template <typename T, typename Container>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, Container, cpp17_input_iterator_wrapper>()));
//	VERIFY((test_impl<T, Container, input_iterator_wrapper>()));
	VERIFY((test_impl<T, Container, forward_iterator_wrapper>()));
	VERIFY((test_impl<T, Container, bidirectional_iterator_wrapper>()));
	VERIFY((test_impl<T, Container, random_access_iterator_wrapper>()));
	VERIFY((test_impl<T, Container, contiguous_iterator_wrapper>()));
	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, CtorIteratorContainerCopyTest)
{
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int>>()));
	EXPECT_TRUE((test<float, std::deque<float>>()));

	EXPECT_TRUE((test<int,   std::vector<int>>()));
	EXPECT_TRUE((test<float, std::vector<float>>()));
}

#undef RIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef RIORITY_QUEUE_TEST_CONSTEXPR

}	// namespace ctor_iterator_container_copy_test

}	// namespace hamon_priority_queue_test
