/**
 *	@file	unit_test_ranges_enumerate_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr auto operator*() const;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace iterator_dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;
	using I = decltype(hamon::declval<EV&>().begin());
	using D = hamon::ranges::range_difference_t<V>;
	using R = hamon::ranges::range_reference_t<V>;

	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), hamon::tuple<D, R>>::value, "");
	
	int a[] = {42, 43, 44};
	V v(a);
	EV ev(v);
	auto it = ev.begin();
	auto t = *it;
	VERIFY(hamon::adl_get<0>(t) == 0);
	VERIFY(hamon::adl_get<1>(t) == 42);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
