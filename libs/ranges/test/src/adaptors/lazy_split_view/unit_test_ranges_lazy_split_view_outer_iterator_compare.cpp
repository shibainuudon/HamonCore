/**
 *	@file	unit_test_ranges_lazy_split_view_outer_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const outer-iterator& x, const outer-iterator& y)
 *	  requires forward_range<Base>;
 *
 *	friend constexpr bool operator==(const outer-iterator& x, default_sentinel_t);
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace outer_iterator_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;

	static_assert( has_eq<I const&, I const&>::value, "");
	static_assert( has_eq<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_eq<hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_neq<I const&, I const&>::value, "");
	static_assert( has_neq<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_neq<hamon::default_sentinel_t, I const&>::value, "");

	static_assert(!has_lt<I>::value, "");
	static_assert(!has_lteq<I>::value, "");
	static_assert(!has_gt<I>::value, "");
	static_assert(!has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<I>::value, "");
#endif

	{
		int a1[] = {3, 1, 2, 4};
		int a2[] = {1, 2};

		V v(a1);
		P p(a2);
		RV rv(v, p);

		auto i1 = rv.begin();
		auto i2 = rv.begin();
		auto i3 = rv.begin();
		auto i4 = rv.begin();
		auto i5 = rv.begin();
		auto i6 = rv.begin();

		++i3;
		++i4;
		++i5;
		++i5;
		++i6;
		++i6;

		VERIFY( (i1 == i1));
		VERIFY( (i1 == i2));
		VERIFY(!(i1 == i3));
		VERIFY(!(i1 == i4));
		VERIFY(!(i1 == i5));
		VERIFY(!(i1 == i6));

		VERIFY(!(i3 == i1));
		VERIFY(!(i3 == i2));
		VERIFY( (i3 == i3));
		VERIFY( (i3 == i4));
		VERIFY(!(i3 == i5));
		VERIFY(!(i3 == i6));

		VERIFY(!(i5 == i1));
		VERIFY(!(i5 == i2));
		VERIFY(!(i5 == i3));
		VERIFY(!(i5 == i4));
		VERIFY( (i5 == i5));
		VERIFY( (i5 == i6));

		VERIFY(!(i1 != i1));
		VERIFY(!(i1 != i2));
		VERIFY( (i1 != i3));
		VERIFY( (i1 != i4));
		VERIFY( (i1 != i5));
		VERIFY( (i1 != i6));

		VERIFY( (i3 != i1));
		VERIFY( (i3 != i2));
		VERIFY(!(i3 != i3));
		VERIFY(!(i3 != i4));
		VERIFY( (i3 != i5));
		VERIFY( (i3 != i6));

		VERIFY( (i5 != i1));
		VERIFY( (i5 != i2));
		VERIFY( (i5 != i3));
		VERIFY( (i5 != i4));
		VERIFY(!(i5 != i5));
		VERIFY(!(i5 != i6));

		VERIFY(!(i1 == hamon::default_sentinel_t{}));
		VERIFY(!(i3 == hamon::default_sentinel_t{}));
		VERIFY( (i5 == hamon::default_sentinel_t{}));

		VERIFY( (i1 != hamon::default_sentinel_t{}));
		VERIFY( (i3 != hamon::default_sentinel_t{}));
		VERIFY(!(i5 != hamon::default_sentinel_t{}));

		VERIFY(!(hamon::default_sentinel_t{} == i1));
		VERIFY(!(hamon::default_sentinel_t{} == i3));
		VERIFY( (hamon::default_sentinel_t{} == i5));

		VERIFY( (hamon::default_sentinel_t{} != i1));
		VERIFY( (hamon::default_sentinel_t{} != i3));
		VERIFY(!(hamon::default_sentinel_t{} != i5));
	}

	{
		int a1[] = {3, 1, 2};
		int a2[] = {1, 2};

		V v(a1);
		P p(a2);
		RV rv(v, p);

		auto i1 = rv.begin();
		auto i2 = rv.begin();
		auto i3 = rv.begin();
		auto i4 = rv.begin();
		auto i5 = rv.begin();
		auto i6 = rv.begin();

		++i3;
		++i4;
		++i5;
		++i5;
		++i6;
		++i6;

		VERIFY( (i1 == i1));
		VERIFY( (i1 == i2));
		VERIFY(!(i1 == i3));
		VERIFY(!(i1 == i4));
		VERIFY(!(i1 == i5));
		VERIFY(!(i1 == i6));

		VERIFY(!(i3 == i1));
		VERIFY(!(i3 == i2));
		VERIFY( (i3 == i3));
		VERIFY( (i3 == i4));
		VERIFY(!(i3 == i5));
		VERIFY(!(i3 == i6));

		VERIFY(!(i5 == i1));
		VERIFY(!(i5 == i2));
		VERIFY(!(i5 == i3));
		VERIFY(!(i5 == i4));
		VERIFY( (i5 == i5));
		VERIFY( (i5 == i6));

		VERIFY(!(i1 != i1));
		VERIFY(!(i1 != i2));
		VERIFY( (i1 != i3));
		VERIFY( (i1 != i4));
		VERIFY( (i1 != i5));
		VERIFY( (i1 != i6));

		VERIFY( (i3 != i1));
		VERIFY( (i3 != i2));
		VERIFY(!(i3 != i3));
		VERIFY(!(i3 != i4));
		VERIFY( (i3 != i5));
		VERIFY( (i3 != i6));

		VERIFY( (i5 != i1));
		VERIFY( (i5 != i2));
		VERIFY( (i5 != i3));
		VERIFY( (i5 != i4));
		VERIFY(!(i5 != i5));
		VERIFY(!(i5 != i6));

		VERIFY(!(i1 == hamon::default_sentinel_t{}));
		VERIFY(!(i3 == hamon::default_sentinel_t{}));
		VERIFY( (i5 == hamon::default_sentinel_t{}));

		VERIFY( (i1 != hamon::default_sentinel_t{}));
		VERIFY( (i3 != hamon::default_sentinel_t{}));
		VERIFY(!(i5 != hamon::default_sentinel_t{}));

		VERIFY(!(hamon::default_sentinel_t{} == i1));
		VERIFY(!(hamon::default_sentinel_t{} == i3));
		VERIFY( (hamon::default_sentinel_t{} == i5));

		VERIFY( (hamon::default_sentinel_t{} != i1));
		VERIFY( (hamon::default_sentinel_t{} != i3));
		VERIFY(!(hamon::default_sentinel_t{} != i5));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;
	using P = test_forward_static_sized_view<int, 1>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;

	static_assert(!has_eq<I const&, I const&>::value, "");
	static_assert( has_eq<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_eq<hamon::default_sentinel_t, I const&>::value, "");
	static_assert(!has_neq<I const&, I const&>::value, "");
	static_assert( has_neq<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_neq<hamon::default_sentinel_t, I const&>::value, "");

	static_assert(!has_lt<I>::value, "");
	static_assert(!has_lteq<I>::value, "");
	static_assert(!has_gt<I>::value, "");
	static_assert(!has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<I>::value, "");
#endif

	{
		int a1[] = {3, 1, 4, 1, 5};
		int a2[] = {1};

		V v(a1);
		P p(a2);
		RV rv(v, p);

		auto i = rv.begin();

		VERIFY(!(i == hamon::default_sentinel_t{}));
		VERIFY( (i != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == i));
		VERIFY( (hamon::default_sentinel_t{} != i));
		++i;
		VERIFY(!(i == hamon::default_sentinel_t{}));
		VERIFY( (i != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == i));
		VERIFY( (hamon::default_sentinel_t{} != i));
		++i;
		VERIFY(!(i == hamon::default_sentinel_t{}));
		VERIFY( (i != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == i));
		VERIFY( (hamon::default_sentinel_t{} != i));
		++i;
		VERIFY( (i == hamon::default_sentinel_t{}));
		VERIFY(!(i != hamon::default_sentinel_t{}));
		VERIFY( (hamon::default_sentinel_t{} == i));
		VERIFY(!(hamon::default_sentinel_t{} != i));
	}
	{
		int a1[] = {3, 1, 4, 1};
		int a2[] = {1};

		V v(a1);
		P p(a2);
		RV rv(v, p);

		auto i = rv.begin();

		VERIFY(!(i == hamon::default_sentinel_t{}));
		VERIFY( (i != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == i));
		VERIFY( (hamon::default_sentinel_t{} != i));
		++i;
		VERIFY(!(i == hamon::default_sentinel_t{}));
		VERIFY( (i != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == i));
		VERIFY( (hamon::default_sentinel_t{} != i));
		++i;
		VERIFY(!(i == hamon::default_sentinel_t{}));
		VERIFY( (i != hamon::default_sentinel_t{}));
		VERIFY(!(hamon::default_sentinel_t{} == i));
		VERIFY( (hamon::default_sentinel_t{} != i));
		++i;
		VERIFY( (i == hamon::default_sentinel_t{}));
		VERIFY(!(i != hamon::default_sentinel_t{}));
		VERIFY( (hamon::default_sentinel_t{} == i));
		VERIFY(!(hamon::default_sentinel_t{} != i));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewOuterIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace outer_iterator_compare_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
