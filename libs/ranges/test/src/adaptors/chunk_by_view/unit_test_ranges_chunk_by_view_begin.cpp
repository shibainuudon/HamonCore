/**
 *	@file	unit_test_ranges_chunk_by_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr iterator begin();
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace begin_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;

	int a[] = {1,2,3};
	V v(a);
	CV cv(v, F{});
	auto it = cv.begin();
	VERIFY(it == cv.begin());
	VERIFY(it != cv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
