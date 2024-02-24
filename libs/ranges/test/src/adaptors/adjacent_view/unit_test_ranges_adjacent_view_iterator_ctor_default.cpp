/**
 *	@file	unit_test_ranges_adjacent_view_iterator_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	iterator() = default;
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace iterator_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using AV = hamon::ranges::adjacent_view<V, 2>;
	using I = decltype(hamon::declval<AV&>().begin());
	I it{};
	(void)it;	// TODO
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewIteratorCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_ctor_default_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
