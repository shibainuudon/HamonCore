/**
 *	@file	unit_test_ranges_elements_view_instantiate.cpp
 *
 *	@brief	elements_view のテスト
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace instantiate_test
{

template <typename T, typename ValueType = T, typename Reference = T&>
struct TestIterator
{
	T*	m_ptr;

	using iterator_category = hamon::input_iterator_tag;
	using value_type        = ValueType;
	using difference_type   = hamon::ptrdiff_t;

	TestIterator& operator++();
	void          operator++(int);
	Reference     operator*() const;
	bool operator==(const TestIterator& rhs) const;
	bool operator!=(const TestIterator& rhs) const;
};

struct Movable
{};

static_assert(hamon::move_constructible_t<Movable>::value, "");

struct NotMovable
{
	NotMovable(NotMovable&&) = delete;
};

static_assert(!hamon::move_constructible_t<NotMovable>::value, "");

template <typename T, hamon::size_t N, typename = void>
struct CanInstantiateElementsView
	: hamon::false_type {};

template <typename T, hamon::size_t N>
struct CanInstantiateElementsView<T, N, hamon::void_t<hamon::ranges::elements_view<T, N>>>
	: hamon::true_type {};

static_assert(!CanInstantiateElementsView<test_input_view<int>, 0>::value, "");

static_assert( CanInstantiateElementsView<test_input_view<hamon::tuple<int>>, 0>::value, "");
static_assert(!CanInstantiateElementsView<test_input_view<hamon::tuple<int>>, 1>::value, "");

static_assert( CanInstantiateElementsView<test_input_view<hamon::tuple<int, long>>, 0>::value, "");
static_assert( CanInstantiateElementsView<test_input_view<hamon::tuple<int, long>>, 1>::value, "");
static_assert(!CanInstantiateElementsView<test_input_view<hamon::tuple<int, long>>, 2>::value, "");

static_assert(!CanInstantiateElementsView<test_output_view<hamon::tuple<int, long>>, 0>::value, "");	// requires input_range<V>
static_assert(!CanInstantiateElementsView<test_input_range<hamon::tuple<int, long>>, 0>::value, "");	// requires view<V>

static_assert( CanInstantiateElementsView<test_input_view<hamon::tuple<char, float, double>>, 0>::value, "");
static_assert( CanInstantiateElementsView<test_input_view<hamon::tuple<char, float, double>>, 1>::value, "");
static_assert( CanInstantiateElementsView<test_input_view<hamon::tuple<char, float, double>>, 2>::value, "");
static_assert(!CanInstantiateElementsView<test_input_view<hamon::tuple<char, float, double>>, 3>::value, "");

static_assert( CanInstantiateElementsView<test_input_view<hamon::pair<int, long>>, 0>::value, "");
static_assert( CanInstantiateElementsView<test_input_view<hamon::pair<int, long>>, 1>::value, "");
static_assert(!CanInstantiateElementsView<test_input_view<hamon::pair<int, long>>, 2>::value, "");

GTEST_TEST(RangesTest, ElementsViewInstantiateTest)
{
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple>>;
		static_assert( CanInstantiateElementsView<V, 0>::value, "");
		static_assert( CanInstantiateElementsView<V, 1>::value, "");
	}
	{
		using Tuple = hamon::tuple<Movable, Movable>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple>>;
		static_assert( CanInstantiateElementsView<V, 0>::value, "");
		static_assert( CanInstantiateElementsView<V, 1>::value, "");
	}
	{
		using Tuple = hamon::tuple<Movable, NotMovable>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple>>;
		static_assert( CanInstantiateElementsView<V, 0>::value, "");
		static_assert(!CanInstantiateElementsView<V, 1>::value, "");
	}
	{
		using Tuple = hamon::tuple<NotMovable, Movable>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple>>;
		static_assert(!CanInstantiateElementsView<V, 0>::value, "");
		static_assert( CanInstantiateElementsView<V, 1>::value, "");
	}
	{
		using Tuple = hamon::tuple<Movable, NotMovable>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple&>>;
		static_assert( CanInstantiateElementsView<V, 0>::value, "");
		static_assert( CanInstantiateElementsView<V, 1>::value, "");
	}
	{
		using Tuple = hamon::tuple<NotMovable, Movable>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple&>>;
		static_assert( CanInstantiateElementsView<V, 0>::value, "");
		static_assert( CanInstantiateElementsView<V, 1>::value, "");
	}
}

}	// namespace instantiate_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
