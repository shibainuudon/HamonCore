/**
 *	@file	unit_test_ranges_enumerate_view_iterator_index.cpp
 *
 *	@brief	index() のテスト
 *
 *	constexpr difference_type index() const noexcept;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace iterator_index_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;
	using I = decltype(hamon::declval<EV&>().begin());
	using D = hamon::ranges::range_difference_t<V>;

	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().index()), D>::value, "");

	static_assert( noexcept(hamon::declval<I const&>().index()), "");
	
	int a[] = {1,2,3};
	V v(a);
	EV ev(v);
	auto it = ev.begin();
	VERIFY(it.index() == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorindexTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_index_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
