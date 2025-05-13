/**
 *	@file	unit_test_queue_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class Container>
 *	queue(Container) -> queue<typename Container::value_type, Container>;
 *
 *	template<class InputIterator>
 *	queue(InputIterator, InputIterator) -> queue<iter-value-type<InputIterator>>;
 *
 *	template<ranges::input_range R>
 *	queue(from_range_t, R&&) -> queue<ranges::range_value_t<R>>;
 *
 *	template<class Container, class Allocator>
 *	queue(Container, Allocator) -> queue<typename Container::value_type, Container>;
 *
 *	template<class InputIterator, class Allocator>
 *	queue(InputIterator, InputIterator, Allocator)
 *		-> queue<iter-value-type<InputIterator>, deque<iter-value-type<InputIterator>, Allocator>>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	queue(from_range_t, R&&, Allocator)
 *		-> queue<ranges::range_value_t<R>, deque<ranges::range_value_t<R>, Allocator>>;
 */

#include <hamon/queue/queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "queue_test_helper.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_queue_test
{

namespace ctad_test
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
QUEUE_TEST_CONSTEXPR bool test1_impl()
{
	{
		Container const c{T{10}, T{20}, T{30}};
		hamon::queue q(c);
		static_assert(hamon::is_same<decltype(q), hamon::queue<T, Container>>::value, "");
	}
	{
		Container c{T{10}, T{20}, T{30}};
		hamon::queue q(hamon::move(c));
		static_assert(hamon::is_same<decltype(q), hamon::queue<T, Container>>::value, "");
	}
	{
		Container const c{T{10}, T{20}, T{30}};
		hamon::allocator<T> a{};
		hamon::queue q(c, a);
		static_assert(hamon::is_same<decltype(q), hamon::queue<T, Container>>::value, "");
	}
	{
		Container c{T{10}, T{20}, T{30}};
		hamon::allocator<T> a{};
		hamon::queue q(hamon::move(c), a);
		static_assert(hamon::is_same<decltype(q), hamon::queue<T, Container>>::value, "");
	}

	return true;
}

template <typename T>
QUEUE_TEST_CONSTEXPR bool test1()
{
	VERIFY((test1_impl<T, hamon::deque<T>>()));
	VERIFY((test1_impl<T, hamon::list<T>>()));
	return true;
}

template <typename Container, typename Allocator>
struct container_rebind_allocator;

template <typename T, typename A, template <typename, typename> class Container, typename Allocator>
struct container_rebind_allocator<Container<T, A>, Allocator>
{
	using type = Container<T, Allocator>;
};

template <typename Container, typename Allocator>
using container_rebind_allocator_t = typename container_rebind_allocator<Container, Allocator>::type;

template <typename T, template <typename> class IteratorWrapper>
QUEUE_TEST_CONSTEXPR bool test2_impl()
{
	using Iterator = IteratorWrapper<T>;
	using DefaultContainer = typename hamon::queue<T>::container_type;
	using Allocator = TestAllocator<T>;

	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	{
		hamon::queue q(Iterator{v}, Iterator{v + 4});
		static_assert(hamon::is_same<decltype(q), hamon::queue<T, DefaultContainer>>::value, "");
	}
	{
		hamon::queue q(Iterator{v}, Iterator{v + 4}, Allocator{});
		using Container2 = container_rebind_allocator_t<DefaultContainer, Allocator>;
		static_assert(hamon::is_same<decltype(q), hamon::queue<T, Container2>>::value, "");
	}

	return true;
}

template <typename T>
QUEUE_TEST_CONSTEXPR bool test2()
{
	VERIFY((test2_impl<T, cpp17_input_iterator_wrapper>()));
//	VERIFY((test2_impl<T, input_iterator_wrapper>()));
	VERIFY((test2_impl<T, forward_iterator_wrapper>()));
	VERIFY((test2_impl<T, bidirectional_iterator_wrapper>()));
	VERIFY((test2_impl<T, random_access_iterator_wrapper>()));
	VERIFY((test2_impl<T, contiguous_iterator_wrapper>()));
	return true;
}

template <typename T, template <typename> class RangeWrapper>
QUEUE_TEST_CONSTEXPR bool test3_impl()
{
	using Range = RangeWrapper<T>;
	using DefaultContainer = typename hamon::queue<T>::container_type;
	using Allocator = TestAllocator<T>;

	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	{
		hamon::queue q(hamon::from_range, Range{v});
		static_assert(hamon::is_same<decltype(q), hamon::queue<T, DefaultContainer>>::value, "");
	}
	{
		hamon::queue q(hamon::from_range, Range{v}, Allocator{});
		using Container2 = container_rebind_allocator_t<DefaultContainer, Allocator>;
		static_assert(hamon::is_same<decltype(q), hamon::queue<T, Container2>>::value, "");
	}

	return true;
}

template <typename T>
QUEUE_TEST_CONSTEXPR bool test3()
{
	VERIFY((test3_impl<T, test_input_range>()));
	VERIFY((test3_impl<T, test_forward_range>()));
	VERIFY((test3_impl<T, test_bidirectional_range>()));
	VERIFY((test3_impl<T, test_random_access_range>()));
	VERIFY((test3_impl<T, test_contiguous_range>()));
	VERIFY((test3_impl<T, test_input_sized_range>()));
	VERIFY((test3_impl<T, test_forward_sized_range>()));
	VERIFY((test3_impl<T, test_bidirectional_sized_range>()));
	VERIFY((test3_impl<T, test_random_access_sized_range>()));
	VERIFY((test3_impl<T, test_contiguous_sized_range>()));
	return true;
}

#undef VERIFY

GTEST_TEST(QueueTest, CtadTest)
{
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

#if !defined(HAMON_USE_STD_QUEUE) || \
	(defined(__cpp_lib_adaptor_iterator_pair_constructor) && (__cpp_lib_adaptor_iterator_pair_constructor >= 202106L))
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));
#endif

#if !defined(HAMON_USE_STD_QUEUE) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test3<float>()));
#endif
}

#undef QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef QUEUE_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_queue_test

#endif
