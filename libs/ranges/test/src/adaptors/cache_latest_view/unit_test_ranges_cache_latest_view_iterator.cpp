/**
 *	@file	unit_test_ranges_cache_latest_view_iterator.cpp
 *
 *	@brief	cache_latest_view::iterator のテスト
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace iterator_test
{

template <template <typename> class ViewWrapper>
void test()
{
	using T = int;
	using V = ViewWrapper<T>;
	using CLV = hamon::ranges::cache_latest_view<V>;
	using I  = decltype(hamon::declval<CLV&>().begin());

	static_assert( has_base<I>::value, "");
	static_assert(!has_subscript<I>::value, "");
	static_assert( has_dereference<I>::value, "");
	static_assert(!has_arrow<I>::value, "");
	static_assert( has_pre_increment<I>::value, "");
	static_assert( has_post_increment<I>::value, "");
	static_assert(!has_pre_decrement<I>::value, "");
	static_assert(!has_post_decrement<I>::value, "");
	static_assert(!has_plus_equal<I, int>::value, "");
	static_assert(!has_minus_equal<I, int>::value, "");
	static_assert(!has_plus<I, int>::value, "");
	static_assert(!has_plus<int, I>::value, "");
	static_assert(!has_minus<I, int>::value, "");
	static_assert(!has_minus<I, I>::value, "");
	static_assert(!has_eq<I, I>::value, "");
	static_assert(!has_neq<I, I>::value, "");
	static_assert(!has_lt<I, I>::value, "");
	static_assert(!has_lteq<I, I>::value, "");
	static_assert(!has_gt<I, I>::value, "");
	static_assert(!has_gteq<I, I>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<I, I>::value, "");
#endif
}

GTEST_TEST(RangesTest, CacheLatestViewIteratorTest)
{
	test<test_input_view>();
	test<test_forward_view>();
	test<test_bidirectional_view>();
	test<test_random_access_view>();
	test<test_contiguous_view>();
}

}	// namespace iterator_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
