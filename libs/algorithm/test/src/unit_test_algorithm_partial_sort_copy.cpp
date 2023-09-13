/**
 *	@file	unit_test_algorithm_partial_sort_copy.cpp
 *
 *	@brief	partial_sort_copy のテスト
 */

#include <hamon/algorithm/partial_sort_copy.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace partial_sort_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool PartialSortCopyTest1()
{
	{
		const int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int b[1] {};
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::end(b));
		VERIFY(1 == b[0]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortCopyTest2()
{
	{
		const int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		hamon::array<int, 2> b {};
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::greater<>());
		VERIFY(ret == hamon::end(b));
		VERIFY(9 == b[0]);
		VERIFY(6 == b[1]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortCopyTest3()
{
	{
		const hamon::array<int, 11> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 }};
		hamon::array<int, 3> b {};
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::end(b));
		VERIFY(1 == b[0]);
		VERIFY(1 == b[1]);
		VERIFY(2 == b[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortCopyTest4()
{
	{
		const hamon::array<int, 11> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 }};
		int b[4] {};
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::greater<>());
		VERIFY(ret == hamon::end(b));
		VERIFY(9 == b[0]);
		VERIFY(6 == b[1]);
		VERIFY(5 == b[2]);
		VERIFY(5 == b[3]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartialSortCopyTest5()
{
	{
		const hamon::array<int, 10> a {{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 }};
		hamon::array<int, 10> b {};
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::end(b));
		VERIFY(0 == b[0]);
		VERIFY(1 == b[1]);
		VERIFY(2 == b[2]);
		VERIFY(3 == b[3]);
		VERIFY(4 == b[4]);
		VERIFY(5 == b[5]);
		VERIFY(6 == b[6]);
		VERIFY(7 == b[7]);
		VERIFY(8 == b[8]);
		VERIFY(9 == b[9]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, PartialSortCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortCopyTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortCopyTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortCopyTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortCopyTest4());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartialSortCopyTest5());

	{
		const int a[] { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		hamon::vector<int> b(5);
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::end(b));
		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(4, b[4]);
	}
	{
		const int a[] { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		hamon::vector<int> b(5);
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::greater<>());
		EXPECT_TRUE(ret == hamon::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(8, b[1]);
		EXPECT_EQ(7, b[2]);
		EXPECT_EQ(6, b[3]);
		EXPECT_EQ(5, b[4]);
	}
	{
		const hamon::array<int, 10> a {{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 }};
		hamon::vector<int> b(10);
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::greater<>());
		EXPECT_TRUE(ret == hamon::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(8, b[1]);
		EXPECT_EQ(7, b[2]);
		EXPECT_EQ(6, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(4, b[5]);
		EXPECT_EQ(3, b[6]);
		EXPECT_EQ(2, b[7]);
		EXPECT_EQ(1, b[8]);
		EXPECT_EQ(0, b[9]);
	}
	{
		const hamon::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int b[5];
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::end(b));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(3, b[4]);
	}
	{
		const hamon::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		hamon::array<int, 6> b;
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::greater<>());
		EXPECT_TRUE(ret == hamon::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(6, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(5, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(4, b[5]);
	}
	{
		const hamon::vector<int> a { 3, 1, 4 };
		hamon::vector<int> b(5);
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 3));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const hamon::vector<int> a { 3, 1, 4 };
		int b[5] {};
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::greater<>());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 3));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const std::list<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int b[5];
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::end(b));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(3, b[4]);
	}
	{
		const std::list<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		hamon::array<int, 6> b;
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::greater<>());
		EXPECT_TRUE(ret == hamon::end(b));
		EXPECT_EQ(9, b[0]);
		EXPECT_EQ(6, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(5, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(4, b[5]);
	}
	{
		const std::list<int> a { 3, 1, 4 };
		hamon::vector<int> b(5);
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 3));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const std::list<int> a { 3, 1, 4 };
		int b[5] {};
		auto ret = hamon::partial_sort_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::greater<>());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 3));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
}

#undef VERIFY

}	// namespace partial_sort_copy_test

}	// namespace hamon_algorithm_test
