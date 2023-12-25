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
static_assert(!hamon::copyable_t<MoveOnlyView<int>>::value, "");

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class View, typename Pred>
HAMON_CXX14_CONSTEXPR bool test00_impl()
{
	using T = int;
	using V = View<T>;
	using RV = hamon::ranges::drop_while_view<V, Pred>;
	using I = hamon::ranges::iterator_t<RV>;
	using S = hamon::ranges::sentinel_t<RV>;

	static_assert(hamon::ranges::range_t<RV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range_t<RV>::value == hamon::ranges::borrowed_range_t<V>::value, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == hamon::sized_sentinel_for_t<S, I>::value, "");
	static_assert(hamon::ranges::output_range_t<RV, T>::value == hamon::ranges::output_range_t<V, T>::value, "");
	static_assert(hamon::ranges::input_range_t<RV>::value == hamon::ranges::input_range_t<V>::value, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value == hamon::ranges::forward_range_t<V>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value == hamon::ranges::bidirectional_range_t<V>::value, "");
	static_assert(hamon::ranges::random_access_range_t<RV>::value == hamon::ranges::random_access_range_t<V>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<RV>::value == hamon::ranges::contiguous_range_t<V>::value, "");
	static_assert(hamon::ranges::common_range_t<RV>::value == hamon::ranges::common_range_t<V>::value, "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::view_t<RV>::value == true, "");

	static_assert(hamon::is_default_constructible<RV>::value ==
		(hamon::is_default_constructible<V>::value && hamon::is_default_constructible<Pred>::value), "");
	static_assert(hamon::is_nothrow_default_constructible<RV>::value ==
		(hamon::is_nothrow_default_constructible<V>::value && hamon::is_nothrow_default_constructible<Pred>::value), "");

	static_assert(!hamon::is_constructible<RV, V>::value, "");
	static_assert(!hamon::is_constructible<RV, Pred>::value, "");
	static_assert( hamon::is_constructible<RV, V, Pred>::value, "");
	static_assert(!hamon::is_constructible<RV, Pred, V>::value, "");
	static_assert(!hamon::is_constructible<RV, V, Pred, Pred>::value, "");

	static_assert(has_base<RV&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV&&>::value, "");
	static_assert(has_base<RV const&>::value == hamon::copy_constructible_t<V>::value, "");
	static_assert(has_base<RV const&&>::value == hamon::copy_constructible_t<V>::value, "");

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV&&>().base()), V>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::copy_constructible_t<V>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&>().base()), V>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<RV const&&>().base()), V>::value, "");
	}
#endif

	static_assert(hamon::same_as_t<decltype(hamon::declval<RV const>().pred()), Pred const&>::value, "");

	static_assert( has_begin<RV>::value, "");
	static_assert(!has_begin<RV const>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV>().begin()), I>::value, "");

	static_assert( has_end<RV>::value, "");
	static_assert(!has_end<RV const>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<RV>().end()), S>::value, "");

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
	hamon::ranges::drop_while_view<V, LessThanFive> rv{};

	VERIFY(rv.begin() == rv.end());
	VERIFY(rv.begin() == rv.base().begin());

	{
		auto& p = rv.pred();
		static_assert(hamon::same_as_t<decltype(p), LessThanFive const&>::value, "");
	}
	{
		auto b = rv.base();
		static_assert(hamon::same_as_t<decltype(b), V>::value, "");
		VERIFY(b.begin() == b.end());
	}
	{
		auto b = hamon::move(rv).base();
		static_assert(hamon::same_as_t<decltype(b), V>::value, "");
		VERIFY(b.begin() == b.end());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8};

	using V = test_input_view<int>;
	V v(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_while_view rv{v, LessThanFive{}};
	static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::drop_while_view<V, LessThanFive>>::value, "");
#else
	hamon::ranges::drop_while_view<V, LessThanFive> rv{v, LessThanFive{}};
#endif

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 5);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 6);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 7);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 8);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto b = rv.base();
		static_assert(hamon::same_as_t<decltype(b), V>::value, "");
		VERIFY(rv.begin() != b.begin());
	}
	{
		auto b = hamon::move(rv).base();
		static_assert(hamon::same_as_t<decltype(b), V>::value, "");
		VERIFY(rv.begin() != b.begin());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[] = {10, 1, 2};

	using V = test_input_view<int>;
	V v(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::drop_while_view rv{v, LessThanFive{}};
	static_assert(hamon::same_as_t<decltype(rv), hamon::ranges::drop_while_view<V, LessThanFive>>::value, "");
#else
	hamon::ranges::drop_while_view<V, LessThanFive> rv{v, LessThanFive{}};
#endif

	{
		auto it = rv.begin();
		VERIFY(it != rv.end());
		VERIFY(*it == 10);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != rv.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it == rv.end());
	}
	{
		auto b = rv.base();
		static_assert(hamon::same_as_t<decltype(b), V>::value, "");
		VERIFY(rv.begin() == b.begin());
	}
	{
		auto b = hamon::move(rv).base();
		static_assert(hamon::same_as_t<decltype(b), V>::value, "");
		VERIFY(rv.begin() == b.begin());
	}

	return true;
}

HAMON_CXX17_CONSTEXPR bool test04()
{
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		auto rv = a | hamon::views::drop_while([](int x) { return x % 2 != 0; });
		auto it = rv.begin();
		VERIFY(it[0] == 4);
		VERIFY(it[1] == 1);
		VERIFY(it[2] == 5);
		VERIFY(it[3] == 9);
	}
	{
		auto rv = hamon::views::iota(1, 10) | hamon::views::drop_while([](int x) { return x < 5; });
		auto it = rv.begin();
		VERIFY(*it++ == 5);
		VERIFY(*it++ == 6);
		VERIFY(*it++ == 7);
		VERIFY(*it++ == 8);
		VERIFY(*it++ == 9);
		VERIFY(it == rv.end());
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
