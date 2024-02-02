/**
 *	@file	unit_test_ranges_split_view_iterator_ctor_parent_current_next.cpp
 *
 *	@brief	parent,current,nextを引数に取るコンストラクタのテスト
 *
 *	constexpr iterator(split_view& parent, iterator_t<V> current, subrange<iterator_t<V>> next);
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace iterator_ctor_parent_current_next_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert( hamon::is_constructible<I, RV&, BaseIter, hamon::ranges::subrange<BaseIter>>::value, "");
	static_assert(!hamon::is_constructible<I, RV const&, BaseIter, hamon::ranges::subrange<BaseIter>>::value, "");
	static_assert(!hamon::is_constructible<I, RV&, BaseIter>::value, "");
	static_assert(!hamon::is_constructible<I, RV&, hamon::ranges::subrange<BaseIter>>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	
	I it(rv, v.begin(), hamon::ranges::subrange<BaseIter>{v.begin(), v.begin()});
	(void)it;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewIteratorCtorParentCurrentNextTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_ctor_parent_current_next_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
