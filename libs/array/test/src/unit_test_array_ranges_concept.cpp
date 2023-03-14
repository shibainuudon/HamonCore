/**
 *	@file	unit_test_array_ranges_concept.cpp
 *
 *	@brief	rangesコンセプトのテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <gtest/gtest.h>

namespace hamon_array_test
{

namespace ranges_concept_test
{

template <typename T, hamon::size_t N>
void RangesConceptTest()
{
	using Array = hamon::array<T, N>;

	static_assert(!hamon::ranges::view_t<Array>::value, "");
	static_assert( hamon::same_as_t<hamon::ranges::iterator_t<Array>, typename Array::iterator>::value, "");
	static_assert( hamon::ranges::common_range_t<Array>::value, "");
	static_assert( hamon::ranges::random_access_range_t<Array>::value, "");
	static_assert( hamon::ranges::contiguous_range_t<Array>::value, "");
	static_assert( hamon::ranges::sized_range_t<Array>::value, "");
	static_assert(!hamon::ranges::borrowed_range_t<Array>::value, "");
	static_assert( hamon::ranges::viewable_range_t<Array>::value, "");

	static_assert(!hamon::ranges::view_t<Array const>::value, "");
	static_assert( hamon::same_as_t<hamon::ranges::iterator_t<Array const>, typename Array::const_iterator>::value, "");
	static_assert( hamon::ranges::common_range_t<Array const>::value, "");
	static_assert( hamon::ranges::random_access_range_t<Array const>::value, "");
	static_assert( hamon::ranges::contiguous_range_t<Array const>::value, "");
	static_assert( hamon::ranges::sized_range_t<Array const>::value, "");
	static_assert(!hamon::ranges::borrowed_range_t<Array const>::value, "");
	static_assert(!hamon::ranges::viewable_range_t<Array const>::value, "");
}

GTEST_TEST(ArrayTest, RangesConceptTest)
{
	RangesConceptTest<char, 0>();
	RangesConceptTest<char, 1>();
	RangesConceptTest<int, 0>();
	RangesConceptTest<int, 2>();
	RangesConceptTest<float, 0>();
	RangesConceptTest<float, 10>();
	RangesConceptTest<double, 0>();
	RangesConceptTest<double, 20>();
}

}	// namespace ranges_concept_test

}	// namespace hamon_array_test
