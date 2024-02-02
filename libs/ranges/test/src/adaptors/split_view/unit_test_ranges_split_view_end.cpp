/**
 *	@file	unit_test_ranges_split_view_end.cpp
 *
 *	@brief	end() のテスト
 *
 *	constexpr auto end();
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace end_test
{

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV&&>::value, "");
	static_assert(!has_end<RV const&>::value, "");
	static_assert(!has_end<RV const&&>::value, "");

	using I = decltype(hamon::declval<RV&>().begin());
	using S = decltype(hamon::declval<RV&>().end());
	static_assert(!hamon::is_same<I, S>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto sent = rv.end();
	(void)sent;

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_forward_common_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV&&>::value, "");
	static_assert(!has_end<RV const&>::value, "");
	static_assert(!has_end<RV const&&>::value, "");

	using I = decltype(hamon::declval<RV&>().begin());
	using S = decltype(hamon::declval<RV&>().end());
	static_assert(hamon::is_same<I, S>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto sent = rv.end();
	(void)sent;

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace end_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
