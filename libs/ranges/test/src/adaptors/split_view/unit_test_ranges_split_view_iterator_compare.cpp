/**
 *	@file	unit_test_ranges_split_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y);
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace iterator_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;

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

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_compare_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
