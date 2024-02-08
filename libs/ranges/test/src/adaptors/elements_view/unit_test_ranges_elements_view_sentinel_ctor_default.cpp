/**
 *	@file	unit_test_ranges_elements_view_sentinel_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	sentinel() = default;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace sentinel_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using S = hamon::ranges::sentinel_t<EV>;
		using BaseSent = hamon::ranges::sentinel_t<V>;

		S sent{};
		VERIFY(sent.base() == BaseSent{});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewSentinelCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_default_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
