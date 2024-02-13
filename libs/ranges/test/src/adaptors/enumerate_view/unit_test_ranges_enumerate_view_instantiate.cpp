/**
 *	@file	unit_test_ranges_enumerate_view_instantiate.cpp
 *
 *	@brief	enumerate_view のテスト
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace instantiate_test
{

template <typename ValueType, typename Reference, typename IterMoveResult>
struct TestIterator
{
	ValueType* m_ptr;

	using iterator_category = hamon::input_iterator_tag;
	using value_type        = ValueType;
	using difference_type   = hamon::ptrdiff_t;

	TestIterator& operator++();
	void          operator++(int);
	Reference     operator*() const;
	bool operator==(const TestIterator& rhs) const;
	bool operator!=(const TestIterator& rhs) const;

	friend IterMoveResult iter_move(TestIterator const& it) { return *it.m_ptr; }
};

struct NotMovable
{
	NotMovable(NotMovable const&) = default;
	NotMovable(NotMovable&&) = delete;
};

template <typename T, typename = void>
struct CanInstantiateEnumerateView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateEnumerateView<T, hamon::void_t<hamon::ranges::enumerate_view<T>>>
	: hamon::true_type {};

static_assert( CanInstantiateEnumerateView<test_input_view<int>>::value, "");
static_assert(!CanInstantiateEnumerateView<test_input_range<int>>::value, "");	// requires view<V>
static_assert(!CanInstantiateEnumerateView<test_output_view<int>>::value, "");	// requires input_range<V>
static_assert(!CanInstantiateEnumerateView<test_view<NotMovable, TestIterator<NotMovable, NotMovable, NotMovable>>>::value, "");
static_assert(!CanInstantiateEnumerateView<test_view<NotMovable, TestIterator<NotMovable, NotMovable, NotMovable&>>>::value, "");	// requires move_constructible<range_reference_t<V>>
static_assert(!CanInstantiateEnumerateView<test_view<NotMovable, TestIterator<NotMovable, NotMovable&, NotMovable>>>::value, "");	// requires move_constructible<range_rvalue_reference_t<V>>
static_assert( CanInstantiateEnumerateView<test_view<NotMovable, TestIterator<NotMovable, NotMovable&, NotMovable&>>>::value, "");

}	// namespace instantiate_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
