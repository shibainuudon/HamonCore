/**
 *	@file	unit_test_ranges_concat_view_iterator_dereference.cpp
 *
 *	@brief	operator*() のテスト
 *
 *	constexpr decltype(auto) operator*() const;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
{
namespace iterator_dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<int>;
	using CV = hamon::ranges::concat_view<V1, V2>;
	using I = decltype(hamon::declval<CV&>().begin());
	using CI = decltype(hamon::declval<CV const&>().begin());

	static_assert(has_dereference<I&>::value, "");
	static_assert(has_dereference<I const&>::value, "");
	static_assert(has_dereference<CI&>::value, "");
	static_assert(has_dereference<CI const&>::value, "");

	static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int&>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), int&>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<CI&>()), int&>::value, "");
	static_assert(hamon::is_same<decltype(*hamon::declval<CI const&>()), int&>::value, "");

	int a1[] = {1,2};
	int a2[] = {3,4,5};
	V1 v1(a1);
	V2 v2(a2);

	CV cv(v1, v2);

	auto it = cv.begin();
	VERIFY(*it == 1);
	++it;
	++it;
	VERIFY(*it == 3);
	*it = 42;
	VERIFY(a2[0] == 42);
	VERIFY(*it == 42);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewIteratorDereferenceTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
