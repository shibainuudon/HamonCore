/**
 *	@file	unit_test_ranges_as_input_view_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const sentinel_t<Base>& y);
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace iterator_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class ViewWrapper>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = ViewWrapper<T>;
	using AIV = hamon::ranges::as_input_view<V>;
	using I = decltype(hamon::declval<AIV&>().begin());
	using S = decltype(hamon::declval<AIV&>().end());

	static_assert(!has_eq<I, I>::value, "");
	static_assert( has_eq<I, S>::value, "");
	static_assert( has_eq<S, I>::value, "");
//	static_assert( has_eq<S, S>::value, "");

	static_assert(!has_neq<I, I>::value, "");
	static_assert( has_neq<I, S>::value, "");
	static_assert( has_neq<S, I>::value, "");
//	static_assert( has_neq<S, S>::value, "");

	static_assert(!has_lt<I, I>::value, "");
	static_assert(!has_lt<I, S>::value, "");
	static_assert(!has_lt<S, I>::value, "");
	static_assert(!has_lt<S, S>::value, "");
	static_assert(!has_lteq<I, I>::value, "");
	static_assert(!has_lteq<I, S>::value, "");
	static_assert(!has_lteq<S, I>::value, "");
	static_assert(!has_lteq<S, S>::value, "");
	static_assert(!has_gt<I, I>::value, "");
	static_assert(!has_gt<I, S>::value, "");
	static_assert(!has_gt<S, I>::value, "");
	static_assert(!has_gt<S, S>::value, "");
	static_assert(!has_gteq<I, I>::value, "");
	static_assert(!has_gteq<I, S>::value, "");
	static_assert(!has_gteq<S, I>::value, "");
	static_assert(!has_gteq<S, S>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<I>() == hamon::declval<S>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<S>() == hamon::declval<I>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I>() != hamon::declval<S>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<S>() != hamon::declval<I>()), bool>::value, "");

	int a[] = {1,2,3};
	V v(a);
	AIV aiv(v);

	auto it = aiv.begin();
	auto sent = aiv.end();
	VERIFY(!(it == sent));
	VERIFY( (it != sent));
	VERIFY(!(sent == it));
	VERIFY( (sent != it));
	++it;
	VERIFY(!(it == sent));
	VERIFY( (it != sent));
	VERIFY(!(sent == it));
	VERIFY( (sent != it));
	++it;
	VERIFY(!(it == sent));
	VERIFY( (it != sent));
	VERIFY(!(sent == it));
	VERIFY( (sent != it));
	++it;
	VERIFY( (it == sent));
	VERIFY(!(it != sent));
	VERIFY( (sent == it));
	VERIFY(!(sent != it));

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_view>());
}

}	// namespace iterator_compare_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
