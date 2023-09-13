/**
 *	@file	unit_test_algorithm_ranges_is_heap_until.cpp
 *
 *	@brief	ranges::is_heap_until のテスト
 */

#include <hamon/algorithm/ranges/is_heap_until.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_is_heap_until_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int a[] { 1, 2, 3 };
		auto ret = ranges::is_heap_until(a, a+3);
		VERIFY(ret == a+1);
	}
	{
		int a[] { 1, 2, 3 };
		auto ret = ranges::is_heap_until(a, a+3, ranges::greater{});
		VERIFY(ret == a+3);
	}
	{
		int a[] { 3, 2, 1 };
		auto ret = ranges::is_heap_until(a);
		VERIFY(ret == a+3);
	}
	{
		int a[] { 3, 2, 1 };
		auto ret = ranges::is_heap_until(a, ranges::greater{});
		VERIFY(ret == a+1);
	}
	{
		int a[] { 9, 5, 4, 1, 1, 3, 2, 6 };
		test_random_access_range<int> r(a);
		auto ret = ranges::is_heap_until(r);
		VERIFY(ret == ranges::next(r.begin(), 7));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		hamon::vector<int> a { 9, 9, 7, 3, 4, 3, 2 };
		auto ret = ranges::is_heap_until(a.begin(), a.end());
		VERIFY(ret == ranges::next(a.begin(), 7));
	}
	{
		hamon::vector<int> a { 9, 7, 7, 8, 4, 3, 2 };
		auto ret = ranges::is_heap_until(a.begin(), a.end());
		VERIFY(ret == ranges::next(a.begin(), 3));
	}
	{
		hamon::vector<int> a { 3, 2, 1 };
		auto ret = ranges::is_heap_until(a, [](int x, int y){return x < y;});
		VERIFY(ret == ranges::next(a.begin(), 3));
	}
	{
		hamon::vector<int> a { 1, 2, 3 };
		auto ret = ranges::is_heap_until(a, [](int x, int y){return x < y;});
		VERIFY(ret == ranges::next(a.begin(), 1));
	}
	{
		hamon::vector<int> a { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		auto ret = ranges::is_heap_until(a, [](int x, int y){return x < y;});
		VERIFY(ret == a.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIsHeapUntilTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_is_heap_until_test

}	// namespace hamon_algorithm_test
