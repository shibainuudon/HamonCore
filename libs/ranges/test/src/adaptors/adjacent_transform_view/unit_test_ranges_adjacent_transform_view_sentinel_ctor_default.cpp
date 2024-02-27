/**
 *	@file	unit_test_ranges_adjacent_transform_view_sentinel_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	sentinel() = default;
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace sentinel_ctor_default_test
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
	using S = decltype(hamon::declval<AV&>().end());
	S sent{};
	(void)sent;	// TODO
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewSentinelCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_default_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
