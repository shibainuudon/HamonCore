/**
 *	@file	unit_test_ranges_lazy_split_view_outer_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr value_type operator*() const;
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace outer_iterator_dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;
	static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), typename I::value_type>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), typename I::value_type>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};

	V v(a1);
	P p(a2);
	RV rv(v, p);

	auto it = rv.begin();
	auto inner = *it;
	auto it2 = inner.begin();
	VERIFY(*it2 == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewOuterIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace outer_iterator_dereference_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
