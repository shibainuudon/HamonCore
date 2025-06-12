/**
 *	@file	unit_test_algorithm_sort.cpp
 *
 *	@brief	sort のテスト
 */

#include <hamon/algorithm/sort.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		int a[] { 3, 1, 4 };
		hamon::sort(hamon::begin(a), hamon::end(a));
		VERIFY(1 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(4 == a[2]);
	}
	{
		int a[] { 3, 1, 4 };
		hamon::sort(hamon::begin(a), hamon::end(a), hamon::greater<>());
		VERIFY(4 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(1 == a[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		hamon::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		hamon::sort(hamon::begin(a), hamon::end(a));
		VERIFY(1 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(5 == a[4]);
		VERIFY(9 == a[5]);
	}
	{
		hamon::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		hamon::sort(hamon::begin(a), hamon::end(a), hamon::greater<>());
		VERIFY(9 == a[0]);
		VERIFY(5 == a[1]);
		VERIFY(4 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(1 == a[4]);
		VERIFY(1 == a[5]);
	}
	return true;
}

inline bool test3()
{
	{
		hamon::vector<int> a { 5, 4, 1, 1, 3 };
		hamon::sort(hamon::begin(a), hamon::end(a));
		VERIFY(1 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(5 == a[4]);
	}
	{
		hamon::vector<int> a { 5, 4, 1, 1, 3 };
		hamon::sort(hamon::begin(a), hamon::end(a), hamon::greater<>());
		VERIFY(5 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(1 == a[4]);
	}
	{
		hamon::vector<int> a;
		hamon::sort(hamon::begin(a), hamon::end(a));
		VERIFY(a.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, SortTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());
	EXPECT_TRUE(test3());

}

}	// namespace sort_test

}	// namespace hamon_algorithm_test
