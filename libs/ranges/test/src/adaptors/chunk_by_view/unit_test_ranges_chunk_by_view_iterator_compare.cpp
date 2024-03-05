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

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace iterator_compare_test
{

template <typename T, typename U, typename = void>
struct has_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_not_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_not_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;
	using I = decltype(hamon::declval<CV&>().begin());

	static_assert( has_equal<I, I>::value, "");
	static_assert( has_equal<I, hamon::default_sentinel_t>::value, "");
	static_assert( has_equal<hamon::default_sentinel_t, I>::value, "");
	static_assert( has_not_equal<I, I>::value, "");
	static_assert( has_not_equal<I, hamon::default_sentinel_t>::value, "");
	static_assert( has_not_equal<hamon::default_sentinel_t, I>::value, "");

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
