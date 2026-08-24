/**
 *	@file	unit_test_priority_queue_ctor_iterator_container_copy_alloc.cpp
 *
 *	@brief	イテレータ と Container const& と Alloc を引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr priority_queue(InputIterator, InputIterator, const Compare&, const Container&, const Alloc&);
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
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "priority_queue_test_helper.hpp"

namespace hamon_priority_queue_test
{

namespace ctor_iterator_container_copy_alloc_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Container, template <typename> class IteratorWrapper>
HAMON_CXX20_CONSTEXPR bool test_impl()
{
	using Iterator = IteratorWrapper<T>;
	using Alloc = TestAllocator<T>;

	Container const c{T{3}, T{1}, T{4},};
	T v[] = { T{0}, T{1}, T{2}, T{3}, };
	Alloc const a{};

	{
		using Compare = hamon::less<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, Iterator, Iterator, Compare const&, Container const&, Alloc const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, Iterator, Iterator, Compare const&, Container const&, Alloc const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, Iterator, Iterator, Compare const&, Container const&, Alloc const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, Iterator, Iterator, Compare const&, Container const&, Alloc const&>::value, "");

		Queue const q(Iterator{v}, Iterator{v+4}, Compare{}, c, a);
		VERIFY(q.size() == 7);
		VERIFY(q.top() == T{4});
	}
	{
		using Compare = hamon::greater<T>;
		using Queue = hamon::priority_queue<T, Container, Compare>;

		static_assert( hamon::is_constructible<Queue, Iterator, Iterator, Compare const&, Container const&, Alloc const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Queue, Iterator, Iterator, Compare const&, Container const&, Alloc const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Queue, Iterator, Iterator, Compare const&, Container const&, Alloc const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Queue, Iterator, Iterator, Compare const&, Container const&, Alloc const&>::value, "");

		Queue const q(Iterator{v}, Iterator{v+4}, Compare{}, c, a);
		VERIFY(q.size() == 7);
		VERIFY(q.top() == T{0});
	}

	return true;
}

template <typename T, typename Container>
HAMON_CXX20_CONSTEXPR bool test()
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

GTEST_TEST(PriorityQueueTest, CtorIteratorContainerCopyAllocTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::deque<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::deque<float>>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int,   hamon::vector<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::vector<float>>()));

	EXPECT_TRUE((test<int,   std::deque<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::deque<float, hamon::allocator<float>>>()));

	EXPECT_TRUE((test<int,   std::vector<int,   hamon::allocator<int>>>()));
	EXPECT_TRUE((test<float, std::vector<float, hamon::allocator<float>>>()));
}

}	// namespace ctor_iterator_container_copy_alloc_test

}	// namespace hamon_priority_queue_test
