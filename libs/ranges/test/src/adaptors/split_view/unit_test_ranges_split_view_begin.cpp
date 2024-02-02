/**
 *	@file	unit_test_ranges_split_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr iterator begin();
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace begin_test
{

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;

	static_assert( has_begin<RV&>::value, "");
	static_assert( has_begin<RV&&>::value, "");
	static_assert(!has_begin<RV const&>::value, "");
	static_assert(!has_begin<RV const&&>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto it = rv.begin();
	(void)it;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
