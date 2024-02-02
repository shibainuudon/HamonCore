/**
 *	@file	unit_test_ranges_split_view_sentinel_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const sentinel& y);
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace sentinel_compare_test
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

	auto i = rv.begin();
	VERIFY(!(i == rv.end()));
	VERIFY( (i != rv.end()));
	VERIFY(!(rv.end() == i));
	VERIFY( (rv.end() != i));
	++i;
	VERIFY(!(i == rv.end()));
	VERIFY( (i != rv.end()));
	VERIFY(!(rv.end() == i));
	VERIFY( (rv.end() != i));
	++i;
	VERIFY( (i == rv.end()));
	VERIFY(!(i != rv.end()));
	VERIFY( (rv.end() == i));
	VERIFY(!(rv.end() != i));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewSentinelCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_compare_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
