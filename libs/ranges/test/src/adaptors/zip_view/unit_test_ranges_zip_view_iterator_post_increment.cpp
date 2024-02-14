/**
 *	@file	unit_test_ranges_zip_view_iterator_post_increment.cpp
 *
 *	@brief	後置インクリメントのテスト
 *
 *	constexpr void operator++(int);
 *	constexpr iterator operator++(int) requires all-forward<Const, Views...>;
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace iterator_post_increment_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V1 = test_forward_view<int>;
	using V2 = test_input_view<char>;
	using ZV = hamon::ranges::zip_view<V1, V2>;
	using I = decltype(hamon::declval<ZV&>().begin());
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");

	int a1[] = {42, 43, 44};
	char a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(v1, v2);

	auto it = zv.begin();
	VERIFY(hamon::adl_get<0>(*it) == 42);
	VERIFY(hamon::adl_get<1>(*it) == 1);
	it++;
	VERIFY(hamon::adl_get<0>(*it) == 43);
	VERIFY(hamon::adl_get<1>(*it) == 2);
	it++;
	VERIFY(hamon::adl_get<0>(*it) == 44);
	VERIFY(hamon::adl_get<1>(*it) == 3);
	VERIFY(it != zv.end());
	it++;
	VERIFY(it == zv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_forward_view<int>;
	using V2 = test_forward_view<char>;
	using ZV = hamon::ranges::zip_view<V1, V2>;
	using I = decltype(hamon::declval<ZV&>().begin());
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), I>::value, "");

	int a1[] = {42, 43, 44};
	char a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(v1, v2);

	auto it = zv.begin();
	VERIFY(hamon::adl_get<0>(*it) == 42);
	VERIFY(hamon::adl_get<1>(*it) == 1);
	auto t1 = it++;
	VERIFY(t1 != it);
	VERIFY(hamon::adl_get<0>(*t1) == 42);
	VERIFY(hamon::adl_get<1>(*t1) == 1);
	VERIFY(hamon::adl_get<0>(*it) == 43);
	VERIFY(hamon::adl_get<1>(*it) == 2);
	auto t2 = it++;
	VERIFY(t2 != it);
	VERIFY(hamon::adl_get<0>(*t2) == 43);
	VERIFY(hamon::adl_get<1>(*t2) == 2);
	VERIFY(hamon::adl_get<0>(*it) == 44);
	VERIFY(hamon::adl_get<1>(*it) == 3);
	VERIFY(it++ != zv.end());
	VERIFY(it   == zv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_post_increment_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
