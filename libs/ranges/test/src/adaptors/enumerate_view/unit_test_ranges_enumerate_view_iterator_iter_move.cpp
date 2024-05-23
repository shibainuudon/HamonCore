/**
 *	@file	unit_test_ranges_enumerate_view_iterator_iter_move.cpp
 *
 *	@brief	iter_move のテスト
 *
 *	friend constexpr auto iter_move(const iterator& i);
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace iterator_iter_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;

	int a[] = {11,13,15,17,19};
	V v(a);
	EV ev{v};

	auto it = ev.begin();
	static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), hamon::tuple<hamon::ptrdiff_t, int&&>>::value, "");
	auto x = hamon::ranges::iter_move(it);
	VERIFY(hamon::adl_get<0>(x) == 0);
	VERIFY(hamon::adl_get<1>(x) == 11);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorIterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_iter_move_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
