/**
 *	@file	unit_test_algorithm_ranges_is_heap.cpp
 *
 *	@brief	ranges::is_heap のテスト
 */

#include <hamon/algorithm/ranges/is_heap.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_is_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int a[] { 1, 2, 3 };
		VERIFY(false == ranges::is_heap(a, a + 3));
	}
	{
		int a[] { 1, 2, 3 };
		VERIFY(true  == ranges::is_heap(a, a + 3, ranges::greater{}));
	}
	{
		int a[] { 3, 2, 1 };
		VERIFY(true  == ranges::is_heap(a));
	}
	{
		int a[] { 3, 2, 1 };
		VERIFY(false == ranges::is_heap(a, ranges::greater{}));
	}
	{
		int a[] { 9, 5, 4, 1, 1, 3, 2, 6 };
		test_random_access_range<int> r(a);
		VERIFY(false == ranges::is_heap(r));
	}
	{
		int a[] { 9, 9, 7, 3, 4, 3, 2 };
		test_random_access_range<int> r(a);
		VERIFY(true  == ranges::is_heap(r));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		std::vector<int> a { 9, 9, 7, 3, 4, 3, 2 };
		VERIFY(true  == ranges::is_heap(a));
	}
	{
		std::vector<int> a { 9, 7, 7, 8, 4, 3, 2 };
		VERIFY(false == ranges::is_heap(a));
	}
	{
		std::vector<int> a { 3, 2, 1 };
		VERIFY(true  == ranges::is_heap(a, [](int x, int y){return x < y;}));
	}
	{
		std::vector<int> a { 1, 2, 3 };
		VERIFY(false == ranges::is_heap(a, [](int x, int y){return x < y;}));
	}
	{
		std::vector<int> a { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		VERIFY(true  == ranges::is_heap(a, [](int x, int y){return x < y;}));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIsHeapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_is_heap_test

}	// namespace hamon_algorithm_test
