/**
 *	@file	unit_test_ranges_lazy_split_view_concepts.cpp
 *
 *	@brief	lazy_split_view のテスト
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <gtest/gtest.h>
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace concepts_test
{

template <typename T, typename V, typename Pattern>
void test()
{
	using LSV = hamon::ranges::lazy_split_view<V, Pattern>;

	static_assert(hamon::ranges::range_t<LSV>::value                     == true, "");
	static_assert(hamon::ranges::borrowed_range<LSV>            == false, "");
	static_assert(hamon::ranges::sized_range_t<LSV>::value               == false, "");
	static_assert(hamon::ranges::approximately_sized_range<LSV> == false, "");
	static_assert(hamon::ranges::output_range_t<LSV, T>::value           == false, "");
	static_assert(hamon::ranges::input_range_t<LSV>::value               == true, "");
	static_assert(hamon::ranges::forward_range<LSV>             == hamon::ranges::forward_range<V>, "");
	static_assert(hamon::ranges::bidirectional_range<LSV> == false, "");
	static_assert(hamon::ranges::random_access_range_t<LSV>::value       == false, "");
	static_assert(hamon::ranges::contiguous_range<LSV> == false, "");
	static_assert(hamon::ranges::common_range<LSV>              == hamon::ranges::common_range<V>, "");
	static_assert(hamon::ranges::viewable_range_t<LSV>::value            == true, "");
	static_assert(hamon::ranges::view_t<LSV>::value                      == true, "");
	static_assert(hamon::ranges::constant_range<LSV>            == false, "");

	static_assert(has_begin<LSV&>::value         == true, "");
	static_assert(has_end<LSV&>::value           == true, "");
	static_assert(has_empty<LSV&>::value         == hamon::ranges::forward_range<LSV>, "");
	static_assert(has_cbegin<LSV&>::value        == true, "");
	static_assert(has_cend<LSV&>::value          == true, "");
	static_assert(has_operator_bool<LSV&>::value == hamon::ranges::forward_range<LSV>, "");
	static_assert(has_data<LSV&>::value          == false, "");
	static_assert(has_size<LSV&>::value          == false, "");
	static_assert(has_reserve_hint<LSV&>::value  == false, "");
	static_assert(has_front<LSV&>::value         == hamon::ranges::forward_range<LSV>, "");
	static_assert(has_back<LSV&>::value          == false, "");
	static_assert(has_subscript<LSV&>::value     == false, "");
	static_assert(has_base<LSV&>::value          == true, "");

	static_assert(has_begin<LSV const&>::value         == hamon::ranges::forward_range<LSV const>, "");
	static_assert(has_end<LSV const&>::value           == true, "");
	static_assert(has_empty<LSV const&>::value         == hamon::ranges::forward_range<LSV const>, "");
	static_assert(has_cbegin<LSV const&>::value        == hamon::ranges::forward_range<LSV const>, "");
	static_assert(has_cend<LSV const&>::value          == hamon::ranges::input_range_t<LSV const>::value, "");
	static_assert(has_operator_bool<LSV const&>::value == hamon::ranges::forward_range<LSV const>, "");
	static_assert(has_data<LSV const&>::value          == false, "");
	static_assert(has_size<LSV const&>::value          == false, "");
	static_assert(has_reserve_hint<LSV const&>::value  == false, "");
	static_assert(has_front<LSV const&>::value         == hamon::ranges::forward_range<LSV const>, "");
	static_assert(has_back<LSV const&>::value          == false, "");
	static_assert(has_subscript<LSV const&>::value     == false, "");
	static_assert(has_base<LSV const&>::value          == true, "");

	using IV = hamon::ranges::range_reference_t<LSV>;

	static_assert(hamon::ranges::range_t<IV>::value                     == true, "");
	static_assert(hamon::ranges::borrowed_range<IV>            == false, "");
	static_assert(hamon::ranges::sized_range_t<IV>::value               == false, "");
	static_assert(hamon::ranges::approximately_sized_range<IV> == false, "");
	static_assert(hamon::ranges::output_range_t<IV, T>::value           == hamon::ranges::forward_range<V>, "");
	static_assert(hamon::ranges::input_range_t<IV>::value               == true, "");
	static_assert(hamon::ranges::forward_range<IV>             == hamon::ranges::forward_range<V>, "");
	static_assert(hamon::ranges::bidirectional_range<IV>       == false, "");
	static_assert(hamon::ranges::random_access_range_t<IV>::value       == false, "");
	static_assert(hamon::ranges::contiguous_range<IV>          == false, "");
	static_assert(hamon::ranges::common_range<IV>              == false, "");
	static_assert(hamon::ranges::viewable_range_t<IV>::value            == true, "");
	static_assert(hamon::ranges::view_t<IV>::value                      == true, "");
	static_assert(hamon::ranges::constant_range<IV>            == false, "");
}

GTEST_TEST(RangesTest, LazySplitViewConceptsTest)
{
	using T = int;
	test<T, test_input_view<T>,   test_forward_static_sized_view<T, 0>>();
	test<T, test_input_view<T>,   test_forward_static_sized_view<T, 1>>();
	test<T, test_input_view<T*>,  test_forward_static_sized_view<T*, 1>>();

	test<T, test_forward_view<T>, test_forward_view<T>>();
	test<T, test_forward_view<T>, test_bidirectional_view<T>>();
	test<T, test_forward_view<T>, test_random_access_view<T>>();
	test<T, test_forward_view<T>, test_contiguous_view<T>>();

	test<T, test_forward_common_view<T>, test_forward_view<T>>();
	test<T, test_forward_common_view<T>, test_bidirectional_view<T>>();
	test<T, test_forward_common_view<T>, test_random_access_view<T>>();
	test<T, test_forward_common_view<T>, test_contiguous_view<T>>();

	test<T, test_forward_borrowed_view<T>, test_forward_view<T>>();
	test<T, test_forward_borrowed_view<T>, test_bidirectional_view<T>>();
	test<T, test_forward_borrowed_view<T>, test_random_access_view<T>>();
	test<T, test_forward_borrowed_view<T>, test_contiguous_view<T>>();

	test<T, test_forward_sized_view<T>, test_forward_view<T>>();
	test<T, test_forward_sized_view<T>, test_bidirectional_view<T>>();
	test<T, test_forward_sized_view<T>, test_random_access_view<T>>();
	test<T, test_forward_sized_view<T>, test_contiguous_view<T>>();

	test<T, test_forward_approximately_sized_view<T>, test_forward_view<T>>();
	test<T, test_forward_approximately_sized_view<T>, test_bidirectional_view<T>>();
	test<T, test_forward_approximately_sized_view<T>, test_random_access_view<T>>();
	test<T, test_forward_approximately_sized_view<T>, test_contiguous_view<T>>();
}

}	// namespace concepts_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
