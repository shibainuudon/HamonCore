/**
 *	@file	unit_test_ranges_as_input_view_iterator_dereference.cpp
 *
 *	@brief	operator*() のテスト
 *
 *	constexpr decltype(auto) operator*() const { return *current_; }
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
namespace iterator_dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using AIV = hamon::ranges::as_input_view<V>;
	using I = decltype(hamon::declval<AIV&>().begin());

	static_assert(has_dereference<I&>::value, "");
	static_assert(has_dereference<I const&>::value, "");

	static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int&>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), int&>::value, "");

	int a[] = {2,3,4,5};
	V v(a);

	AIV aiv(v);

	auto it = aiv.begin();
	VERIFY(*it == 2);
	++it;
	VERIFY(*it == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
