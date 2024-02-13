/**
 *	@file	unit_test_ranges_enumerate_view_iterator_pre_increment.cpp
 *
 *	@brief	前置インクリメントのテスト
 *
 *	constexpr iterator& operator++();
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace iterator_pre_increment_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;
	using I = decltype(hamon::declval<EV&>().begin());
	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");

	int a[] = {42, 3, 9};
	V v(a);
	EV ev(v);
	auto it = ev.begin();
	VERIFY(hamon::adl_get<0>(*it) == 0);
	VERIFY(hamon::adl_get<1>(*it) == 42);
	auto t1 = ++it;
	VERIFY(t1 == it);
	VERIFY(hamon::adl_get<0>(*it) == 1);
	VERIFY(hamon::adl_get<1>(*it) == 3);
	auto t2 = ++it;
	VERIFY(t2 == it);
	VERIFY(hamon::adl_get<0>(*it) == 2);
	VERIFY(hamon::adl_get<1>(*it) == 9);
	VERIFY(it != ev.end());
	VERIFY(++it == ev.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorPreIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_pre_increment_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
