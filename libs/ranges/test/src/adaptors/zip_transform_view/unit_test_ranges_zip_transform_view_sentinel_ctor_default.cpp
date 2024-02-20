/**
 *	@file	unit_test_ranges_zip_transform_view_sentinel_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	sentinel() = default;
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace sentinel_ctor_default_test
{

struct F1
{
	int operator()(int) const;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using ZV = hamon::ranges::zip_transform_view<F1, V>;
	using S = decltype(hamon::declval<ZV&>().end());

	S sent{};
	(void)sent;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewSentinelCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_default_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
