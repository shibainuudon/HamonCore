/**
 *	@file	unit_test_ranges_chunk_by_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y);
 *	friend constexpr bool operator==(const iterator& x, default_sentinel_t);
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace iterator_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;
	using I = decltype(hamon::declval<CV&>().begin());

	static_assert( has_eq<I, I>::value, "");
	static_assert( has_eq<I, hamon::default_sentinel_t>::value, "");
	static_assert( has_eq<hamon::default_sentinel_t, I>::value, "");
	static_assert( has_neq<I, I>::value, "");
	static_assert( has_neq<I, hamon::default_sentinel_t>::value, "");
	static_assert( has_neq<hamon::default_sentinel_t, I>::value, "");

	static_assert(!has_lt  <I>::value, "");
	static_assert(!has_lteq<I>::value, "");
	static_assert(!has_gt  <I>::value, "");
	static_assert(!has_gteq<I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<I>::value, "");
#endif

	int a[] = {1,2,3,4,0,1};
	V v(a);
	CV cv(v, F{});
	auto it = cv.begin();
	VERIFY( (it == cv.begin()));
	VERIFY(!(it != cv.begin()));
	VERIFY( (cv.begin() == it));
	VERIFY(!(cv.begin() != it));
	VERIFY(!(it == cv.end()));
	VERIFY( (it != cv.end()));
	VERIFY(!(cv.end() == it));
	VERIFY( (cv.end() != it));
	++it;
	VERIFY(!(it == cv.begin()));
	VERIFY( (it != cv.begin()));
	VERIFY(!(cv.begin() == it));
	VERIFY( (cv.begin() != it));
	VERIFY(!(it == cv.end()));
	VERIFY( (it != cv.end()));
	VERIFY(!(cv.end() == it));
	VERIFY( (cv.end() != it));
	++it;
	VERIFY(!(it == cv.begin()));
	VERIFY( (it != cv.begin()));
	VERIFY(!(cv.begin() == it));
	VERIFY( (cv.begin() != it));
	VERIFY( (it == cv.end()));
	VERIFY(!(it != cv.end()));
	VERIFY( (cv.end() == it));
	VERIFY(!(cv.end() != it));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_compare_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
