/**
 *	@file	unit_test_ranges_split_view_iterator_base.cpp
 *
 *	@brief	base()  のテスト
 *
 *	constexpr iterator_t<V> base() const;
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace iterator_base_test
{

template <typename T, typename = void>
struct has_base
	: public hamon::false_type {};

template <typename T>
struct has_base<T, hamon::void_t<decltype(hamon::declval<T>().base())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert( has_base<I&>::value, "");
	static_assert( has_base<I&&>::value, "");
	static_assert( has_base<I const&>::value, "");
	static_assert( has_base<I const&&>::value, "");

	static_assert(hamon::is_same<BaseIter, decltype(hamon::declval<I&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter, decltype(hamon::declval<I&&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter, decltype(hamon::declval<I const&>().base())>::value, "");
	static_assert(hamon::is_same<BaseIter, decltype(hamon::declval<I const&&>().base())>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	{
		auto&& b = i.base();
		static_assert(hamon::is_same<decltype(b), BaseIter&&>::value, "");
		VERIFY(b == v.begin());
	}
	{
		auto&& b = hamon::move(i).base();
		static_assert(hamon::is_same<decltype(b), BaseIter&&>::value, "");
		VERIFY(b == v.begin());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewIteratorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_base_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
