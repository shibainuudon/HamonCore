/**
 *	@file	unit_test_ranges_lazy_split_view_instantiate.cpp
 *
 *	@brief	ranges::lazy_split_view のテスト
 * 
 *	template<input_range V, forward_range Pattern>
 *	  requires view<V> && view<Pattern> &&
 *	    indirectly_comparable<iterator_t<V>, iterator_t<Pattern>, ranges::equal_to> &&
 *	    (forward_range<V> || tiny-range<Pattern>)
 *	class lazy_split_view;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace instantiate_test
{

template <typename T, hamon::size_t N, template <typename> class Iterator>
struct NoConstexprStaticSizedView : public test_range<T, Iterator<T>>
	, public hamon::ranges::view_base
{
	using test_range<T, Iterator<T>>::test_range;

	static hamon::size_t size() noexcept
	{
		return N;
	}
};

template <typename T, hamon::size_t N>
using ForwardNoConstexprStaticSizedView = NoConstexprStaticSizedView<T, N, forward_iterator_wrapper>;

template <typename T, typename U, typename = void>
struct CanInstantiateLazySplitView
	: hamon::false_type {};

template <typename T, typename U>
struct CanInstantiateLazySplitView<T, U, hamon::void_t<hamon::ranges::lazy_split_view<T, U>>>
	: hamon::true_type {};

static_assert( CanInstantiateLazySplitView<test_input_view<int>, test_forward_static_sized_view<int, 0>>::value, "");
static_assert( CanInstantiateLazySplitView<test_input_view<int>, test_forward_static_sized_view<int, 1>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_input_view<int>, test_forward_static_sized_view<int, 2>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_input_view<int>, test_forward_static_sized_range<int, 1>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_input_range<int>, test_forward_static_sized_view<int, 1>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_input_view<int>, test_input_static_sized_view<int, 1>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_input_view<int>, test_forward_view<int>>::value, "");
static_assert( CanInstantiateLazySplitView<test_forward_view<int>, test_forward_view<int>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_forward_view<int>, test_input_view<int>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_forward_range<int>, test_forward_view<int>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_forward_view<int>, test_forward_range<int>>::value, "");
static_assert( CanInstantiateLazySplitView<test_input_view<int*>, test_forward_static_sized_view<int*, 1>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_input_view<int*>, test_forward_static_sized_view<int, 1>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_forward_view<int>, test_forward_view<int*>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_input_view<int>, ForwardNoConstexprStaticSizedView<int, 0>>::value, "");
static_assert(!CanInstantiateLazySplitView<test_input_view<int>, ForwardNoConstexprStaticSizedView<int, 1>>::value, "");

}	// namespace instantiate_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
