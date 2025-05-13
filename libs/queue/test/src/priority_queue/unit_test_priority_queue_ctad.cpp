/**
 *	@file	unit_test_priority_queue_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class Compare, class Container>
 *	priority_queue(Compare, Container)
 *		-> priority_queue<typename Container::value_type, Container, Compare>;
 *
 *	template<class InputIterator,
 *		class Compare = less<iter-value-type<InputIterator>>,
 *		class Container = vector<iter-value-type<InputIterator>>>
 *	priority_queue(InputIterator, InputIterator, Compare = Compare(), Container = Container())
 *		-> priority_queue<iter-value-type<InputIterator>, Container, Compare>;
 *
 *	template<ranges::input_range R, class Compare = less<ranges::range_value_t<R>>>
 *	priority_queue(from_range_t, R&&, Compare = Compare())
 *		-> priority_queue<ranges::range_value_t<R>, vector<ranges::range_value_t<R>>, Compare>;
 *
 *	template<class Compare, class Container, class Allocator>
 *	priority_queue(Compare, Container, Allocator)
 *		-> priority_queue<typename Container::value_type, Container, Compare>;
 *
 *	template<class InputIterator, class Allocator>
 *	priority_queue(InputIterator, InputIterator, Allocator)
 *		-> priority_queue<iter-value-type<InputIterator>,
 *			vector<iter-value-type<InputIterator>, Allocator>,
 *			less<iter-value-type<InputIterator>>>;
 *
 *	template<class InputIterator, class Compare, class Allocator>
 *	priority_queue(InputIterator, InputIterator, Compare, Allocator)
 *		-> priority_queue<iter-value-type<InputIterator>,
 *			vector<iter-value-type<InputIterator>, Allocator>, Compare>;
 *
 *	template<class InputIterator, class Compare, class Container, class Allocator>
 *	priority_queue(InputIterator, InputIterator, Compare, Container, Allocator)
 *		-> priority_queue<typename Container::value_type, Container, Compare>;
 *
 *	template<ranges::input_range R, class Compare, class Allocator>
 *	priority_queue(from_range_t, R&&, Compare, Allocator)
 *		-> priority_queue<ranges::range_value_t<R>, vector<ranges::range_value_t<R>, Allocator>, Compare>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	priority_queue(from_range_t, R&&, Allocator)
 *		-> priority_queue<ranges::range_value_t<R>, vector<ranges::range_value_t<R>, Allocator>>;
 */

#include <hamon/queue/priority_queue.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "priority_queue_test_helper.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_priority_queue_test
{

namespace ctad_test
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
PRIORITY_QUEUE_TEST_CONSTEXPR bool test1_impl_2()
{
	{
		Container const c{T{1}, T{2}, T{3}};
		hamon::priority_queue q(Compare{}, c);
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, Container, Compare>>::value, "");
	}
	{
		using Alloc = TestAllocator<T>;
		Container const c{T{1}, T{2}, T{3}};
		hamon::priority_queue q(Compare{}, c, Alloc{});
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, Container, Compare>>::value, "");
	}

	return true;
}

template <typename T, typename Container>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test1_impl_1()
{
	VERIFY((test1_impl_2<T, Container, hamon::less<T>>()));
	VERIFY((test1_impl_2<T, Container, hamon::greater<T>>()));
	return true;
}

template <typename T>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test1()
{
	VERIFY((test1_impl_1<T, hamon::deque<T>>()));
	VERIFY((test1_impl_1<T, hamon::vector<T>>()));
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

template <typename T, typename Container, typename Compare, template <typename> class IteratorWrapper>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test2_impl_3()
{
	using Iterator = IteratorWrapper<T>;
	using DefaultCompare = typename hamon::priority_queue<T>::value_compare;
	using DefaultContainer = typename hamon::priority_queue<T>::container_type;

	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	{
		hamon::priority_queue q(Iterator{v}, Iterator{v + 4});
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, DefaultContainer, DefaultCompare>>::value, "");
	}
	{
		hamon::priority_queue q(Iterator{v}, Iterator{v + 4}, Compare{});
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, DefaultContainer, Compare>>::value, "");
	}
	{
		hamon::priority_queue q(Iterator{v}, Iterator{v + 4}, Compare{}, Container{});
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, Container, Compare>>::value, "");
	}

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE)	// LWG 3506
	using Alloc = TestAllocator<T>;
	{
		hamon::priority_queue q(Iterator{v}, Iterator{v + 4}, Alloc{});
		using Container2 = container_rebind_allocator_t<DefaultContainer, Alloc>;
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, Container2, DefaultCompare>>::value, "");
	}
	{
		hamon::priority_queue q(Iterator{v}, Iterator{v + 4}, Compare{}, Alloc{});
		using Container2 = container_rebind_allocator_t<DefaultContainer, Alloc>;
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, Container2, Compare>>::value, "");
	}
	{
		hamon::priority_queue q(Iterator{v}, Iterator{v + 4}, Compare{}, Container{}, Alloc{});
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, Container, Compare>>::value, "");
	}
#endif

	return true;
}

template <typename T, typename Container, typename Compare>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test2_impl_2()
{
	VERIFY((test2_impl_3<T, Container, Compare, cpp17_input_iterator_wrapper>()));
//	VERIFY((test2_impl_3<T, Container, Compare, input_iterator_wrapper>()));
	VERIFY((test2_impl_3<T, Container, Compare, forward_iterator_wrapper>()));
	VERIFY((test2_impl_3<T, Container, Compare, bidirectional_iterator_wrapper>()));
	VERIFY((test2_impl_3<T, Container, Compare, random_access_iterator_wrapper>()));
	VERIFY((test2_impl_3<T, Container, Compare, contiguous_iterator_wrapper>()));
	return true;
}

template <typename T, typename Container>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test2_impl_1()
{
	VERIFY((test2_impl_2<T, Container, hamon::less<T>>()));
	VERIFY((test2_impl_2<T, Container, hamon::greater<T>>()));
	return true;
}

template <typename T>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test2()
{
	VERIFY((test2_impl_1<T, hamon::deque<T>>()));
	VERIFY((test2_impl_1<T, hamon::vector<T>>()));
	return true;
}

template <typename T, typename Container, typename Compare, template <typename> class RangeWrapper>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test3_impl_3()
{
	using Range = RangeWrapper<T>;
	using DefaultCompare = typename hamon::priority_queue<T>::value_compare;
	using DefaultContainer = typename hamon::priority_queue<T>::container_type;
	using Alloc = TestAllocator<T>;

	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	{
		hamon::priority_queue q(hamon::from_range, Range{v});
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, DefaultContainer, DefaultCompare>>::value, "");
	}
	{
		hamon::priority_queue q(hamon::from_range, Range{v}, Compare{});
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, DefaultContainer, Compare>>::value, "");
	}
	{
		hamon::priority_queue q(hamon::from_range, Range{v}, Compare{}, Alloc{});
		using Container2 = container_rebind_allocator_t<DefaultContainer, Alloc>;
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, Container2, Compare>>::value, "");
	}
	{
		hamon::priority_queue q(hamon::from_range, Range{v}, Alloc{});
		using Container2 = container_rebind_allocator_t<DefaultContainer, Alloc>;
		static_assert(hamon::is_same<decltype(q), hamon::priority_queue<T, Container2, DefaultCompare>>::value, "");
	}

	return true;
}

template <typename T, typename Container, typename Compare>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test3_impl_2()
{
	VERIFY((test3_impl_3<T, Container, Compare, test_input_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_forward_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_bidirectional_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_random_access_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_contiguous_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_input_sized_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_forward_sized_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_bidirectional_sized_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_random_access_sized_range>()));
	VERIFY((test3_impl_3<T, Container, Compare, test_contiguous_sized_range>()));
	return true;
}

template <typename T, typename Container>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test3_impl_1()
{
	VERIFY((test3_impl_2<T, Container, hamon::less<T>>()));
	VERIFY((test3_impl_2<T, Container, hamon::greater<T>>()));
	return true;
}

template <typename T>
PRIORITY_QUEUE_TEST_CONSTEXPR bool test3()
{
	VERIFY((test3_impl_1<T, hamon::deque<T>>()));
	VERIFY((test3_impl_1<T, hamon::vector<T>>()));
	return true;
}

#undef VERIFY

GTEST_TEST(PriorityQueueTest, CtadTest)
{
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

#if !defined(HAMON_USE_STD_PRIORITY_QUEUE) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	PRIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE((test3<float>()));
#endif
}

#undef RIORITY_QUEUE_TEST_CONSTEXPR_EXPECT_TRUE
#undef RIORITY_QUEUE_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_priority_queue_test

#endif
