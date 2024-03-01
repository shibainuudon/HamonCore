/**
 *	@file	unit_test_ranges_slide_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr auto operator*() const;
 */

#include <hamon/ranges/adaptors/slide_view.hpp>
#include <hamon/ranges/adaptors/counted_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace slide_view_test
{
namespace iterator_dereference_test
{

template <typename T, typename = void>
struct has_dereference
	: public hamon::false_type {};

template <typename T>
struct has_dereference<T, hamon::void_t<decltype(*hamon::declval<T>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_random_access_view<int>;
	using SV = hamon::ranges::slide_view<V>;
	using I  = decltype(hamon::declval<SV&>().begin());
	static_assert( has_dereference<I&>::value, "");
	static_assert( has_dereference<I const&>::value, "");
	static_assert(hamon::is_same<
		decltype(*hamon::declval<I&>()),
		decltype(hamon::views::counted(
			hamon::declval<hamon::ranges::iterator_t<V>>(),
			hamon::declval<hamon::ranges::range_difference_t<V>>()))
	>::value, "");
	int a[] = {10,20,30,40};
	V v(a);
	SV sv(v, 2);
	auto it = sv.begin();
	int const expected[] = {10,20};
	VERIFY(hamon::ranges::equal(*it, expected));
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SlideViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace slide_view_test
}	// namespace hamon_ranges_test
