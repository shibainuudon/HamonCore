/**
 *	@file	unit_test_ranges_adjacent_view_iterator_iter_move.cpp
 *
 *	@brief	iter_move() のテスト
 *
 *	friend constexpr auto iter_move(const iterator& i) noexcept(see below);
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace iterator_iter_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_view<V, 2>;

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v};

		auto it = av.begin();
#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		static_assert(!noexcept(hamon::ranges::iter_move(it)), "");
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), hamon::tuple<int&&, int&&>>::value, "");
#endif
		auto x = hamon::ranges::iter_move(it);
		VERIFY(x == hamon::make_tuple(1, 2));
	}
	{
		using V = test_forward_view<int const>;
		using AV = hamon::ranges::adjacent_view<V, 3>;

		int a[] = {10,20,30,40};
		V v(a);
		AV av{v};

		auto it = av.begin();
#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		static_assert(!noexcept(hamon::ranges::iter_move(it)), "");
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), hamon::tuple<int const&&, int const&&, int const&&>>::value, "");
#endif
		auto x = hamon::ranges::iter_move(it);
		VERIFY(x == hamon::make_tuple(10, 20, 30));
	}
	{
		using V = test_view<int, int*>;
		using AV = hamon::ranges::adjacent_view<V, 2>;

		int a[] = {1,2,3,4};
		V v(a);
		AV av{v};

		auto it = av.begin();
#if !(defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION < 110000))
		static_assert( noexcept(hamon::ranges::iter_move(it)), "");
		static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), hamon::tuple<int&&, int&&>>::value, "");
#endif
		auto x = hamon::ranges::iter_move(it);
		VERIFY(x == hamon::make_tuple(1, 2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewIteratorIterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_iter_move_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
