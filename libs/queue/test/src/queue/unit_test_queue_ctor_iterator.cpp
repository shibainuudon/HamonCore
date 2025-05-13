/**
 *	@file	unit_test_queue_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator> constexpr queue(InputIterator first, InputIterator last);
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
#include "iterator_test.hpp"

#if !defined(HAMON_USE_STD_QUEUE) || \
	(defined(__cpp_lib_adaptor_iterator_pair_constructor) && (__cpp_lib_adaptor_iterator_pair_constructor >= 202106L))

namespace hamon_queue_test
{

namespace ctor_iterator_test
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

template <typename T, typename Container, template <typename> class IteratorWrapper>
QUEUE_TEST_CONSTEXPR bool test_impl()
{
	using Queue = hamon::queue<T, Container>;
	using Iterator = IteratorWrapper<T>;

	static_assert( hamon::is_constructible<Queue, Iterator, Iterator>::value, "");
#if !defined(HAMON_USE_STD_QUEUE)
	static_assert(
		hamon::is_nothrow_constructible<Queue,     Iterator, Iterator>::value ==
		hamon::is_nothrow_constructible<Container, Iterator, Iterator>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Queue, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<Queue, Iterator, Iterator>::value, "");

	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	Queue const q(Iterator{v}, Iterator{v+4});
	VERIFY(!q.empty());
	VERIFY(q.size()  == 4);
	VERIFY(q.front() == T{0});
	VERIFY(q.back()  == T{3});

	return true;
}

template <typename T, typename Container>
QUEUE_TEST_CONSTEXPR bool test()
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

GTEST_TEST(QueueTest, CtorIteratorTest)
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

}	// namespace ctor_iterator_test

}	// namespace hamon_queue_test

#endif
