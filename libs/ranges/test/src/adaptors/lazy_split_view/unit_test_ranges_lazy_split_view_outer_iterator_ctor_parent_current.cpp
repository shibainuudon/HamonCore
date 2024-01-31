/**
 *	@file	unit_test_ranges_lazy_split_view_outer_iterator_ctor_parent_current.cpp
 *
 *	@brief	parentとcurrentを引数に取るコンストラクタのテスト
 *
 *	constexpr outer-iterator(Parent& parent, iterator_t<Base> current)
 *	  requires forward_range<Base>;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace outer_iterator_ctor_parent_current_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using BaseI = hamon::ranges::iterator_t<V>;
		using I = hamon::ranges::iterator_t<RV>;

		static_assert(hamon::is_constructible<I, RV&, BaseI>::value, "");

		RV rv{};
		BaseI bi{};
		I it{rv, bi};
		(void)it;
	}
	{
		using V = test_input_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using BaseI = hamon::ranges::iterator_t<V>;
		using I = hamon::ranges::iterator_t<RV>;

		static_assert(!hamon::is_constructible<I, RV&, BaseI>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewOuterIteratorCtorParentCurrentTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace outer_iterator_ctor_parent_current_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
