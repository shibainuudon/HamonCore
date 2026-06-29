/**
 *	@file	unit_test_ranges_concat_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y)
 *		requires (equality_comparable<iterator_t<maybe-const<Const, Views>>> && ...);
 *	friend constexpr bool operator==(const iterator& it, default_sentinel_t);
 *	friend constexpr bool operator<(const iterator& x, const iterator& y)
 *		requires all-random-access<Const, Views...>;
 *	friend constexpr bool operator>(const iterator& x, const iterator& y)
 *		requires all-random-access<Const, Views...>;
 *	friend constexpr bool operator<=(const iterator& x, const iterator& y)
 *		requires all-random-access<Const, Views...>;
 *	friend constexpr bool operator>=(const iterator& x, const iterator& y)
 *		requires all-random-access<Const, Views...>;
 *	friend constexpr auto operator<=>(const iterator& x, const iterator& y)
 *		requires (all-random-access<Const, Views...> &&
 *			(three_way_comparable<iterator_t<maybe-const<Const, Views>>> && ...));
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/compare.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace iterator_compare_test
{

template <typename T>
struct NonComparableIterator
{
	T*	m_ptr;

	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;

	NonComparableIterator& operator++();
	NonComparableIterator  operator++(int);
	T&                     operator*() const;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V1 = test_view<int, int*>;
		using V2 = test_view<int, int*>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_eq  <I const&>::value, "");
		static_assert( has_neq <I const&>::value, "");
		static_assert( has_lt  <I const&>::value, "");
		static_assert( has_lteq<I const&>::value, "");
		static_assert( has_gt  <I const&>::value, "");
		static_assert( has_gteq<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert( has_compare_three_way<I const&>::value, "");
#endif
		static_assert( has_eq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq<hamon::default_sentinel_t, I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_eq  <I const&>::value, "");
		static_assert( has_neq <I const&>::value, "");
		static_assert( has_lt  <I const&>::value, "");
		static_assert( has_lteq<I const&>::value, "");
		static_assert( has_gt  <I const&>::value, "");
		static_assert( has_gteq<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&>::value, "");
#endif
		static_assert( has_eq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq<hamon::default_sentinel_t, I const&>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_bidirectional_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_eq  <I const&>::value, "");
		static_assert( has_neq <I const&>::value, "");
		static_assert(!has_lt  <I const&>::value, "");
		static_assert(!has_lteq<I const&>::value, "");
		static_assert(!has_gt  <I const&>::value, "");
		static_assert(!has_gteq<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&>::value, "");
#endif
		static_assert( has_eq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq<hamon::default_sentinel_t, I const&>::value, "");
	}
	{
		using V1 = test_view<int, NonComparableIterator<int>>;
		using V2 = test_view<int, int*>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_eq  <I const&>::value, "");
		static_assert(!has_neq <I const&>::value, "");
		static_assert(!has_lt  <I const&>::value, "");
		static_assert(!has_lteq<I const&>::value, "");
		static_assert(!has_gt  <I const&>::value, "");
		static_assert(!has_gteq<I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!has_compare_three_way<I const&>::value, "");
#endif
		static_assert( has_eq <I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_neq<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_eq <hamon::default_sentinel_t, I const&>::value, "");
		static_assert( has_neq<hamon::default_sentinel_t, I const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a1[] = {1,2};
	int a2[] = {3};

	auto cv = hamon::views::concat(a1, a2);

	auto it1 = cv.begin();
	auto it2 = cv.begin();
	auto it3 = cv.begin();
	++it2;
	++it3;
	++it3;

	VERIFY(!(it2 == it1));
	VERIFY( (it2 == it2));
	VERIFY(!(it2 == it3));

	VERIFY( (it2 != it1));
	VERIFY(!(it2 != it2));
	VERIFY( (it2 != it3));

	VERIFY(!(it2 <  it1));
	VERIFY(!(it2 <  it2));
	VERIFY( (it2 <  it3));

	VERIFY(!(it2 <= it1));
	VERIFY( (it2 <= it2));
	VERIFY( (it2 <= it3));

	VERIFY( (it2 >  it1));
	VERIFY(!(it2 >  it2));
	VERIFY(!(it2 >  it3));

	VERIFY( (it2 >= it1));
	VERIFY( (it2 >= it2));
	VERIFY(!(it2 >= it3));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_gt(it2 <=> it1));
	VERIFY(hamon::is_eq(it2 <=> it2));
	VERIFY(hamon::is_lt(it2 <=> it3));
#endif

	VERIFY(!(it3 == hamon::default_sentinel));
	VERIFY( (it3 != hamon::default_sentinel));
	VERIFY(!(hamon::default_sentinel == it3));
	VERIFY( (hamon::default_sentinel != it3));
	++it3;
	VERIFY( (it3 == hamon::default_sentinel));
	VERIFY(!(it3 != hamon::default_sentinel));
	VERIFY( (hamon::default_sentinel == it3));
	VERIFY(!(hamon::default_sentinel != it3));

	return true;
}


HAMON_CXX14_CONSTEXPR bool test02()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<int>;
	using CV = hamon::ranges::concat_view<V1, V2>;

	int a1[] = {1,2};
	int a2[] = {3,4,5};
	V1 v1(a1);
	V2 v2(a2);

	CV cv(v1, v2);

	auto it1 = cv.begin();
	auto it2 = cv.begin();
	auto it3 = cv.begin();
	++it2;
	++it3;
	++it3;

	VERIFY(!(it2 == it1));
	VERIFY( (it2 == it2));
	VERIFY(!(it2 == it3));

	VERIFY( (it2 != it1));
	VERIFY(!(it2 != it2));
	VERIFY( (it2 != it3));

	VERIFY(!(it2 <  it1));
	VERIFY(!(it2 <  it2));
	VERIFY( (it2 <  it3));

	VERIFY(!(it2 <= it1));
	VERIFY( (it2 <= it2));
	VERIFY( (it2 <= it3));

	VERIFY( (it2 >  it1));
	VERIFY(!(it2 >  it2));
	VERIFY(!(it2 >  it3));

	VERIFY( (it2 >= it1));
	VERIFY( (it2 >= it2));
	VERIFY(!(it2 >= it3));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_compare_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
