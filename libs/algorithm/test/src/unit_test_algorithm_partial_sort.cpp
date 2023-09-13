/**
 *	@file	unit_test_algorithm_partial_sort.cpp
 *
 *	@brief	partial_sort のテスト
 */

#include <hamon/algorithm/partial_sort.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace partial_sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool PartialSortTest1()
{
	{
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 1), hamon::end(a));
		VERIFY(1 == a[0]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortTest2()
{
	{
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 2), hamon::end(a), hamon::greater<>());
		VERIFY(9 == a[0]);
		VERIFY(6 == a[1]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortTest3()
{
	{
		int a[] { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 5), hamon::end(a));
		VERIFY(0 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(4 == a[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortTest4()
{
	{
		int a[] { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 5), hamon::end(a), hamon::greater<>());
		VERIFY(9 == a[0]);
		VERIFY(8 == a[1]);
		VERIFY(7 == a[2]);
		VERIFY(6 == a[3]);
		VERIFY(5 == a[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortTest5()
{
	{
		hamon::array<int, 11> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 }};
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 3), hamon::end(a));
		VERIFY(1 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortTest6()
{
	{
		hamon::array<int, 11> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 }};
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 4), hamon::end(a), hamon::greater<>());
		VERIFY(9 == a[0]);
		VERIFY(6 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(5 == a[3]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortTest7()
{
	{
		hamon::array<int, 10> a {{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 }};
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 10), hamon::end(a));
		VERIFY(0 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(4 == a[4]);
		VERIFY(5 == a[5]);
		VERIFY(6 == a[6]);
		VERIFY(7 == a[7]);
		VERIFY(8 == a[8]);
		VERIFY(9 == a[9]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortTest8()
{
	{
		hamon::array<int, 10> a {{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 }};
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 10), hamon::end(a), hamon::greater<>());
		VERIFY(9 == a[0]);
		VERIFY(8 == a[1]);
		VERIFY(7 == a[2]);
		VERIFY(6 == a[3]);
		VERIFY(5 == a[4]);
		VERIFY(4 == a[5]);
		VERIFY(3 == a[6]);
		VERIFY(2 == a[7]);
		VERIFY(1 == a[8]);
		VERIFY(0 == a[9]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, PartialSortTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortTest4());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortTest5());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortTest6());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortTest7());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortTest8());

	{
		hamon::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 5), hamon::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(3, a[4]);
	}
	{
		hamon::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 6), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(6, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(5, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(4, a[5]);
	}
	{
		hamon::vector<int> a { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 1), hamon::end(a));
		EXPECT_EQ(0, a[0]);
	}
	{
		hamon::vector<int> a { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 1), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(9, a[0]);
	}
	{
		hamon::vector<int> a;
		hamon::partial_sort(hamon::begin(a), hamon::next(hamon::begin(a), 0), hamon::end(a));
		EXPECT_TRUE(a.empty());
	}
}

#undef VERIFY

}	// namespace partial_sort_test

}	// namespace hamon_algorithm_test
