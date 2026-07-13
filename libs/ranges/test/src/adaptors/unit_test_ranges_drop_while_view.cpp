/**
 *	@file	unit_test_ranges_drop_while_view.cpp
 *
 *	@brief	ranges::drop_while_view のテスト
 */

#include <hamon/ranges/adaptors/drop_while_view.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/concepts.hpp>
#include <hamon/iterator.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace drop_while_view_test
{

struct LessThanFive
{
	HAMON_CXX11_CONSTEXPR bool operator()(int x) const HAMON_NOEXCEPT
	{
		return x < 5;
	}
};

struct NoDefaultFunc
{
	HAMON_CXX11_CONSTEXPR bool operator()(int x) const HAMON_NOEXCEPT
	{
		return x < 5;
	}

	NoDefaultFunc() = delete;
};
static_assert(!hamon::is_default_constructible<NoDefaultFunc>::value, "");

template <typename T>
struct MoveOnlyView : hamon::ranges::view_base
{
	MoveOnlyView(MoveOnlyView&&) = default;
	MoveOnlyView& operator=(MoveOnlyView&&) = default;

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
};
static_assert(hamon::ranges::view_t<MoveOnlyView<int>>::value, "");
static_assert(!hamon::copyable<MoveOnlyView<int>>, "");

template <typename T, typename Pred, typename = void>
struct CanInstantiateDropWhileView
	: hamon::false_type {};

template <typename T, typename Pred>
struct CanInstantiateDropWhileView<T, Pred, hamon::void_t<hamon::ranges::drop_while_view<T, Pred>>>
	: hamon::true_type {};

static_assert( CanInstantiateDropWhileView<test_input_view<int>, LessThanFive>::value, "");
static_assert(!CanInstantiateDropWhileView<test_input_range<int>, LessThanFive>::value, "");	// view<V>
static_assert(!CanInstantiateDropWhileView<test_output_view<int>, LessThanFive>::value, "");	// input_range<V>
static_assert(!CanInstantiateDropWhileView<test_input_view<int>, LessThanFive&>::value, "");	// is_object_v<Pred>
static_assert(!CanInstantiateDropWhileView<test_input_view<int*>, LessThanFive>::value, "");	// indirect_unary_predicate<const Pred, iterator_t<V>>

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View, typename Pred>
HAMON_CXX14_CONSTEXPR bool test00_impl()
{
	using T = int;
	using V = View<T>;
	using DWV = hamon::ranges::drop_while_view<V, Pred>;
	using I = hamon::ranges::iterator_t<DWV>;
	using S = hamon::ranges::sentinel_t<DWV>;

	static_assert(hamon::ranges::range_t<DWV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range<DWV> == hamon::ranges::borrowed_range<V>, "");
	static_assert(hamon::ranges::sized_range_t<DWV>::value == hamon::sized_sentinel_for<S, I>, "");
	static_assert(hamon::ranges::approximately_sized_range<DWV> == hamon::sized_sentinel_for<S, I>, "");
	static_assert(hamon::ranges::output_range_t<DWV, T>::value == hamon::ranges::output_range_t<V, T>::value, "");
	static_assert(hamon::ranges::input_range_t<DWV>::value == hamon::ranges::input_range_t<V>::value, "");
	static_assert(hamon::ranges::forward_range_t<DWV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range<DWV> == hamon::ranges::bidirectional_range<V>, "");
	static_assert(hamon::ranges::random_access_range_t<DWV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(hamon::ranges::contiguous_range<DWV> == hamon::ranges::contiguous_range<V>, "");
	static_assert(hamon::ranges::common_range<DWV> == hamon::ranges::common_range<V>, "");
	static_assert(hamon::ranges::viewable_range_t<DWV>::value == true, "");
	static_assert(hamon::ranges::view_t<DWV>::value == true, "");
	static_assert(hamon::ranges::constant_range<DWV> == false, "");

	static_assert(hamon::is_default_constructible<DWV>::value ==
		(hamon::is_default_constructible<V>::value && hamon::is_default_constructible<Pred>::value), "");
	static_assert(hamon::is_nothrow_default_constructible<DWV>::value ==
		(hamon::is_nothrow_default_constructible<V>::value && hamon::is_nothrow_default_constructible<Pred>::value), "");

	static_assert(!hamon::is_constructible<DWV, V>::value, "");
	static_assert(!hamon::is_constructible<DWV, Pred>::value, "");
	static_assert( hamon::is_constructible<DWV, V, Pred>::value, "");
	static_assert(!hamon::is_constructible<DWV, Pred, V>::value, "");
	static_assert(!hamon::is_constructible<DWV, V, Pred, Pred>::value, "");

	static_assert(has_base<DWV&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<DWV&&>::value, "");
	static_assert(has_base<DWV const&>::value == hamon::copy_constructible<V>, "");
	static_assert(has_base<DWV const&&>::value == hamon::copy_constructible<V>, "");

	static_assert(hamon::same_as<decltype(hamon::declval<DWV&&>().base()), V>, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible<V>)
	{
		static_assert(hamon::same_as<decltype(hamon::declval<DWV&>().base()), V>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<DWV const&>().base()), V>, "");
		static_assert(hamon::same_as<decltype(hamon::declval<DWV const&&>().base()), V>, "");
	}
#endif

	static_assert(hamon::same_as<decltype(hamon::declval<DWV const>().pred()), Pred const&>, "");

	static_assert( has_begin<DWV>::value, "");
	static_assert(!has_begin<DWV const>::value, "");
	static_assert(hamon::same_as<decltype(hamon::declval<DWV>().begin()), I>, "");

	static_assert( has_end<DWV>::value, "");
	static_assert(!has_end<DWV const>::value, "");
	static_assert(hamon::same_as<decltype(hamon::declval<DWV>().end()), S>, "");

	return true;
}

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test00()
{
	VERIFY(test00_impl<View, LessThanFive>());
	VERIFY(test00_impl<View, NoDefaultFunc>());
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_random_access_view<int>;
	using DWV = hamon::ranges::drop_while_view<V, LessThanFive>;

	static_assert( has_begin<DWV&>::value, "");
	static_assert( has_end<DWV&>::value, "");
	static_assert( has_empty<DWV&>::value, "");
	static_assert( has_cbegin<DWV&>::value, "");
	static_assert( has_cend<DWV&>::value, "");
	static_assert( has_operator_bool<DWV&>::value, "");
	static_assert(!has_data<DWV&>::value, "");
	static_assert( has_size<DWV&>::value, "");
	static_assert(!has_reserve_hint<DWV&>::value, "");
	static_assert( has_front<DWV&>::value, "");
	static_assert(!has_back<DWV&>::value, "");
	static_assert( has_subscript<DWV&>::value, "");
	static_assert( has_base<DWV&>::value, "");

	static_assert(!has_begin<DWV const&>::value, "");
	static_assert(!has_end<DWV const&>::value, "");
	static_assert(!has_empty<DWV const&>::value, "");
	static_assert(!has_cbegin<DWV const&>::value, "");
	static_assert(!has_cend<DWV const&>::value, "");
	static_assert(!has_operator_bool<DWV const&>::value, "");
	static_assert(!has_data<DWV const&>::value, "");
	static_assert(!has_size<DWV const&>::value, "");
	static_assert(!has_reserve_hint<DWV const&>::value, "");
	static_assert(!has_front<DWV const&>::value, "");
	static_assert(!has_back<DWV const&>::value, "");
	static_assert(!has_subscript<DWV const&>::value, "");
	static_assert( has_base<DWV const&>::value, "");

	DWV dwv{};

	VERIFY(dwv.begin() == dwv.end());
	VERIFY(dwv.begin() == dwv.base().begin());

	{
		auto& p = dwv.pred();
		static_assert(hamon::same_as<decltype(p), LessThanFive const&>, "");
	}
	{
		auto b = dwv.base();
		static_assert(hamon::same_as<decltype(b), V>, "");
		VERIFY(b.begin() == b.end());
	}
	{
		auto b = hamon::move(dwv).base();
		static_assert(hamon::same_as<decltype(b), V>, "");
		VERIFY(b.begin() == b.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V = test_input_view<int>;
	using DWV = hamon::ranges::drop_while_view<V, LessThanFive>;

	static_assert( has_begin<DWV&>::value, "");
	static_assert( has_end<DWV&>::value, "");
	static_assert(!has_empty<DWV&>::value, "");
	static_assert( has_cbegin<DWV&>::value, "");
	static_assert( has_cend<DWV&>::value, "");
	static_assert(!has_operator_bool<DWV&>::value, "");
	static_assert(!has_data<DWV&>::value, "");
	static_assert(!has_size<DWV&>::value, "");
	static_assert(!has_reserve_hint<DWV&>::value, "");
	static_assert(!has_front<DWV&>::value, "");
	static_assert(!has_back<DWV&>::value, "");
	static_assert(!has_subscript<DWV&>::value, "");
	static_assert( has_base<DWV&>::value, "");

	static_assert(!has_begin<DWV const&>::value, "");
	static_assert(!has_end<DWV const&>::value, "");
	static_assert(!has_empty<DWV const&>::value, "");
	static_assert(!has_cbegin<DWV const&>::value, "");
	static_assert(!has_cend<DWV const&>::value, "");
	static_assert(!has_operator_bool<DWV const&>::value, "");
	static_assert(!has_data<DWV const&>::value, "");
	static_assert(!has_size<DWV const&>::value, "");
	static_assert(!has_reserve_hint<DWV const&>::value, "");
	static_assert(!has_front<DWV const&>::value, "");
	static_assert(!has_back<DWV const&>::value, "");
	static_assert(!has_subscript<DWV const&>::value, "");
	static_assert( has_base<DWV const&>::value, "");

	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	V v(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_while_view dwv{v, LessThanFive{}};
	static_assert(hamon::same_as<decltype(dwv), DWV>, "");
#else
	DWV dwv{v, LessThanFive{}};
#endif

	{
		auto it = dwv.begin();
		VERIFY(it != dwv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != dwv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it != dwv.end());
		VERIFY(*it == 7);
		++it;
		VERIFY(it != dwv.end());
		VERIFY(*it == 8);
		++it;
		VERIFY(it == dwv.end());
	}
	{
		auto b = dwv.base();
		static_assert(hamon::same_as<decltype(b), V>, "");
		VERIFY(dwv.begin() != b.begin());
	}
	{
		auto b = hamon::move(dwv).base();
		static_assert(hamon::same_as<decltype(b), V>, "");
		VERIFY(dwv.begin() != b.begin());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using V = test_input_view<int>;
	using DWV = hamon::ranges::drop_while_view<V, LessThanFive>;

	static_assert( has_begin<DWV&>::value, "");
	static_assert( has_end<DWV&>::value, "");
	static_assert(!has_empty<DWV&>::value, "");
	static_assert( has_cbegin<DWV&>::value, "");
	static_assert( has_cend<DWV&>::value, "");
	static_assert(!has_operator_bool<DWV&>::value, "");
	static_assert(!has_data<DWV&>::value, "");
	static_assert(!has_size<DWV&>::value, "");
	static_assert(!has_reserve_hint<DWV&>::value, "");
	static_assert(!has_front<DWV&>::value, "");
	static_assert(!has_back<DWV&>::value, "");
	static_assert(!has_subscript<DWV&>::value, "");
	static_assert( has_base<DWV&>::value, "");

	static_assert(!has_begin<DWV const&>::value, "");
	static_assert(!has_end<DWV const&>::value, "");
	static_assert(!has_empty<DWV const&>::value, "");
	static_assert(!has_cbegin<DWV const&>::value, "");
	static_assert(!has_cend<DWV const&>::value, "");
	static_assert(!has_operator_bool<DWV const&>::value, "");
	static_assert(!has_data<DWV const&>::value, "");
	static_assert(!has_size<DWV const&>::value, "");
	static_assert(!has_reserve_hint<DWV const&>::value, "");
	static_assert(!has_front<DWV const&>::value, "");
	static_assert(!has_back<DWV const&>::value, "");
	static_assert(!has_subscript<DWV const&>::value, "");
	static_assert( has_base<DWV const&>::value, "");

	int a[] = {10, 1, 2};
	V v(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_while_view dwv{v, LessThanFive{}};
	static_assert(hamon::same_as<decltype(dwv), DWV>, "");
#else
	DWV dwv{v, LessThanFive{}};
#endif

	{
		auto it = dwv.begin();
		VERIFY(it != dwv.end());
		VERIFY(*it == 10);
		++it;
		VERIFY(it != dwv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != dwv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it == dwv.end());
	}
	{
		auto b = dwv.base();
		static_assert(hamon::same_as<decltype(b), V>, "");
		VERIFY(dwv.begin() == b.begin());
	}
	{
		auto b = hamon::move(dwv).base();
		static_assert(hamon::same_as<decltype(b), V>, "");
		VERIFY(dwv.begin() == b.begin());
	}

	return true;
}

HAMON_CXX17_CONSTEXPR bool test04()
{
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		auto dwv = a | hamon::views::drop_while([](int x) { return x % 2 != 0; });
		auto it = dwv.begin();
		VERIFY(it[0] == 4);
		VERIFY(it[1] == 1);
		VERIFY(it[2] == 5);
		VERIFY(it[3] == 9);
	}
	{
		auto dwv = hamon::views::iota(1, 10) | hamon::views::drop_while([](int x) { return x < 5; });
		auto it = dwv.begin();
		VERIFY(*it++ == 5);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 7);
		VERIFY(*it++ == 8);
		VERIFY(*it++ == 9);
		VERIFY(it == dwv.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, DropWhileViewTest)
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

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<MoveOnlyView>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(test04());

#if defined(HAMON_HAS_CXX14_GENERIC_LAMBDAS)
	// [range.drop.while.overview]/3
	// Example 1:
	{
		std::stringstream ss;
		constexpr auto source = hamon::string_view{"  \t   \t   \t   hello there"};
		auto is_invisible = [](const auto x) { return x == ' ' || x == '\t'; };
		auto skip_ws = hamon::views::drop_while(source, is_invisible);
		for (auto c : skip_ws)
		{
			ss << c;                                    // prints hello there with no leading space
		}
		EXPECT_EQ("hello there", ss.str());
	}
#endif
}

}	// namespace drop_while_view_test
}	// namespace hamon_ranges_test
