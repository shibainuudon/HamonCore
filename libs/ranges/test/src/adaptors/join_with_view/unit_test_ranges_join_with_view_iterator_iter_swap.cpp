/**
 *	@file	unit_test_ranges_join_with_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	friend constexpr void iter_swap(const iterator& x, const iterator& y)
 *    requires indirectly_swappable<InnerIter, PatternIter>
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace iterator_iter_swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using InnerView = test_input_view<int>;
	using View = test_input_view<InnerView>;
	using Pattern = test_forward_view<int>;
	using JV = hamon::ranges::join_with_view<View, Pattern>;

	int a0[] = {1,2,3};
	int a1[] = {4,5};
	int a2[] = {6,7,8,9};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	int a3[] = {-1,-2};
	Pattern pat(a3);

	JV jv(v, pat);

	{
		auto it1 = jv.begin();
		auto it2 = jv.begin();
		++it2;
		hamon::ranges::iter_swap(it1, it2);
	}
	VERIFY(a0[0] == 2);
	VERIFY(a0[1] == 1);
	VERIFY(a0[2] == 3);
	VERIFY(a1[0] == 4);
	VERIFY(a1[1] == 5);
	VERIFY(a2[0] == 6);
	VERIFY(a2[1] == 7);
	VERIFY(a2[2] == 8);
	VERIFY(a2[3] == 9);
	VERIFY(a3[0] == -1);
	VERIFY(a3[1] == -2);

	{
		auto it1 = jv.begin();
		++it1;
		auto it2 = jv.begin();
		++it2;
		++it2;
		++it2;
		hamon::ranges::iter_swap(it1, it2);
	}
	VERIFY(a0[0] == 2);
	VERIFY(a0[1] == -1);
	VERIFY(a0[2] == 3);
	VERIFY(a1[0] == 4);
	VERIFY(a1[1] == 5);
	VERIFY(a2[0] == 6);
	VERIFY(a2[1] == 7);
	VERIFY(a2[2] == 8);
	VERIFY(a2[3] == 9);
	VERIFY(a3[0] == 1);
	VERIFY(a3[1] == -2);

	{
		auto it1 = jv.begin();
		++it1;
		++it1;
		++it1;
		++it1;
		++it1;
		auto it2 = jv.begin();
		++it2;
		++it2;
		++it2;
		++it2;
		++it2;
		++it2;
		++it2;
		++it2;
		++it2;
		++it2;
		hamon::ranges::iter_swap(it1, it2);
	}
	VERIFY(a0[0] == 2);
	VERIFY(a0[1] == -1);
	VERIFY(a0[2] == 3);
	VERIFY(a1[0] == 7);
	VERIFY(a1[1] == 5);
	VERIFY(a2[0] == 6);
	VERIFY(a2[1] == 4);
	VERIFY(a2[2] == 8);
	VERIFY(a2[3] == 9);
	VERIFY(a3[0] == 1);
	VERIFY(a3[1] == -2);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewIteratorIterSwapTest)
{
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test00());
#else
	EXPECT_TRUE(test00());
#endif
}

}	// namespace iterator_iter_swap_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
