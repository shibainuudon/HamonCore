/**
 *	@file	unit_test_ranges_lazy_split_view_outer_iterator_ctor_parent.cpp
 *
 *	@brief	parentを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit outer-iterator(Parent& parent)
 *	  requires (!forward_range<Base>);
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
namespace outer_iterator_ctor_parent_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;

		static_assert(!hamon::is_constructible<I, RV&>::value, "");
	}
	{
		using V = test_input_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;

		static_assert(hamon::is_constructible<I, RV&>::value, "");

		RV rv{};
		I it{rv};
		(void)it;
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewOuterIteratorCtorParentTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace outer_iterator_ctor_parent_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
