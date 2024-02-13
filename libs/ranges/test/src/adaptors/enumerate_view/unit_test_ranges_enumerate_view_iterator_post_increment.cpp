/**
 *	@file	unit_test_ranges_enumerate_view_iterator_post_increment.cpp
 *
 *	@brief	後置インクリメントのテスト
 *
 *	constexpr void operator++(int);
 *	constexpr iterator operator++(int) requires forward_range<Base>;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace iterator_post_increment_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;
	using I = decltype(hamon::declval<EV&>().begin());
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");

	int a[] = {42, 3, 9};
	V v(a);
	EV ev(v);
	auto it = ev.begin();
	VERIFY(hamon::adl_get<0>(*it) == 0);
	VERIFY(hamon::adl_get<1>(*it) == 42);
	it++;
	VERIFY(hamon::adl_get<0>(*it) == 1);
	VERIFY(hamon::adl_get<1>(*it) == 3);
	it++;
	VERIFY(hamon::adl_get<0>(*it) == 2);
	VERIFY(hamon::adl_get<1>(*it) == 9);
	VERIFY(it != ev.end());
	it++;
	VERIFY(it == ev.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;
	using I = decltype(hamon::declval<EV&>().begin());
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");

	int a[] = {42, 3, 9};
	V v(a);
	EV ev(v);
	auto it = ev.begin();
	VERIFY(hamon::adl_get<0>(*it) == 0);
	VERIFY(hamon::adl_get<1>(*it) == 42);
	auto t1 = it++;
	VERIFY(t1 != it);
	VERIFY(hamon::adl_get<0>(*t1) == 0);
	VERIFY(hamon::adl_get<1>(*t1) == 42);
	VERIFY(hamon::adl_get<0>(*it) == 1);
	VERIFY(hamon::adl_get<1>(*it) == 3);
	auto t2 = it++;
	VERIFY(t2 != it);
	VERIFY(hamon::adl_get<0>(*t2) == 1);
	VERIFY(hamon::adl_get<1>(*t2) == 3);
	VERIFY(hamon::adl_get<0>(*it) == 2);
	VERIFY(hamon::adl_get<1>(*it) == 9);
	VERIFY(it++ != ev.end());
	VERIFY(it   == ev.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_post_increment_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
