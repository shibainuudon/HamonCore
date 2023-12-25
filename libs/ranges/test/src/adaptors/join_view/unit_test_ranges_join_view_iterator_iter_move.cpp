/**
 *	@file	unit_test_ranges_join_view_iterator_iter_move.cpp
 *
 *	@brief	iter_move のテスト
 *
 *	friend constexpr decltype(auto) iter_move(const iterator& i);
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace iterator_iter_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	hamon::array<hamon::array<int, 2>, 3> a
	{{
		{{11, 12}},
		{{21, 22}},
		{{31, 32}},
	}};
	auto rv = a | hamon::views::join;

	auto it = rv.begin();
	VERIFY(*it == 11);
	//static_assert(noexcept(hamon::ranges::iter_move(it)), "");
	static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), int&&>::value, "");
	auto x = hamon::ranges::iter_move(it);
	VERIFY(x == 11);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a0[] = {21,22};
	int a1[] = {23,24,25};
	int a2[] = {26};
	using InnerView = test_forward_view<int>;
	using View = test_forward_view<InnerView>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	hamon::ranges::join_view<View> rv(v);

	auto it = rv.begin();
	static_assert(!noexcept(hamon::ranges::iter_move(it)), "");
	static_assert(hamon::is_same<decltype(hamon::ranges::iter_move(it)), int&&>::value, "");
	auto x = hamon::ranges::iter_move(it);
	VERIFY(x == 21);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorIterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_iter_move_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
