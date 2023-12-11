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
#include <hamon/iterator/concepts/detail/has_iterator_category.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace filter_view_test
{

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_arrow
	: public hamon::false_type {};

template <typename T>
struct has_arrow<T, hamon::void_t<decltype(hamon::declval<T>().operator->())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pre_increment
	: public hamon::false_type {};

template <typename T>
struct has_pre_increment<T, hamon::void_t<decltype(++hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_post_increment
	: public hamon::false_type {};

template <typename T>
struct has_post_increment<T, hamon::void_t<decltype(hamon::declval<T>()++)>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pre_decrement
	: public hamon::false_type {};

template <typename T>
struct has_pre_decrement<T, hamon::void_t<decltype(--hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_post_decrement
	: public hamon::false_type {};

template <typename T>
struct has_post_decrement<T, hamon::void_t<decltype(hamon::declval<T>()--)>>
	: public hamon::true_type {};

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
	using RV = hamon::ranges::filter_view<V, Pred>;

	static_assert(hamon::is_default_constructible<RV>::value ==
		hamon::is_default_constructible<V>::value && hamon::is_default_constructible<Pred>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<RV>::value ==
		hamon::is_nothrow_default_constructible<V>::value && hamon::is_nothrow_default_constructible<Pred>::value, "");

	static_assert(!hamon::is_constructible<RV, V>::value, "");
	static_assert(!hamon::is_constructible<RV, Pred>::value, "");
	static_assert( hamon::is_constructible<RV, V, Pred>::value, "");

	static_assert(hamon::ranges::range_t<RV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::output_range_t<RV, T>::value == hamon::ranges::output_range_t<V, T>::value, "");
	static_assert(hamon::ranges::input_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value == hamon::ranges::bidirectional_range_t<V>::value, "");
	static_assert(hamon::ranges::random_access_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::contiguous_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::common_range_t<RV>::value == hamon::ranges::common_range_t<V>::value, "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::view_t<RV>::value == true, "");

	static_assert(has_base<RV&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV&&>::value, "");
	static_assert(has_base<RV const&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV const&&>::value == hamon::copy_constructible_t<V>::value, "");

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&&>().base()), V>::value, "");
#if !defined(HAMON_USE_STD_RANGES)
	static_assert(noexcept(hamon::declval<RV&&>().base()) == hamon::is_nothrow_move_constructible<V>::value, "");
#endif

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible_t<V>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&&>().base()), V>::value, "");
#if !defined(HAMON_USE_STD_RANGES)
		static_assert(noexcept(hamon::declval<RV&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
		static_assert(noexcept(hamon::declval<RV const&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
		static_assert(noexcept(hamon::declval<RV const&&>().base()) == hamon::is_nothrow_copy_constructible<V>::value, "");
#endif
	}
#endif

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().pred()), Pred const&>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&&>().pred()), Pred const&>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().pred()), Pred const&>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&&>().pred()), Pred const&>::value, "");
#if !defined(HAMON_USE_STD_RANGES)
	static_assert(noexcept(hamon::declval<RV&>().pred()), "");
#endif

	static_assert( has_begin<RV&>::value, "");
	static_assert( has_begin<RV&&>::value, "");
	static_assert(!has_begin<RV const&>::value, "");
	static_assert(!has_begin<RV const&&>::value, "");
	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV&&>::value, "");
	static_assert(!has_end<RV const&>::value, "");
	static_assert(!has_end<RV const&&>::value, "");
	using I = decltype(hamon::declval<RV&>().begin());
	using S = decltype(hamon::declval<RV&>().end());
	using BI = decltype(hamon::ranges::begin(hamon::declval<V&>()));
	static_assert(hamon::same_as_t<I, S>::value == hamon::ranges::common_range_t<V>::value, "");
	static_assert(hamon::detail::has_iterator_category<I>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::same_as_t<typename I::value_type, hamon::ranges::range_value_t<V>>::value, "");
	static_assert(hamon::same_as_t<typename I::difference_type, hamon::ranges::range_difference_t<V>>::value, "");
	static_assert(hamon::default_initializable_t<I>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<I>::value, "");
	static_assert(has_arrow<I>::value == (has_arrow<BI>::value && hamon::copyable_t<BI>::value), "");
	static_assert(has_pre_increment<I>::value, "");
	static_assert(has_post_increment<I>::value, "");
	static_assert(has_pre_decrement<I>::value == hamon::ranges::bidirectional_range_t<V>::value, "");
	static_assert(has_post_decrement<I>::value == hamon::ranges::bidirectional_range_t<V>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using R = test_random_access_view<int>;
		hamon::ranges::filter_view<R, is_even> rv{};
		VERIFY(rv.empty());
		VERIFY(rv.begin() == rv.end());
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int a[] = {1, 2, 3, 4, 5};
		using R = test_random_access_view<int>;
		R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::filter_view rv{r, is_even{}};
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::filter_view<R, is_even>>::value, "");
#else
		hamon::ranges::filter_view<R, is_even> rv{r, is_even{}};
#endif
		VERIFY(!rv.empty());
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(hamon::move(rv).base().begin() == r.begin());

		auto it = rv.begin();
		VERIFY(it.base() != r.begin());
		VERIFY(hamon::move(it).base() != r.begin());

		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());
		--it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		it--;
		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 2);

		using I = decltype(it);
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert( hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");

		using S = decltype(rv.end());
		I iter{};
		S sent{};
//		VERIFY(iter != rv.begin());
		VERIFY(iter != rv.end());
		VERIFY(iter == sent);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		int a[] = {3, 1, 4, 1, 5, 9, 2};
		using R = test_forward_view<int>;
		R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::ranges::filter_view rv{r, is_even{}};
		static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::filter_view<R, is_even>>::value, "");
#else
		hamon::ranges::filter_view<R, is_even> rv{r, is_even{}};
#endif
		VERIFY(!rv.empty());
		VERIFY(rv.base().begin() == r.begin());
		VERIFY(hamon::move(rv).base().begin() == r.begin());

		auto it = rv.begin();
		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 4);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(rv.end() != it);
		VERIFY(*it == 2);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());
		VERIFY(rv.end() == it);

		using I = decltype(it);
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert( hamon::detail::has_iterator_category<I>::value, "");
		static_assert(hamon::same_as_t<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");

		using S = decltype(rv.end());
		I iter{};
		S sent{};
//		VERIFY(iter != rv.begin());
		VERIFY(iter != rv.end());
		VERIFY(iter == sent);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	{
		int a[] = {1, 2, 3, 4, 5};
		using R = test_input_common_view<int>;
		R r(a);
		is_odd pred{};
		hamon::ranges::filter_view<R, is_odd> rv{r, pred};
		VERIFY(&rv.pred() != &pred);

		auto it = rv.begin();
		VERIFY(it.base() == r.begin());
		VERIFY(hamon::move(it).base() == r.begin());

		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(rv.end() != it);
		VERIFY(*it == 5);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());
		VERIFY(rv.end() == it);

		using I = decltype(it);
		static_assert(hamon::same_as_t<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(!hamon::detail::has_iterator_category<I>::value, "");

		using S = decltype(rv.end());
		I iter{};
		S sent{};
//		VERIFY(iter != rv.begin());
//		VERIFY(iter != rv.end());
		VERIFY(iter == sent);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	{
		int a[] = {1, 2, 3, 4, 5};
		using R = test_contiguous_view<int>;
		R r(a);
		is_odd pred{};
		hamon::ranges::filter_view<R, is_odd> rv{r, pred};
		VERIFY(&rv.pred() != &pred);

		auto it = rv.begin();
		VERIFY(it.base() == r.begin());
		VERIFY(hamon::move(it).base() == r.begin());
		VERIFY(it.operator->() == r.begin());

		VERIFY(it == rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 3);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it != rv.end());
		VERIFY(*it == 5);
		it++;
		VERIFY(it != rv.begin());
		VERIFY(it == rv.end());

		auto sent = rv.end();
		VERIFY(sent.base() == hamon::ranges::end(r));
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
	{
		int a[] = {2, 3, 4, 5};
		using R = test_contiguous_view<int>;
		R r(a);
		is_odd pred{};
		hamon::ranges::filter_view<R, is_odd> rv{r, pred};
		VERIFY(&rv.pred() != &pred);

		{
			auto it = rv.begin();
			auto ir = hamon::ranges::iter_move(it);
			VERIFY(ir == 3);
		}
		{
			auto it1 = rv.begin();
			auto it2 = rv.begin();
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
	auto rv = hamon::views::filter(a, is_odd{});
	auto it = rv.begin();
	VERIFY(it != rv.end());
	VERIFY(*it++ == 3);
	VERIFY(it != rv.end());
	VERIFY(*it++ == 1);
	VERIFY(it != rv.end());
	VERIFY(*it++ == 1);
	VERIFY(it != rv.end());
	VERIFY(*it++ == 5);
	VERIFY(it != rv.end());
	VERIFY(*it++ == 9);
	VERIFY(it == rv.end());
	return true;
}

HAMON_CXX14_CONSTEXPR bool test08()
{
	int const a[] = {3, 1, 4, 1, 5, 9, 2};
	auto rv = a | hamon::views::filter(is_odd{});
	auto it = rv.begin();
	VERIFY(it != rv.end());
	VERIFY(*it++ == 3);
	VERIFY(it != rv.end());
	VERIFY(*it++ == 1);
	VERIFY(it != rv.end());
	VERIFY(*it++ == 1);
	VERIFY(it != rv.end());
	VERIFY(*it++ == 5);
	VERIFY(it != rv.end());
	VERIFY(*it++ == 9);
	VERIFY(it == rv.end());
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
