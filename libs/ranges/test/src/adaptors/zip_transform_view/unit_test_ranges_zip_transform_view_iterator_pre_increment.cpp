/**
 *	@file	unit_test_ranges_zip_transform_view_iterator_pre_increment.cpp
 *
 *	@brief	前置インクリメントのテスト
 *
 *	constexpr iterator& operator++();
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace iterator_pre_increment_test
{

struct Add
{
	constexpr int operator()(int x, char y) const { return x + y; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using F = Add;
	using V1 = test_input_view<int>;
	using V2 = test_input_view<char>;
	using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
	using I = decltype(hamon::declval<ZV&>().begin());
	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");

	F f{};
	int a1[] = {42, 43, 44};
	char a2[] = {1,2,3,4};
	V1 v1(a1);
	V2 v2(a2);
	ZV zv(f, v1, v2);
	auto it = zv.begin();
	VERIFY(*it == 43);
	auto t1 = ++it;
	VERIFY(t1 == it);
	VERIFY(*it == 45);
	auto t2 = ++it;
	VERIFY(t2 == it);
	VERIFY(*it == 47);
	VERIFY(it != zv.end());
	VERIFY(++it == zv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewIteratorPreIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_pre_increment_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
