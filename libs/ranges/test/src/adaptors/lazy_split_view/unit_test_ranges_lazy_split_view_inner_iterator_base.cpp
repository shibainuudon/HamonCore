/**
 *	@file	unit_test_ranges_lazy_split_view_inner_iterator_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr const iterator_t<Base>& base() const & noexcept;
 *	constexpr iterator_t<Base> base() && requires forward_range<V>;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace inner_iterator_base_test
{

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I&&>::value, "");
	static_assert( has_base<I const&>::value, "");
	static_assert( has_base<I const&&>::value, "");

	static_assert(hamon::is_same<BaseIter const&, decltype(hamon::declval<I&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter,        decltype(hamon::declval<I&&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter const&, decltype(hamon::declval<I const&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter const&, decltype(hamon::declval<I const&&>().base())>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	auto inner = *i;
	auto ii = inner.begin();
	{
		auto&& b = ii.base();
		static_assert(hamon::is_same<decltype(b), BaseIter const&>::value, "");
		VERIFY(b == v.begin());
	}
	{
		auto&& b = hamon::move(ii).base();
		static_assert(hamon::is_same<decltype(b), BaseIter&&>::value, "");
		VERIFY(b == v.begin());
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;
	using P = test_forward_static_sized_view<int, 1>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter = hamon::ranges::iterator_t<RV>;
	using InnerRng = decltype(*hamon::declval<OuterIter&>());
	using I = decltype(hamon::declval<InnerRng&>().begin());
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I&&>::value, "");
	static_assert( has_base<I const&>::value, "");
	static_assert( has_base<I const&&>::value, "");

	static_assert(hamon::is_same<BaseIter const&, decltype(hamon::declval<I&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter const&, decltype(hamon::declval<I&&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter const&, decltype(hamon::declval<I const&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter const&, decltype(hamon::declval<I const&&>().base())>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	auto inner = *i;
	auto ii = inner.begin();
	{
		auto&& b = ii.base();
		static_assert(hamon::is_same<decltype(b), BaseIter const&>::value, "");
		VERIFY(b == v.begin());
	}
	{
		auto&& b = hamon::move(ii).base();
		static_assert(hamon::is_same<decltype(b), BaseIter const&>::value, "");
		VERIFY(b == v.begin());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewInnerIteratorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace inner_iterator_base_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
