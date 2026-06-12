/**
 *	@file	unit_test_stack_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class Container>
 *	stack(Container) -> stack<typename Container::value_type, Container>;
 *
 *	template<class InputIterator>
 *	stack(InputIterator, InputIterator) -> stack<iter-value-type<InputIterator>>;
 *
 *	template<ranges::input_range R>
 *	stack(from_range_t, R&&) -> stack<ranges::range_value_t<R>>;
 *
 *	template<class Container, class Allocator>
 *	stack(Container, Allocator) -> stack<typename Container::value_type, Container>;
 *
 *	template<class InputIterator, class Allocator>
 *	stack(InputIterator, InputIterator, Allocator)
 *	-> stack<iter-value-type<InputIterator>, deque<iter-value-type<InputIterator>, Allocator>>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	stack(from_range_t, R&&, Allocator)
 *	-> stack<ranges::range_value_t<R>, deque<ranges::range_value_t<R>, Allocator>>;
 */

#include <hamon/stack/stack.hpp>
#include <hamon/deque.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"
#include "stack_test_helper.hpp"

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

namespace hamon_stack_test
{

namespace ctad_test
{

template <typename T, typename Container>
void test1_impl()
{
	{
		Container const c{T{10}, T{20}, T{30}};
		hamon::stack s(c);
		static_assert(hamon::is_same<decltype(s), hamon::stack<T, Container>>::value, "");
	}
	{
		Container c{T{10}, T{20}, T{30}};
		hamon::stack s(hamon::move(c));
		static_assert(hamon::is_same<decltype(s), hamon::stack<T, Container>>::value, "");
	}
	{
		Container const c{T{10}, T{20}, T{30}};
		TestAllocator<T> a{};
		hamon::stack s(c, a);
		static_assert(hamon::is_same<decltype(s), hamon::stack<T, Container>>::value, "");
	}
	{
		Container c{T{10}, T{20}, T{30}};
		TestAllocator<T> a{};
		hamon::stack s(hamon::move(c), a);
		static_assert(hamon::is_same<decltype(s), hamon::stack<T, Container>>::value, "");
	}
}

template <typename T>
void test1()
{
	test1_impl<T, hamon::deque<T>>();
	test1_impl<T, hamon::vector<T>>();
	test1_impl<T, hamon::list<T>>();
	test1_impl<T, std::deque<T, hamon::allocator<T>>>();
	test1_impl<T, std::vector<T, hamon::allocator<T>>>();
	test1_impl<T, std::list<T, hamon::allocator<T>>>();
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
void test2_impl()
{
	using Iterator = IteratorWrapper<T>;
	using DefaultContainer = typename hamon::stack<T>::container_type;
	using Allocator = TestAllocator<T>;

	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	{
		hamon::stack s(Iterator{v}, Iterator{v + 4});
		static_assert(hamon::is_same<decltype(s), hamon::stack<T, DefaultContainer>>::value, "");
	}
	{
		Allocator a{};
		hamon::stack s(Iterator{v}, Iterator{v + 4}, a);
		using Container2 = container_rebind_allocator_t<DefaultContainer, Allocator>;
		static_assert(hamon::is_same<decltype(s), hamon::stack<T, Container2>>::value, "");
	}
}

template <typename T>
void test2()
{
	test2_impl<T, cpp17_input_iterator_wrapper>();
//	test2_impl<T, input_iterator_wrapper>();
	test2_impl<T, forward_iterator_wrapper>();
	test2_impl<T, bidirectional_iterator_wrapper>();
	test2_impl<T, random_access_iterator_wrapper>();
	test2_impl<T, contiguous_iterator_wrapper>();
}

template <typename T, template <typename> class RangeWrapper>
void test3_impl()
{
	using Range = RangeWrapper<T>;
	using DefaultContainer = typename hamon::stack<T>::container_type;
	using Allocator = TestAllocator<T>;

	T v[] = { T{0}, T{1}, T{2}, T{3}, };

	{
		hamon::stack s(hamon::from_range, Range{v});
		static_assert(hamon::is_same<decltype(s), hamon::stack<T, DefaultContainer>>::value, "");
	}
	{
		hamon::stack s(hamon::from_range, Range{v}, Allocator{});
		using Container2 = container_rebind_allocator_t<DefaultContainer, Allocator>;
		static_assert(hamon::is_same<decltype(s), hamon::stack<T, Container2>>::value, "");
	}
}

template <typename T>
void test3()
{
	test3_impl<T, test_input_range>();
	test3_impl<T, test_forward_range>();
	test3_impl<T, test_bidirectional_range>();
	test3_impl<T, test_random_access_range>();
	test3_impl<T, test_contiguous_range>();
	test3_impl<T, test_input_sized_range>();
	test3_impl<T, test_forward_sized_range>();
	test3_impl<T, test_bidirectional_sized_range>();
	test3_impl<T, test_random_access_sized_range>();
	test3_impl<T, test_contiguous_sized_range>();
}

GTEST_TEST(StackTest, CtadTest)
{
	test1<int>();
	test1<float>();

#if !defined(HAMON_USE_STD_STACK) || \
	(defined(__cpp_lib_adaptor_iterator_pair_constructor) && (__cpp_lib_adaptor_iterator_pair_constructor >= 202106L))
	test2<int>();
	test2<float>();
#endif

#if !defined(HAMON_USE_STD_STACK) || \
	(defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L))
	test3<int>();
	test3<float>();
#endif
}

}	// namespace ctad_test

}	// namespace hamon_stack_test

#endif
