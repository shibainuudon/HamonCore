/**
 *	@file	unit_test_ranges_cache_latest_view_iterator_pre_increment.cpp
 *
 *	@brief	前置インクリメントのテスト
 *
 *	constexpr iterator& operator++();
 */

#include <hamon/ranges/adaptors/cache_latest_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace cache_latest_view_test
{
namespace iterator_pre_increment_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class ViewWrapper>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = ViewWrapper<T>;
	using CLV = hamon::ranges::cache_latest_view<V>;
	using I  = decltype(hamon::declval<CLV&>().begin());

	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");

	int a[] = {1,2,3};
	V v(a);

	CLV clv(v);
	auto it = clv.begin();
	VERIFY(it != clv.end());
	VERIFY(*it == 1);
	auto& t1 = ++it;
	VERIFY(it != clv.end());
	VERIFY(*it == 2);
	VERIFY(*t1 == 2);
	auto& t2 = ++it;
	VERIFY(it != clv.end());
	VERIFY(*it == 3);
	VERIFY(*t2 == 3);
	auto& t3 = ++it;
	VERIFY(it == clv.end());
	VERIFY(t3 == clv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CacheLatestViewIteratorPreIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_view>());
}

}	// namespace iterator_pre_increment_test
}	// namespace cache_latest_view_test
}	// namespace hamon_ranges_test
