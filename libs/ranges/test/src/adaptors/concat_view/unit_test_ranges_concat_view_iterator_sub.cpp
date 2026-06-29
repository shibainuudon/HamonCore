/**
 *	@file	unit_test_ranges_concat_view_iterator_sub.cpp
 *
 *	@brief	operator-() のテスト
 *
 *	friend constexpr iterator operator-(const iterator& it, difference_type n)
 *		requires concat-is-random-access<Const, Views...>;
 *	friend constexpr difference_type operator-(const iterator& x, const iterator& y)
 *		requires concat-is-random-access<Const, Views...>;
 *	friend constexpr difference_type operator-(const iterator& x, default_sentinel_t)
 *		requires see below;
 *	friend constexpr difference_type operator-(default_sentinel_t, const iterator& x)
 *		requires see below;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace iterator_sub_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V1 = test_random_access_common_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert( has_minus<I const&, int>::value, "");
		static_assert(!has_minus<int, I const&>::value, "");
		static_assert( has_minus<I const&, I const&>::value, "");
		static_assert( has_minus<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_minus<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<int>()), I>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V1 = test_random_access_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_minus<I const&, int>::value, "");
		static_assert(!has_minus<int, I const&>::value, "");
		static_assert(!has_minus<I const&, I const&>::value, "");
		static_assert( has_minus<I const&, hamon::default_sentinel_t>::value, "");
		static_assert( has_minus<hamon::default_sentinel_t, I const&>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<I const&>() - hamon::declval<hamon::default_sentinel_t>()), hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<I const&>()), hamon::ptrdiff_t>::value, "");
	}
	{
		using V1 = test_bidirectional_common_view<int>;
		using V2 = test_bidirectional_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_minus<I const&, int>::value, "");
		static_assert(!has_minus<int, I const&>::value, "");
		static_assert(!has_minus<I const&, I const&>::value, "");
		static_assert(!has_minus<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_minus<hamon::default_sentinel_t, I const&>::value, "");
	}
	{
		using V1 = test_input_sized_view<int>;
		using V2 = test_input_sized_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;
		using I = hamon::ranges::iterator_t<CV>;
		static_assert(!has_minus<I const&, int>::value, "");
		static_assert(!has_minus<int, I const&>::value, "");
		static_assert(!has_minus<I const&, I const&>::value, "");
		static_assert(!has_minus<I const&, hamon::default_sentinel_t>::value, "");
		static_assert(!has_minus<hamon::default_sentinel_t, I const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V1 = test_random_access_common_view<int>;
		using V2 = test_random_access_view<int>;
		using CV = hamon::ranges::concat_view<V1, V2>;

		int a1[] = {1,2,3};
		int a2[] = {4,5};
		V1 v1(a1);
		V2 v2(a2);

		CV cv(v1, v2);

		auto it = cv.begin();
		++it;
		++it;
		++it;
		++it;
		VERIFY(*it == 5);

		auto it1 = it - 1;
		auto it2 = it - 3;
		auto it3 = it - 4;
		VERIFY(*it1 == 4);
		VERIFY(*it2 == 2);
		VERIFY(*it3 == 1);

		auto d1 = it1 - it2;
		auto d2 = it2 - it1;
		VERIFY(d1 == 2);
		VERIFY(d2 == -2);

		auto d3 = it1 - hamon::default_sentinel;
		auto d4 = it2 - hamon::default_sentinel;
		VERIFY(d3 == -2);
		VERIFY(d4 == -4);

		auto d5 = hamon::default_sentinel - it1;
		auto d6 = hamon::default_sentinel - it2;
		VERIFY(d5 == 2);
		VERIFY(d6 == 4);

		auto d7 = it2 - it3;
		auto d8 = it3 - it2;
		VERIFY(d7 == 1);
		VERIFY(d8 == -1);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a1[] = {1,2};
	int a2[] = {3};
	int a3[] = {4};
	int a4[] = {5,6,7};
	int a5[] = {8,9};

	auto cv = hamon::views::concat(a1, a2, a3, a4, a5);
	auto it1 = cv.begin() + 0;
	auto it2 = cv.begin() + 1;
	auto it3 = cv.begin() + 2;
	auto it4 = cv.begin() + 3;
	auto it5 = cv.begin() + 4;
	auto it6 = cv.begin() + 5;
	auto it7 = cv.begin() + 6;
	auto it8 = cv.begin() + 7;
	auto it9 = cv.begin() + 8;

	VERIFY(*it1 == 1);
	VERIFY(*it2 == 2);
	VERIFY(*it3 == 3);
	VERIFY(*it4 == 4);
	VERIFY(*it5 == 5);
	VERIFY(*it6 == 6);
	VERIFY(*it7 == 7);
	VERIFY(*it8 == 8);
	VERIFY(*it9 == 9);

	VERIFY(it1 - it1 == 0);
	VERIFY(it2 - it1 == 1);
	VERIFY(it3 - it1 == 2);
	VERIFY(it4 - it1 == 3);
	VERIFY(it5 - it1 == 4);
	VERIFY(it6 - it1 == 5);
	VERIFY(it7 - it1 == 6);
	VERIFY(it8 - it1 == 7);
	VERIFY(it9 - it1 == 8);

	VERIFY(it1 - it1 == -0);
	VERIFY(it1 - it2 == -1);
	VERIFY(it1 - it3 == -2);
	VERIFY(it1 - it4 == -3);
	VERIFY(it1 - it5 == -4);
	VERIFY(it1 - it6 == -5);
	VERIFY(it1 - it7 == -6);
	VERIFY(it1 - it8 == -7);
	VERIFY(it1 - it9 == -8);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewIteratorSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_sub_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
