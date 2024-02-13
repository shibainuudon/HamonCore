/**
 *	@file	unit_test_ranges_enumerate_view_sentinel_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	sentinel() = default;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace sentinel_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;
	using S = hamon::ranges::sentinel_t<EV>;
	using BaseSent = hamon::ranges::sentinel_t<V>;

	S sent{};
	VERIFY(sent.base() == BaseSent{});

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewSentinelCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_default_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
