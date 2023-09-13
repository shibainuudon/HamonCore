/**
 *	@file	unit_test_algorithm_ranges_make_heap.cpp
 *
 *	@brief	ranges::make_heap のテスト
 */

#include <hamon/algorithm/ranges/make_heap.hpp>
#include <hamon/algorithm/ranges/is_heap.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_make_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int a[] = { 3, 1, 4 };
		auto it = ranges::make_heap(a);
		VERIFY(it == a+3);
		VERIFY(ranges::is_heap(a));
	}
	{
		int a[] = { 3, 1, 4 };
		auto it = ranges::make_heap(a, ranges::greater{});
		VERIFY(it == a+3);
		VERIFY(ranges::is_heap(a, ranges::greater{}));
	}
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		test_random_access_range<int> r(a);
		auto it = ranges::make_heap(r);
		VERIFY(it == r.end());
		VERIFY(ranges::is_heap(r));
	}
	{
		int a[] = { 3, 1, 4, 1, 5, 9 };
		test_random_access_range<int> r(a);
		auto it = ranges::make_heap(r, ranges::greater{});
		VERIFY(it == r.end());
		VERIFY(ranges::is_heap(r, ranges::greater{}));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		hamon::vector<int> a { 5, 4, 1, 1, 3 };
		auto it = ranges::make_heap(a);
		VERIFY(it == a.end());
		VERIFY(ranges::is_heap(a));
	}
	{
		hamon::vector<int> a { 5, 4, 1, 1, 3 };
		auto it = ranges::make_heap(a, ranges::greater{});
		VERIFY(it == a.end());
		VERIFY(ranges::is_heap(a, ranges::greater{}));
	}
	{
		hamon::vector<int> a;
		auto it = ranges::make_heap(a);
		VERIFY(it == a.end());
		VERIFY(a.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMakeHeapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_make_heap_test

}	// namespace hamon_algorithm_test
