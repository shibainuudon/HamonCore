/**
 *	@file	unit_test_ranges_counted_view.cpp
 *
 *	@brief	views::counted のテスト
 */

#include <hamon/ranges/adaptors/counted_view.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/iterator/counted_iterator.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/span.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace counted_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[]{0,1,2,3,4,5,6,7,8,9};
	auto cv = hamon::views::counted(a+1, 3);
	using CV = decltype(cv);
	static_assert(hamon::is_same<CV, hamon::span<int, hamon::dynamic_extent>>::value, "");
	static_assert(hamon::ranges::borrowed_range_t<CV>::value, "");
	static_assert(hamon::ranges::sized_range_t<CV>::value, "");
	static_assert(hamon::ranges::output_range_t<CV, int>::value, "");
	static_assert(hamon::ranges::input_range_t<CV>::value, "");
	static_assert(hamon::ranges::forward_range_t<CV>::value, "");
	static_assert(hamon::ranges::bidirectional_range_t<CV>::value, "");
	static_assert(hamon::ranges::random_access_range_t<CV>::value, "");
	static_assert(hamon::ranges::contiguous_range_t<CV>::value, "");
	static_assert(hamon::ranges::common_range_t<CV>::value, "");
	static_assert(hamon::ranges::viewable_range_t<CV>::value, "");
	static_assert(hamon::ranges::view_t<CV>::value, "");
	VERIFY(cv.size() == 3);
	VERIFY(*cv.begin() == 1);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[]{0,1,2,3,4,5,6,7,8,9};
	random_access_iterator_wrapper<int> it{a};
	auto cv = hamon::views::counted(it, 4);
	using CV = decltype(cv);
	static_assert(hamon::is_same<CV,
		hamon::ranges::subrange<
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			hamon::ranges::subrange_kind::sized>>::value, "");
	static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
	static_assert( hamon::ranges::sized_range_t<CV>::value, "");
	static_assert( hamon::ranges::output_range_t<CV, int>::value, "");
	static_assert( hamon::ranges::input_range_t<CV>::value, "");
	static_assert( hamon::ranges::forward_range_t<CV>::value, "");
	static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
	static_assert( hamon::ranges::random_access_range_t<CV>::value, "");
	static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
	static_assert( hamon::ranges::common_range_t<CV>::value, "");
	static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
	static_assert( hamon::ranges::view_t<CV>::value, "");
	VERIFY(cv.size() == 4);
	VERIFY(cv.begin() == it);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[]{0,1,2,3,4,5,6,7,8,9};
	bidirectional_iterator_wrapper<int> it{a};
	auto cv = hamon::views::counted(it, 2);
	using CV = decltype(cv);
	static_assert(hamon::is_same<CV,
		hamon::ranges::subrange<
			hamon::counted_iterator<bidirectional_iterator_wrapper<int>>,
			hamon::default_sentinel_t,
			hamon::ranges::subrange_kind::sized>>::value, "");
	static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
	static_assert( hamon::ranges::sized_range_t<CV>::value, "");
	static_assert( hamon::ranges::output_range_t<CV, int>::value, "");
	static_assert( hamon::ranges::input_range_t<CV>::value, "");
	static_assert( hamon::ranges::forward_range_t<CV>::value, "");
	static_assert( hamon::ranges::bidirectional_range_t<CV>::value, "");
	static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
	static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
	static_assert(!hamon::ranges::common_range_t<CV>::value, "");
	static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
	static_assert( hamon::ranges::view_t<CV>::value, "");
	VERIFY(cv.size() == 2);
	VERIFY(cv.begin().base() == it);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[]{0,1,2,3,4,5,6,7,8,9};
	forward_iterator_wrapper<int> it{a};
	auto cv = hamon::views::counted(it, 5);
	using CV = decltype(cv);
	static_assert(hamon::is_same<CV,
		hamon::ranges::subrange<
			hamon::counted_iterator<forward_iterator_wrapper<int>>,
			hamon::default_sentinel_t,
			hamon::ranges::subrange_kind::sized>>::value, "");
	static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
	static_assert( hamon::ranges::sized_range_t<CV>::value, "");
	static_assert( hamon::ranges::output_range_t<CV, int>::value, "");
	static_assert( hamon::ranges::input_range_t<CV>::value, "");
	static_assert( hamon::ranges::forward_range_t<CV>::value, "");
	static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
	static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
	static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
	static_assert(!hamon::ranges::common_range_t<CV>::value, "");
	static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
	static_assert( hamon::ranges::view_t<CV>::value, "");
	VERIFY(cv.size() == 5);
	VERIFY(cv.begin().base() == it);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[]{0,1,2,3,4,5,6,7,8,9};
	input_iterator_wrapper<int> it{a};
	auto cv = hamon::views::counted(it, 6);
	using CV = decltype(cv);
	static_assert(hamon::is_same<CV,
		hamon::ranges::subrange<
			hamon::counted_iterator<input_iterator_wrapper<int>>,
			hamon::default_sentinel_t,
			hamon::ranges::subrange_kind::sized>>::value, "");
	static_assert( hamon::ranges::borrowed_range_t<CV>::value, "");
	static_assert( hamon::ranges::sized_range_t<CV>::value, "");
	static_assert(!hamon::ranges::output_range_t<CV, int>::value, "");
	static_assert( hamon::ranges::input_range_t<CV>::value, "");
	static_assert(!hamon::ranges::forward_range_t<CV>::value, "");
	static_assert(!hamon::ranges::bidirectional_range_t<CV>::value, "");
	static_assert(!hamon::ranges::random_access_range_t<CV>::value, "");
	static_assert(!hamon::ranges::contiguous_range_t<CV>::value, "");
	static_assert(!hamon::ranges::common_range_t<CV>::value, "");
	static_assert( hamon::ranges::viewable_range_t<CV>::value, "");
	static_assert( hamon::ranges::view_t<CV>::value, "");
	VERIFY(cv.size() == 6);
	VERIFY(cv.begin().base() == it);
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CountedViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());

#if defined(HAMON_HAS_CXX17_RANGE_BASED_FOR)
	{
		hamon::vector<int> v;
		int i = 0;
		for (auto& elem : hamon::views::counted(hamon::back_inserter(v), 5))
		{
			elem = i++;
		}
		int const expected[] = {0,1,2,3,4};
		EXPECT_TRUE(hamon::ranges::equal(v, expected));
	}
#endif
}

}	// namespace counted_view_test
}	// namespace hamon_ranges_test
