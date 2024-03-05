/**
 *	@file	unit_test_ranges_chunk_by_view_iterator_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	iterator() = default;
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace iterator_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;
	using I = decltype(hamon::declval<CV&>().begin());
	I it{};
	(void)it;	// TODO
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewIteratorCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_ctor_default_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
