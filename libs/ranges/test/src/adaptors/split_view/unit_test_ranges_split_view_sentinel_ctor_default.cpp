/**
 *	@file	unit_test_ranges_split_view_sentinel_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	sentinel() = default;
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace sentinel_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;
	using S = hamon::ranges::sentinel_t<RV>;

	static_assert(hamon::is_default_constructible<S>::value, "");

	S sent{};
	(void)sent;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewSentinelCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_default_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
