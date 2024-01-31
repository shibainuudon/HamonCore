/**
 *	@file	unit_test_ranges_lazy_split_view_inner_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const inner-iterator& x, const inner-iterator& y)
 *	  requires forward_range<Base>;
 *
 *	friend constexpr bool operator==(const inner-iterator& x, default_sentinel_t);
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace inner_iterator_compare_test
{

template <typename T, typename U, typename = void>
struct has_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_not_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_not_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
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

	static_assert( has_equal<I const&, I const&>::value, "");
	static_assert( has_equal<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_equal<hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_not_equal<I const&, I const&>::value, "");
	static_assert( has_not_equal<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_not_equal<hamon::default_sentinel_t, I const&>::value, "");

	int a1[] = {1, 2, 0, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	{
		auto inner = *i;
		auto ii1 = inner.begin();
		auto ii2 = inner.begin();
		auto ii3 = inner.begin();
		auto ii4 = inner.begin();
		auto ii5 = inner.begin();
		auto ii6 = inner.begin();

		++ii3;
		++ii4;
		++ii5;
		++ii5;
		++ii6;
		++ii6;

		VERIFY( (ii1 == ii1));
		VERIFY( (ii1 == ii2));
		VERIFY(!(ii1 == ii3));
		VERIFY(!(ii1 == ii4));
		VERIFY(!(ii1 == ii5));
		VERIFY(!(ii1 == ii6));

		VERIFY(!(ii3 == ii1));
		VERIFY(!(ii3 == ii2));
		VERIFY( (ii3 == ii3));
		VERIFY( (ii3 == ii4));
		VERIFY(!(ii3 == ii5));
		VERIFY(!(ii3 == ii6));

		VERIFY(!(ii5 == ii1));
		VERIFY(!(ii5 == ii2));
		VERIFY(!(ii5 == ii3));
		VERIFY(!(ii5 == ii4));
		VERIFY( (ii5 == ii5));
		VERIFY( (ii5 == ii6));

		VERIFY(!(ii1 != ii1));
		VERIFY(!(ii1 != ii2));
		VERIFY( (ii1 != ii3));
		VERIFY( (ii1 != ii4));
		VERIFY( (ii1 != ii5));
		VERIFY( (ii1 != ii6));

		VERIFY( (ii3 != ii1));
		VERIFY( (ii3 != ii2));
		VERIFY(!(ii3 != ii3));
		VERIFY(!(ii3 != ii4));
		VERIFY( (ii3 != ii5));
		VERIFY( (ii3 != ii6));

		VERIFY( (ii5 != ii1));
		VERIFY( (ii5 != ii2));
		VERIFY( (ii5 != ii3));
		VERIFY( (ii5 != ii4));
		VERIFY(!(ii5 != ii5));
		VERIFY(!(ii5 != ii6));

		VERIFY(!(ii1 == hamon::default_sentinel_t{}));
		VERIFY(!(ii3 == hamon::default_sentinel_t{}));
		VERIFY( (ii5 == hamon::default_sentinel_t{}));

		VERIFY( (ii1 != hamon::default_sentinel_t{}));
		VERIFY( (ii3 != hamon::default_sentinel_t{}));
		VERIFY(!(ii5 != hamon::default_sentinel_t{}));

		VERIFY(!(hamon::default_sentinel_t{} == ii1));
		VERIFY(!(hamon::default_sentinel_t{} == ii3));
		VERIFY( (hamon::default_sentinel_t{} == ii5));

		VERIFY( (hamon::default_sentinel_t{} != ii1));
		VERIFY( (hamon::default_sentinel_t{} != ii3));
		VERIFY(!(hamon::default_sentinel_t{} != ii5));
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

	static_assert(!has_equal<I const&, I const&>::value, "");
	static_assert( has_equal<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_equal<hamon::default_sentinel_t, I const&>::value, "");
	static_assert(!has_not_equal<I const&, I const&>::value, "");
	static_assert( has_not_equal<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_not_equal<hamon::default_sentinel_t, I const&>::value, "");

	int a1[] = {1, 2, 3, 0, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	{
		auto inner = *i;
		auto ii = inner.begin();
		VERIFY(ii != inner.end());
		VERIFY(!(ii == hamon::default_sentinel_t{}));
		VERIFY( (ii != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == ii));
		VERIFY( (hamon::default_sentinel_t{} != ii));
		++ii;
		VERIFY(!(ii == hamon::default_sentinel_t{}));
		VERIFY( (ii != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == ii));
		VERIFY( (hamon::default_sentinel_t{} != ii));
		++ii;
		VERIFY(!(ii == hamon::default_sentinel_t{}));
		VERIFY( (ii != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == ii));
		VERIFY( (hamon::default_sentinel_t{} != ii));
		++ii;
		VERIFY( (ii == hamon::default_sentinel_t{}));
		VERIFY(!(ii != hamon::default_sentinel_t{}));
		VERIFY( (hamon::default_sentinel_t{} == ii));
		VERIFY(!(hamon::default_sentinel_t{} != ii));
		VERIFY(ii == inner.end());
	}
	++i;
	{
		auto inner = *i;
		auto ii = inner.begin();
		VERIFY(ii != inner.end());
		VERIFY(!(ii == hamon::default_sentinel_t{}));
		VERIFY( (ii != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == ii));
		VERIFY( (hamon::default_sentinel_t{} != ii));
		++ii;
		VERIFY(!(ii == hamon::default_sentinel_t{}));
		VERIFY( (ii != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == ii));
		VERIFY( (hamon::default_sentinel_t{} != ii));
		++ii;
		VERIFY( (ii == hamon::default_sentinel_t{}));
		VERIFY(!(ii != hamon::default_sentinel_t{}));
		VERIFY( (hamon::default_sentinel_t{} == ii));
		VERIFY(!(hamon::default_sentinel_t{} != ii));
		VERIFY(ii == inner.end());
	}
	++i;
	VERIFY(i == rv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewInnerIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace inner_iterator_compare_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
