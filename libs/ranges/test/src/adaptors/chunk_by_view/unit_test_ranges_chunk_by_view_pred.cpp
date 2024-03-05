/**
 *	@file	unit_test_ranges_chunk_by_view_pred.cpp
 *
 *	@brief	pred() のテスト
 *
 *	constexpr const Pred& pred() const;
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace pred_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;

	static_assert(hamon::is_same<F const&, decltype(hamon::declval<CV&>().pred())>::value, "");
	static_assert(hamon::is_same<F const&, decltype(hamon::declval<CV&&>().pred())>::value, "");
	static_assert(hamon::is_same<F const&, decltype(hamon::declval<CV const&>().pred())>::value, "");
	static_assert(hamon::is_same<F const&, decltype(hamon::declval<CV const&&>().pred())>::value, "");

	int a[] = {1,2,3};
	V v(a);
	CV cv(v, F{});
	auto f = cv.pred();
	(void)f;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewPredTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace pred_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
