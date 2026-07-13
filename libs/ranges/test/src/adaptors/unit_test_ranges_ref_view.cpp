/**
 *	@file	unit_test_ranges_ref_view.cpp
 *
 *	@brief	ranges::ref_view のテスト
 */

#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/concepts.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace ref_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using R = RangeWrapper<T>;
	using RV = hamon::ranges::ref_view<RangeWrapper<T>>;

	static_assert(!hamon::constructible_from<RV, T>, "");
	static_assert(!hamon::constructible_from<RV, T&>, "");
	static_assert(!hamon::constructible_from<RV, T&&>, "");
	static_assert(!hamon::constructible_from<RV, T const>, "");
	static_assert(!hamon::constructible_from<RV, T const&>, "");
	static_assert(!hamon::constructible_from<RV, T const&&>, "");

	static_assert(!hamon::constructible_from<RV, R>, "");
	static_assert( hamon::constructible_from<RV, R&>, "");
	static_assert(!hamon::constructible_from<RV, R&&>, "");
	static_assert(!hamon::constructible_from<RV, R const>, "");
	static_assert(!hamon::constructible_from<RV, R const&>, "");
	static_assert(!hamon::constructible_from<RV, R const&&>, "");

	static_assert( hamon::constructible_from<RV, RV>, "");
	static_assert( hamon::constructible_from<RV, RV&>, "");
	static_assert( hamon::constructible_from<RV, RV&&>, "");
	static_assert( hamon::constructible_from<RV, RV const>, "");
	static_assert( hamon::constructible_from<RV, RV const&>, "");
	static_assert( hamon::constructible_from<RV, RV const&&>, "");

	static_assert( hamon::ranges::range_t<RV>::value, "");
	static_assert( hamon::ranges::borrowed_range<RV>, "");
	static_assert( hamon::ranges::sized_range_t<RV>::value == hamon::ranges::sized_range_t<R>::value, "");
	static_assert( hamon::ranges::approximately_sized_range<RV> == hamon::ranges::approximately_sized_range<R>, "");
	static_assert( hamon::ranges::output_range_t<RV, T>::value == hamon::ranges::output_range_t<R, T>::value, "");
	static_assert( hamon::ranges::input_range_t<RV>::value == hamon::ranges::input_range_t<R>::value, "");
	static_assert( hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<R>::value, "");
	static_assert( hamon::ranges::bidirectional_range<RV> == hamon::ranges::bidirectional_range<R>, "");
	static_assert( hamon::ranges::random_access_range_t<RV>::value == hamon::ranges::random_access_range_t<R>::value, "");
	static_assert( hamon::ranges::contiguous_range_t<RV>::value == hamon::ranges::contiguous_range_t<R>::value, "");
	static_assert( hamon::ranges::common_range<RV> == hamon::ranges::common_range<R>, "");
	static_assert( hamon::ranges::viewable_range_t<RV>::value, "");
	static_assert( hamon::ranges::view_t<RV>::value, "");
	static_assert(!hamon::ranges::constant_range<RV>, "");

	static_assert(hamon::same_as<decltype(hamon::declval<RV>().base()), R&>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<RV>().begin()), hamon::ranges::iterator_t<R>>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<RV>().end()), hamon::ranges::sentinel_t<R>>, "");
	
	static_assert(has_empty<RV>::value ==
		(hamon::ranges::sized_range_t<R>::value || hamon::ranges::forward_range_t<R>::value), "");
	static_assert(has_size<RV>::value == hamon::ranges::sized_range_t<R>::value, "");
	static_assert(has_reserve_hint<RV>::value == hamon::ranges::approximately_sized_range<R>, "");
	static_assert(has_data<RV>::value == hamon::ranges::contiguous_range_t<R>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using R = test_random_access_range<int>;
	using RV = hamon::ranges::ref_view<R>;

	static_assert( has_begin<RV&>::value, "");
	static_assert( has_end<RV&>::value, "");
	static_assert( has_empty<RV&>::value, "");
	static_assert( has_cbegin<RV&>::value, "");
	static_assert( has_cend<RV&>::value, "");
	static_assert( has_operator_bool<RV&>::value, "");
	static_assert(!has_data<RV&>::value, "");
	static_assert( has_size<RV&>::value, "");
	static_assert( has_reserve_hint<RV&>::value, "");
	static_assert( has_front<RV&>::value, "");
	static_assert(!has_back<RV&>::value, "");
	static_assert( has_subscript<RV&>::value, "");

	static_assert( has_begin<RV const&>::value, "");
	static_assert( has_end<RV const&>::value, "");
	static_assert( has_empty<RV const&>::value, "");
	static_assert( has_cbegin<RV const&>::value, "");
	static_assert( has_cend<RV const&>::value, "");
	static_assert( has_operator_bool<RV const&>::value, "");
	static_assert(!has_data<RV const&>::value, "");
	static_assert( has_size<RV const&>::value, "");
	static_assert( has_reserve_hint<RV const&>::value, "");
	static_assert( has_front<RV const&>::value, "");
	static_assert(!has_back<RV const&>::value, "");
	static_assert( has_subscript<RV const&>::value, "");

	int a[2] = {1, 2};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::ref_view rv{r};
	static_assert(hamon::same_as<decltype(rv), RV>, "");
#else
	RV rv{r};
#endif

	VERIFY(&rv.base() == &r);
	VERIFY(!rv.empty());
	VERIFY(rv.size() == 2);
	VERIFY(rv.reserve_hint() == 2);
	VERIFY(rv.begin() == r.begin());
	VERIFY(rv.cbegin() == r.begin());
	VERIFY(rv.end().m_it == r.end().m_it);
	VERIFY(rv.cend().m_it == r.end().m_it);
	VERIFY(rv.front() == 1);
	VERIFY(rv[1] == 2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using R = test_contiguous_range<int>;
	using RV = hamon::ranges::ref_view<R>;

	static_assert( has_begin<RV&>::value, "");
	static_assert( has_end<RV&>::value, "");
	static_assert( has_empty<RV&>::value, "");
	static_assert( has_cbegin<RV&>::value, "");
	static_assert( has_cend<RV&>::value, "");
	static_assert( has_operator_bool<RV&>::value, "");
	static_assert( has_data<RV&>::value, "");
	static_assert( has_size<RV&>::value, "");
	static_assert( has_reserve_hint<RV&>::value, "");
	static_assert( has_front<RV&>::value, "");
	static_assert(!has_back<RV&>::value, "");
	static_assert( has_subscript<RV&>::value, "");

	static_assert( has_begin<RV const&>::value, "");
	static_assert( has_end<RV const&>::value, "");
	static_assert( has_empty<RV const&>::value, "");
	static_assert( has_cbegin<RV const&>::value, "");
	static_assert( has_cend<RV const&>::value, "");
	static_assert( has_operator_bool<RV const&>::value, "");
	static_assert( has_data<RV const&>::value, "");
	static_assert( has_size<RV const&>::value, "");
	static_assert( has_reserve_hint<RV const&>::value, "");
	static_assert( has_front<RV const&>::value, "");
	static_assert(!has_back<RV const&>::value, "");
	static_assert( has_subscript<RV const&>::value, "");

	int a[3] = {3, 4, 5};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::ref_view rv{r};
	static_assert(hamon::same_as<decltype(rv), RV>, "");
#else
	RV rv{r};
#endif

	VERIFY(&rv.base() == &r);
	VERIFY(!rv.empty());
	VERIFY(rv.size() == 3);
	VERIFY(rv.reserve_hint() == 3);
	VERIFY(rv.begin() == r.begin());
	VERIFY(rv.end().m_it == r.end().m_it);
	VERIFY(rv.data() == a);

	VERIFY(rv.cbegin() == r.begin());
	VERIFY(rv.cend().m_it == r.end().m_it);
	VERIFY(rv.front() == 3);
	VERIFY(rv[1] == 4);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using R = test_input_approximately_sized_range<int>;
	using RV = hamon::ranges::ref_view<R>;

	static_assert( has_begin<RV&>::value, "");
	static_assert( has_end<RV&>::value, "");
	static_assert(!has_empty<RV&>::value, "");
	static_assert( has_cbegin<RV&>::value, "");
	static_assert( has_cend<RV&>::value, "");
	static_assert(!has_operator_bool<RV&>::value, "");
	static_assert(!has_data<RV&>::value, "");
	static_assert(!has_size<RV&>::value, "");
	static_assert( has_reserve_hint<RV&>::value, "");
	static_assert(!has_front<RV&>::value, "");
	static_assert(!has_back<RV&>::value, "");
	static_assert(!has_subscript<RV&>::value, "");

	static_assert( has_begin<RV const&>::value, "");
	static_assert( has_end<RV const&>::value, "");
	static_assert(!has_empty<RV const&>::value, "");
	static_assert( has_cbegin<RV const&>::value, "");
	static_assert( has_cend<RV const&>::value, "");
	static_assert(!has_operator_bool<RV const&>::value, "");
	static_assert(!has_data<RV const&>::value, "");
	static_assert(!has_size<RV const&>::value, "");
	static_assert( has_reserve_hint<RV const&>::value, "");
	static_assert(!has_front<RV const&>::value, "");
	static_assert(!has_back<RV const&>::value, "");
	static_assert(!has_subscript<RV const&>::value, "");

	int a[3] = {3, 4, 5};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::ref_view rv{r};
	static_assert(hamon::same_as<decltype(rv), RV>, "");
#else
	RV rv{r};
#endif

	VERIFY(&rv.base() == &r);
	VERIFY(rv.reserve_hint() == 3);
	VERIFY(rv.begin() == r.begin());
	VERIFY(rv.end().m_it == r.end().m_it);

	VERIFY(rv.cbegin() == r.begin());
	VERIFY(rv.cend().m_it == r.end().m_it);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, RefViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_range>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_common_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_common_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_borrowed_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_borrowed_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_borrowed_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_borrowed_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_borrowed_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_sized_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_approximately_sized_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_approximately_sized_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_approximately_sized_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_approximately_sized_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_approximately_sized_range>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace ref_view_test
}	// namespace hamon_ranges_test
