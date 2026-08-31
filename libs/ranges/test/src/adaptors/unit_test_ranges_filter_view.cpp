/**
 *	@file	unit_test_ranges_filter_view.cpp
 *
 *	@brief	ranges::filter_view のテスト
 */

#include <hamon/ranges/adaptors/filter_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/concepts.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace filter_view_test
{

struct is_even
{
	HAMON_CXX11_CONSTEXPR bool operator()(int x) const HAMON_NOEXCEPT
	{
		return x % 2 == 0;
	}
};

struct is_odd
{
	HAMON_CXX11_CONSTEXPR bool operator()(int x) const HAMON_NOEXCEPT
	{
		return x % 2 == 1;
	}

	HAMON_CXX11_CONSTEXPR is_odd() {}
	HAMON_CXX11_CONSTEXPR is_odd(is_odd const&){}
	HAMON_CXX11_CONSTEXPR is_odd(is_odd &&){}
	HAMON_CXX14_CONSTEXPR is_odd& operator=(is_odd const&){return *this;}
	HAMON_CXX14_CONSTEXPR is_odd& operator=(is_odd &&){return *this;}
};

struct empty {};

template <typename V, typename Pred, typename = void>
struct CanInstantiateFilterView
	: hamon::false_type {};

template <typename V, typename Pred>
struct CanInstantiateFilterView<V, Pred, hamon::void_t<hamon::ranges::filter_view<V, Pred>>>
	: hamon::true_type {};

static_assert( CanInstantiateFilterView<test_input_view<int>, is_even>::value, "");
static_assert(!CanInstantiateFilterView<test_output_view<int>, is_even>::value, "");	// Vはinput_rangeでなければならない
static_assert(!CanInstantiateFilterView<test_input_view<int>, empty>::value, "");		// Predはindirect_unary_predicateでなければならない
static_assert(!CanInstantiateFilterView<test_input_range<int>, is_even>::value, "");	// Vはviewでなければならない

static_assert( hamon::is_invocable<decltype(hamon::views::filter), test_input_view<int>, is_even>::value, "");
static_assert(!hamon::is_invocable<decltype(hamon::views::filter), test_input_view<int>, empty>::value, "");
static_assert( hamon::is_invocable<decltype(hamon::views::filter), test_input_range<int>, is_even>::value, "");
static_assert( hamon::is_invocable<decltype(hamon::views::filter), is_even>::value, "");
static_assert( hamon::is_invocable<decltype(hamon::views::filter), empty>::value, "");

static_assert( noexcept(hamon::views::filter(hamon::declval<test_input_view<int>>(), hamon::declval<is_even>())), "");
static_assert(!noexcept(hamon::views::filter(hamon::declval<test_input_view<int>>(), hamon::declval<is_odd>())), "");
static_assert( noexcept(hamon::views::filter(hamon::declval<is_even>())), "");
static_assert(!noexcept(hamon::views::filter(hamon::declval<is_odd>())), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = View<T>;
	using Pred = is_even;
	using FV = hamon::ranges::filter_view<V, Pred>;

	static_assert(hamon::is_default_constructible<FV>::value ==
		hamon::is_default_constructible<V>::value && hamon::is_default_constructible<Pred>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<FV>::value ==
		hamon::is_nothrow_default_constructible<V>::value && hamon::is_nothrow_default_constructible<Pred>::value, "");

	static_assert(!hamon::is_constructible<FV, V>::value, "");
	static_assert(!hamon::is_constructible<FV, Pred>::value, "");
	static_assert( hamon::is_constructible<FV, V, Pred>::value, "");

	static_assert(hamon::ranges::range<FV> == true, "");
	static_assert(hamon::ranges::borrowed_range<FV> == false, "");
	static_assert(hamon::ranges::sized_range<FV> == false, "");
	static_assert(hamon::ranges::approximately_sized_range<FV> == false, "");
	static_assert(hamon::ranges::output_range<FV, T> == hamon::ranges::output_range<V, T>, "");
	static_assert(hamon::ranges::input_range<FV> == true, "");
	static_assert(hamon::ranges::forward_range<FV> == hamon::ranges::forward_range<V>, "");
	static_assert(hamon::ranges::bidirectional_range<FV> == hamon::ranges::bidirectional_range<V>, "");
	static_assert(hamon::ranges::random_access_range<FV> == false, "");
	static_assert(hamon::ranges::contiguous_range<FV> == false, "");
	static_assert(hamon::ranges::common_range<FV> == hamon::ranges::common_range<V>, "");
	static_assert(hamon::ranges::viewable_range<FV> == true, "");
	static_assert(hamon::ranges::view<FV> == true, "");
	static_assert(hamon::ranges::constant_range<FV> == false, "");

	static_assert(has_base<FV&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<FV&&>::value, "");
	static_assert(has_base<FV const&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<FV const&&>::value == hamon::copy_constructible<V>, "");

	static_assert(hamon::same_as<decltype(hamon::declval<FV&&>().base()), V>, "");
	static_assert(noexcept(hamon::declval<FV&&>().base()) == hamon::is_nothrow_move_constructible<V>::value, "");

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible<V>)
	{
		static_assert(hamon::same_as<decltype(hamon::declval<FV&>().base()), V>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<FV const&>().base()), V>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<FV const&&>().base()), V>, "");
		static_assert(noexcept(hamon::declval<FV&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
		static_assert(noexcept(hamon::declval<FV const&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
		static_assert(noexcept(hamon::declval<FV const&&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
	}
#endif

	static_assert(hamon::same_as<decltype(hamon::declval<FV&>().pred()), Pred const&>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<FV&&>().pred()), Pred const&>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<FV const&>().pred()), Pred const&>, "");
	static_assert(hamon::same_as<decltype(hamon::declval<FV const&&>().pred()), Pred const&>, "");
	static_assert(noexcept(hamon::declval<FV&>().pred()), "");

	static_assert( has_begin<FV&>::value, "");
	static_assert( has_begin<FV&&>::value, "");
	static_assert(!has_begin<FV const&>::value, "");
	static_assert(!has_begin<FV const&&>::value, "");
	static_assert( has_end<FV&>::value, "");
	static_assert( has_end<FV&&>::value, "");
	static_assert(!has_end<FV const&>::value, "");
	static_assert(!has_end<FV const&&>::value, "");
	using I = decltype(hamon::declval<FV&>().begin());
	using S = decltype(hamon::declval<FV&>().end());
	using BI = decltype(hamon::ranges::begin(hamon::declval<V&>()));
	static_assert(hamon::same_as<I, S> == hamon::ranges::common_range<V>, "");
	static_assert(has_iterator_category<I>::value == hamon::ranges::forward_range<V>, "");
	static_assert(hamon::same_as<typename I::value_type, hamon::ranges::range_value_t<V>>, "");
	static_assert(hamon::same_as<typename I::difference_type, hamon::ranges::range_difference_t<V>>, "");
	static_assert(hamon::default_initializable<I>, "");
	static_assert(hamon::is_nothrow_default_constructible<I>::value, "");
	static_assert(has_arrow<I>::value == (has_arrow<BI>::value && hamon::copyable<BI>), "");
	static_assert(has_pre_increment<I>::value, "");
	static_assert(has_post_increment<I>::value, "");
	static_assert(has_pre_decrement<I>::value == hamon::ranges::bidirectional_range<V>, "");
	static_assert(has_post_decrement<I>::value == hamon::ranges::bidirectional_range<V>, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using R = test_random_access_view<int>;
		using FV = hamon::ranges::filter_view<R, is_even>;

		static_assert( has_begin<FV&>::value, "");
		static_assert( has_end<FV&>::value, "");
		static_assert( has_empty<FV&>::value, "");
		static_assert( has_cbegin<FV&>::value, "");
		static_assert( has_cend<FV&>::value, "");
		static_assert( has_operator_bool<FV&>::value, "");
		static_assert(!has_data<FV&>::value, "");
		static_assert(!has_size<FV&>::value, "");
		static_assert(!has_reserve_hint<FV&>::value, "");
		static_assert( has_front<FV&>::value, "");
		static_assert(!has_back<FV&>::value, "");
		static_assert(!has_subscript<FV&>::value, "");
		static_assert( has_base<FV&>::value, "");

		static_assert(!has_begin<FV const&>::value, "");
		static_assert(!has_end<FV const&>::value, "");
		static_assert(!has_empty<FV const&>::value, "");
		static_assert(!has_cbegin<FV const&>::value, "");
		static_assert(!has_cend<FV const&>::value, "");
		static_assert(!has_operator_bool<FV const&>::value, "");
		static_assert(!has_data<FV const&>::value, "");
		static_assert(!has_size<FV const&>::value, "");
		static_assert(!has_reserve_hint<FV const&>::value, "");
		static_assert(!has_front<FV const&>::value, "");
		static_assert(!has_back<FV const&>::value, "");
		static_assert(!has_subscript<FV const&>::value, "");
		static_assert( has_base<FV const&>::value, "");

		FV fv{};
		VERIFY(fv.empty());
		VERIFY(fv.begin() == fv.end());
		VERIFY(fv.cbegin() == fv.cend());
		VERIFY((bool)fv == false);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		using R = test_random_access_view<int>;
		using FV = hamon::ranges::filter_view<R, is_even>;

		static_assert( has_begin<FV&>::value, "");
		static_assert( has_end<FV&>::value, "");
		static_assert( has_empty<FV&>::value, "");
		static_assert( has_cbegin<FV&>::value, "");
		static_assert( has_cend<FV&>::value, "");
		static_assert( has_operator_bool<FV&>::value, "");
		static_assert(!has_data<FV&>::value, "");
		static_assert(!has_size<FV&>::value, "");
		static_assert(!has_reserve_hint<FV&>::value, "");
		static_assert( has_front<FV&>::value, "");
		static_assert(!has_back<FV&>::value, "");
		static_assert(!has_subscript<FV&>::value, "");
		static_assert( has_base<FV&>::value, "");

		static_assert(!has_begin<FV const&>::value, "");
		static_assert(!has_end<FV const&>::value, "");
		static_assert(!has_empty<FV const&>::value, "");
		static_assert(!has_cbegin<FV const&>::value, "");
		static_assert(!has_cend<FV const&>::value, "");
		static_assert(!has_operator_bool<FV const&>::value, "");
		static_assert(!has_data<FV const&>::value, "");
		static_assert(!has_size<FV const&>::value, "");
		static_assert(!has_reserve_hint<FV const&>::value, "");
		static_assert(!has_front<FV const&>::value, "");
		static_assert(!has_back<FV const&>::value, "");
		static_assert(!has_subscript<FV const&>::value, "");
		static_assert( has_base<FV const&>::value, "");

		int a[] = {1, 2, 3, 4, 5};
		R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::filter_view fv{r, is_even{}};
		static_assert(hamon::same_as<decltype(fv), FV>, "");
#else
		FV fv{r, is_even{}};
#endif
		VERIFY(!fv.empty());
		VERIFY(fv.base().begin() == r.begin());
		VERIFY(hamon::move(fv).base().begin() == r.begin());

		auto it = fv.begin();
		VERIFY(it.base() != r.begin());
		VERIFY(hamon::move(it).base() != r.begin());

		VERIFY(it == fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it != fv.begin());
		VERIFY(it == fv.end());
		--it;
		VERIFY(it != fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 4);
		it--;
		VERIFY(it == fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 2);

		using I = decltype(it);
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::bidirectional_iterator_tag>, "");
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::bidirectional_iterator_tag>, "");

		using S = decltype(fv.end());
		I iter{};
		S sent{};
//		VERIFY(iter != fv.begin());
		VERIFY(iter != fv.end());
		VERIFY(iter == sent);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		using R = test_forward_view<int>;
		using FV = hamon::ranges::filter_view<R, is_even>;

		static_assert( has_begin<FV&>::value, "");
		static_assert( has_end<FV&>::value, "");
		static_assert( has_empty<FV&>::value, "");
		static_assert( has_cbegin<FV&>::value, "");
		static_assert( has_cend<FV&>::value, "");
		static_assert( has_operator_bool<FV&>::value, "");
		static_assert(!has_data<FV&>::value, "");
		static_assert(!has_size<FV&>::value, "");
		static_assert(!has_reserve_hint<FV&>::value, "");
		static_assert( has_front<FV&>::value, "");
		static_assert(!has_back<FV&>::value, "");
		static_assert(!has_subscript<FV&>::value, "");
		static_assert( has_base<FV&>::value, "");

		static_assert(!has_begin<FV const&>::value, "");
		static_assert(!has_end<FV const&>::value, "");
		static_assert(!has_empty<FV const&>::value, "");
		static_assert(!has_cbegin<FV const&>::value, "");
		static_assert(!has_cend<FV const&>::value, "");
		static_assert(!has_operator_bool<FV const&>::value, "");
		static_assert(!has_data<FV const&>::value, "");
		static_assert(!has_size<FV const&>::value, "");
		static_assert(!has_reserve_hint<FV const&>::value, "");
		static_assert(!has_front<FV const&>::value, "");
		static_assert(!has_back<FV const&>::value, "");
		static_assert(!has_subscript<FV const&>::value, "");
		static_assert( has_base<FV const&>::value, "");

		int a[] = {3, 1, 4, 1, 5, 9, 2};
		R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::filter_view fv{r, is_even{}};
		static_assert(hamon::same_as<decltype(fv), FV>, "");
#else
		FV fv{r, is_even{}};
#endif
		VERIFY(!fv.empty());
		VERIFY(fv.base().begin() == r.begin());
		VERIFY(hamon::move(fv).base().begin() == r.begin());

		auto it = fv.begin();
		VERIFY(it == fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != fv.begin());
		VERIFY(it != fv.end());
		VERIFY(fv.end() != it);
		VERIFY(*it == 2);
		it++;
		VERIFY(it != fv.begin());
		VERIFY(it == fv.end());
		VERIFY(fv.end() == it);

		using I = decltype(it);
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::forward_iterator_tag>, "");
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::same_as<typename I::iterator_category, hamon::forward_iterator_tag>, "");

		using S = decltype(fv.end());
		I iter{};
		S sent{};
//		VERIFY(iter != fv.begin());
		VERIFY(iter != fv.end());
		VERIFY(iter == sent);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	{
		using R = test_input_common_view<int>;
		using FV = hamon::ranges::filter_view<R, is_odd>;

		static_assert( has_begin<FV&>::value, "");
		static_assert( has_end<FV&>::value, "");
		static_assert(!has_empty<FV&>::value, "");
		static_assert( has_cbegin<FV&>::value, "");
		static_assert( has_cend<FV&>::value, "");
		static_assert(!has_operator_bool<FV&>::value, "");
		static_assert(!has_data<FV&>::value, "");
		static_assert(!has_size<FV&>::value, "");
		static_assert(!has_reserve_hint<FV&>::value, "");
		static_assert(!has_front<FV&>::value, "");
		static_assert(!has_back<FV&>::value, "");
		static_assert(!has_subscript<FV&>::value, "");
		static_assert( has_base<FV&>::value, "");

		static_assert(!has_begin<FV const&>::value, "");
		static_assert(!has_end<FV const&>::value, "");
		static_assert(!has_empty<FV const&>::value, "");
		static_assert(!has_cbegin<FV const&>::value, "");
		static_assert(!has_cend<FV const&>::value, "");
		static_assert(!has_operator_bool<FV const&>::value, "");
		static_assert(!has_data<FV const&>::value, "");
		static_assert(!has_size<FV const&>::value, "");
		static_assert(!has_reserve_hint<FV const&>::value, "");
		static_assert(!has_front<FV const&>::value, "");
		static_assert(!has_back<FV const&>::value, "");
		static_assert(!has_subscript<FV const&>::value, "");
		static_assert( has_base<FV const&>::value, "");

		int a[] = {1, 2, 3, 4, 5};
		R r(a);
		is_odd pred{};
		FV fv{r, pred};
		VERIFY(&fv.pred() != &pred);

		auto it = fv.begin();
		VERIFY(it.base() == r.begin());
		VERIFY(hamon::move(it).base() == r.begin());

		VERIFY(it == fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 3);
		it++;
		VERIFY(it != fv.begin());
		VERIFY(it != fv.end());
		VERIFY(fv.end() != it);
		VERIFY(*it == 5);
		it++;
		VERIFY(it != fv.begin());
		VERIFY(it == fv.end());
		VERIFY(fv.end() == it);

		using I = decltype(it);
		static_assert(hamon::same_as<typename I::iterator_concept, hamon::input_iterator_tag>, "");
		static_assert(!has_iterator_category<I>::value, "");

		using S = decltype(fv.end());
		I iter{};
		S sent{};
//		VERIFY(iter != fv.begin());
//		VERIFY(iter != fv.end());
		VERIFY(iter == sent);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	{
		using R = test_contiguous_view<int>;
		using FV = hamon::ranges::filter_view<R, is_odd>;

		static_assert( has_begin<FV&>::value, "");
		static_assert( has_end<FV&>::value, "");
		static_assert( has_empty<FV&>::value, "");
		static_assert( has_cbegin<FV&>::value, "");
		static_assert( has_cend<FV&>::value, "");
		static_assert( has_operator_bool<FV&>::value, "");
		static_assert(!has_data<FV&>::value, "");
		static_assert(!has_size<FV&>::value, "");
		static_assert(!has_reserve_hint<FV&>::value, "");
		static_assert( has_front<FV&>::value, "");
		static_assert(!has_back<FV&>::value, "");
		static_assert(!has_subscript<FV&>::value, "");
		static_assert( has_base<FV&>::value, "");

		static_assert(!has_begin<FV const&>::value, "");
		static_assert(!has_end<FV const&>::value, "");
		static_assert(!has_empty<FV const&>::value, "");
		static_assert(!has_cbegin<FV const&>::value, "");
		static_assert(!has_cend<FV const&>::value, "");
		static_assert(!has_operator_bool<FV const&>::value, "");
		static_assert(!has_data<FV const&>::value, "");
		static_assert(!has_size<FV const&>::value, "");
		static_assert(!has_reserve_hint<FV const&>::value, "");
		static_assert(!has_front<FV const&>::value, "");
		static_assert(!has_back<FV const&>::value, "");
		static_assert(!has_subscript<FV const&>::value, "");
		static_assert( has_base<FV const&>::value, "");

		int a[] = {1, 2, 3, 4, 5};
		R r(a);
		is_odd pred{};
		FV fv{r, pred};
		VERIFY(&fv.pred() != &pred);

		auto it = fv.begin();
		VERIFY(it.base() == r.begin());
		VERIFY(hamon::move(it).base() == r.begin());
		VERIFY(it.operator->() == r.begin());

		VERIFY(it == fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 3);
		it++;
		VERIFY(it != fv.begin());
		VERIFY(it != fv.end());
		VERIFY(*it == 5);
		it++;
		VERIFY(it != fv.begin());
		VERIFY(it == fv.end());

		auto sent = fv.end();
		VERIFY(sent.base() == hamon::ranges::end(r));
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
	{
		using R = test_contiguous_view<int>;
		using FV = hamon::ranges::filter_view<R, is_odd>;

		static_assert( has_begin<FV&>::value, "");
		static_assert( has_end<FV&>::value, "");
		static_assert( has_empty<FV&>::value, "");
		static_assert( has_cbegin<FV&>::value, "");
		static_assert( has_cend<FV&>::value, "");
		static_assert( has_operator_bool<FV&>::value, "");
		static_assert(!has_data<FV&>::value, "");
		static_assert(!has_size<FV&>::value, "");
		static_assert(!has_reserve_hint<FV&>::value, "");
		static_assert( has_front<FV&>::value, "");
		static_assert(!has_back<FV&>::value, "");
		static_assert(!has_subscript<FV&>::value, "");
		static_assert( has_base<FV&>::value, "");

		static_assert(!has_begin<FV const&>::value, "");
		static_assert(!has_end<FV const&>::value, "");
		static_assert(!has_empty<FV const&>::value, "");
		static_assert(!has_cbegin<FV const&>::value, "");
		static_assert(!has_cend<FV const&>::value, "");
		static_assert(!has_operator_bool<FV const&>::value, "");
		static_assert(!has_data<FV const&>::value, "");
		static_assert(!has_size<FV const&>::value, "");
		static_assert(!has_reserve_hint<FV const&>::value, "");
		static_assert(!has_front<FV const&>::value, "");
		static_assert(!has_back<FV const&>::value, "");
		static_assert(!has_subscript<FV const&>::value, "");
		static_assert( has_base<FV const&>::value, "");

		int a[] = {2, 3, 4, 5};
		R r(a);
		is_odd pred{};
		FV fv{r, pred};
		VERIFY(&fv.pred() != &pred);

		{
			auto it = fv.begin();
			auto ir = hamon::ranges::iter_move(it);
			VERIFY(ir == 3);
		}
		{
			auto it1 = fv.begin();
			auto it2 = fv.begin();
			it2++;
			VERIFY(*it1 == 3);
			VERIFY(*it2 == 5);
			hamon::ranges::iter_swap(it1, it2);
			VERIFY(*it1 == 5);
			VERIFY(*it2 == 3);
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test07()
{
	int const a[] = {3, 1, 4, 1, 5, 9, 2};
	auto fv = hamon::views::filter(a, is_odd{});
	auto it = fv.begin();
	VERIFY(it != fv.end());
	VERIFY(*it++ == 3);
	VERIFY(it != fv.end());
	VERIFY(*it++ == 1);
	VERIFY(it != fv.end());
	VERIFY(*it++ == 1);
	VERIFY(it != fv.end());
	VERIFY(*it++ == 5);
	VERIFY(it != fv.end());
	VERIFY(*it++ == 9);
	VERIFY(it == fv.end());
	return true;
}

HAMON_CXX14_CONSTEXPR bool test08()
{
	int const a[] = {3, 1, 4, 1, 5, 9, 2};
	auto fv = a | hamon::views::filter(is_odd{});
	auto it = fv.begin();
	VERIFY(it != fv.end());
	VERIFY(*it++ == 3);
	VERIFY(it != fv.end());
	VERIFY(*it++ == 1);
	VERIFY(it != fv.end());
	VERIFY(*it++ == 1);
	VERIFY(it != fv.end());
	VERIFY(*it++ == 5);
	VERIFY(it != fv.end());
	VERIFY(*it++ == 9);
	VERIFY(it == fv.end());
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, FilterViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_view>());

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

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_approximately_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_approximately_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_approximately_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_approximately_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_approximately_sized_view>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test08());
}

}	// namespace filter_view_test
}	// namespace hamon_ranges_test
