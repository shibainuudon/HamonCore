/**
 *	@file	unit_test_ranges_stride_view_iterator_iter_move.cpp
 *
 *	@brief	iter_move のテスト
 *
 *	friend constexpr range_rvalue_reference_t<Base> iter_move(const iterator& i)
 *	  noexcept(noexcept(ranges::iter_move(i.current_)));
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace iterator_iter_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using SV = hamon::ranges::stride_view<V>;

		int a[] = {1,2,3,4};
		V v(a);
		SV sv{v, 1};

		auto it = sv.begin();
		static_assert(!noexcept(hamon::ranges::iter_move(it)), "");
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), int&&>::value, "");

		auto x = hamon::ranges::iter_move(it);
		VERIFY(x == 1);
	}
	{
		using V = test_input_view<int const>;
		using SV = hamon::ranges::stride_view<V>;

		int a[] = {1,2,3,4};
		V v(a);
		SV sv{v, 1};

		auto it = sv.begin();
		static_assert(!noexcept(hamon::ranges::iter_move(it)), "");
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), int const&&>::value, "");

		auto x = hamon::ranges::iter_move(it);
		VERIFY(x == 1);
	}
	{
		using V = test_view<int, int*>;
		using SV = hamon::ranges::stride_view<V>;

		int a[] = {1,2,3,4};
		V v(a);
		SV sv{v, 1};

		auto it = sv.begin();
		static_assert( noexcept(hamon::ranges::iter_move(it)), "");
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), int&&>::value, "");

		auto x = hamon::ranges::iter_move(it);
		VERIFY(x == 1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorIterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_iter_move_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
