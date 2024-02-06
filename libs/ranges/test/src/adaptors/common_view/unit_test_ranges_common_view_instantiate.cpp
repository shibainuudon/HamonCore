/**
 *	@file	unit_test_ranges_common_view_instantiate.cpp
 *
 *	@brief	common_view のテスト
 */

#include <hamon/ranges/adaptors/common_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace common_view_test
{
namespace instantiate_test
{

template <typename T>
struct MoveOnlyInputIterator
{
	T*	m_ptr = nullptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	MoveOnlyInputIterator() = default;
	MoveOnlyInputIterator(T* ptr) : m_ptr(ptr) { }
	MoveOnlyInputIterator(MoveOnlyInputIterator&&) = default;
	MoveOnlyInputIterator& operator=(MoveOnlyInputIterator&&) = default;
	HAMON_CXX14_CONSTEXPR MoveOnlyInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void                   operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                     operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const MoveOnlyInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const MoveOnlyInputIterator& rhs) const { return !(*this == rhs); }
};

template <typename T, typename Iterator, typename Sentinel>
struct TestView : hamon::ranges::view_base
{
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;
};

template <typename T, typename = void>
struct CanInstantiateCommonView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateCommonView<T, hamon::void_t<hamon::ranges::common_view<T>>>
	: hamon::true_type {};

static_assert( CanInstantiateCommonView<test_input_view<int>>::value, "");
static_assert(!CanInstantiateCommonView<test_input_range<int>>::value, "");
static_assert(!CanInstantiateCommonView<test_input_common_view<int>>::value, "");
static_assert(!CanInstantiateCommonView<TestView<int, MoveOnlyInputIterator<int>, hamon::unreachable_sentinel_t>>::value, "");

}	// namespace instantiate_test
}	// namespace common_view_test
}	// namespace hamon_ranges_test
