/**
 *	@file	unit_test_ranges_join_with_view_iterator_iter_move.cpp
 *
 *	@brief	iter_move のテスト
 *
 *	friend constexpr decltype(auto) iter_move(const iterator& x);
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace iterator_iter_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(hamon::declval<I const&>())), int&&>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int const>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(hamon::declval<I const&>())), int const&&>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using V = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<char, forward_iterator_wrapper<char>>;
		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(hamon::declval<I const&>())), int>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
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
	auto it = jv.begin();
	auto x = hamon::ranges::iter_move(it);
	VERIFY(x == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewIteratorIterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace iterator_iter_move_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
