/**
 *	@file	unit_test_ranges_lazy_split_view_outer_iterator_post_increment.cpp
 *
 *	@brief	後置インクリメントのテスト
 *
 *	constexpr decltype(auto) operator++(int);
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
namespace outer_iterator_post_increment_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;

	static_assert(hamon::is_same<decltype(hamon::declval<I>()++), I>::value, "");

	int a1[] = {3, 1, 2, 4, 5, 1, 2, 6};
	int a2[] = {1, 2};

	V v(a1);
	P p(a2);
	RV rv(v, p);

	auto i = rv.begin();
	VERIFY(*((*i).begin()) == 3);
	auto t1 = i++;
	VERIFY(*((*i).begin()) == 4);
	VERIFY(*((*t1).begin()) == 3);
	auto t2 = i++;
	VERIFY(*((*i).begin()) == 6);
	VERIFY(*((*t2).begin()) == 4);
	auto t3 = i++;
	VERIFY(i == rv.end());
	VERIFY(*((*t3).begin()) == 6);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_input_view<int>;
	using P = test_forward_static_sized_view<int, 1>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;

	static_assert(hamon::is_same<decltype(hamon::declval<I>()++), void>::value, "");

	int a1[] = {3, 1, 4, 5, 1, 6};
	int a2[] = {1};

	V v(a1);
	P p(a2);
	RV rv(v, p);

	auto i = rv.begin();
	VERIFY(*((*i).begin()) == 3);
	i++;
	VERIFY(*((*i).begin()) == 4);
	i++;
	VERIFY(*((*i).begin()) == 6);
	i++;
	VERIFY(i == rv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewOuterIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace outer_iterator_post_increment_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
