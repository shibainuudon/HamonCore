/**
 *	@file	unit_test_ranges_split_view_iterator_pre_increment.cpp
 *
 *	@brief	前置インクリメントのテスト
 *
 *	constexpr iterator& operator++();
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace iterator_pre_increment_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;

	static_assert(hamon::is_same<decltype(++hamon::declval<I>()), I&>::value, "");

	int a1[] = {3, 1, 2, 4, 5, 1, 2, 6};
	int a2[] = {1, 2};

	V v(a1);
	P p(a2);
	RV rv(v, p);

	auto i = rv.begin();
	VERIFY(*((*i).begin()) == 3);
	auto& t1 = ++i;
	VERIFY(*((*i).begin()) == 4);
	VERIFY(&t1 == &i);
	auto& t2 = ++i;
	VERIFY(*((*i).begin()) == 6);
	VERIFY(&t2 == &i);
	auto& t3 = ++i;
	VERIFY(i == rv.end());
	VERIFY(&t3 == &i);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewIteratorPreIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_pre_increment_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
