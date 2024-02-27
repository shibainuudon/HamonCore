/**
 *	@file	unit_test_ranges_adjacent_transform_view_ctor_base_fun.cpp
 *
 *	@brief	baseとfunを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit adjacent_transform_view(V base, F fun);
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace ctor_base_fun_test
{

struct F
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;

	static_assert( hamon::is_constructible<AV, V, F>::value, "");
	static_assert(!hamon::is_constructible<AV, F, V>::value, "");
	static_assert(!hamon::is_constructible<AV, V, int>::value, "");
	static_assert(!hamon::is_constructible<AV, V, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<AV, V, F>::value, "");

	int a[] = {1,2,3};
	V v(a);
	F f;
	AV av{v, f};
	(void)av;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewCtorBaseFunTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_base_fun_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
