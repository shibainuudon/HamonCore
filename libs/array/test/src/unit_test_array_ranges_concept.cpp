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

	static_assert(!hamon::ranges::view<Array>, "");
	static_assert( hamon::same_as<hamon::ranges::iterator_t<Array>, typename Array::iterator>, "");
	static_assert( hamon::ranges::common_range<Array>, "");
	static_assert( hamon::ranges::random_access_range<Array>, "");
	static_assert( hamon::ranges::contiguous_range<Array>, "");
	static_assert( hamon::ranges::sized_range<Array>, "");
	static_assert(!hamon::ranges::borrowed_range<Array>, "");
	static_assert( hamon::ranges::viewable_range<Array>, "");

	static_assert(!hamon::ranges::view<Array const>, "");
	static_assert( hamon::same_as<hamon::ranges::iterator_t<Array const>, typename Array::const_iterator>, "");
	static_assert( hamon::ranges::common_range<Array const>, "");
	static_assert( hamon::ranges::random_access_range<Array const>, "");
	static_assert( hamon::ranges::contiguous_range<Array const>, "");
	static_assert( hamon::ranges::sized_range<Array const>, "");
	static_assert(!hamon::ranges::borrowed_range<Array const>, "");
	static_assert(!hamon::ranges::viewable_range<Array const>, "");
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
