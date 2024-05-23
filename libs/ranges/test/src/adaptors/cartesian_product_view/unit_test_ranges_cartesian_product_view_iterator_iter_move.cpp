/**
 *	@file	unit_test_ranges_cartesian_product_view_iterator_iter_move.cpp
 *
 *	@brief	iter_move のテスト
 *
 *	friend constexpr auto iter_move(const iterator& i) noexcept(see below);
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
{
namespace iterator_iter_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V1 = test_input_view<int>;
	using V2 = test_forward_view<char>;
	using CV = hamon::ranges::cartesian_product_view<V1, V2>;

	int a1[] = {42, 43, 44};
	char a2[] = {'a', 'b'};
	V1 v1(a1);
	V2 v2(a2);
	CV cv(v1, v2);

	auto it = cv.begin();
	static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), hamon::tuple<int&&, char&&>>::value, "");
	static_assert(!noexcept(hamon::ranges::iter_move(it)), "");
	auto x = hamon::ranges::iter_move(it);
	VERIFY(x == hamon::make_tuple(42, 'a'));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a1[] = {42, 43, 44};
	char a2[] = {'a', 'b'};
	auto cv = hamon::views::cartesian_product(a1, a2);

	auto it = cv.begin();
	++it;
	static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), hamon::tuple<int&&, char&&>>::value, "");
	static_assert(noexcept(hamon::ranges::iter_move(it)), "");
	auto x = hamon::ranges::iter_move(it);
	VERIFY(x == hamon::make_tuple(42, 'b'));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewIteratorIterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_iter_move_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
