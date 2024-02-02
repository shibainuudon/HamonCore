/**
 *	@file	unit_test_ranges_split_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr value_type operator*() const;
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace iterator_dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using P = test_forward_view<int>;
	using RV = hamon::ranges::split_view<V, P>;
	using I = hamon::ranges::iterator_t<RV>;
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert(hamon::is_same<hamon::ranges::subrange<BaseIter>, decltype(*hamon::declval<I const&>())>::value, "");

	int a1[] = {1, 2, 3, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	auto i = rv.begin();
	auto inner = *i;
	VERIFY(inner.begin().m_ptr == a1 + 0);
	VERIFY(inner.end().m_ptr   == a1 + 5);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
