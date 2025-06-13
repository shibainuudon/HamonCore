/**
 *	@file	unit_test_algorithm_inplace_merge.cpp
 *
 *	@brief	inplace_merge のテスト
 */

#include <hamon/algorithm/inplace_merge.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace inplace_merge_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		int a[] { 1,4,5,  2,3,6 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 3, hamon::end(a));

		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(5 == a[4]);
		VERIFY(6 == a[5]);
	}
	{
		int a[] { 5,4,1,  6,3,2 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 3, hamon::end(a), hamon::greater<>());

		VERIFY(6 == a[0]);
		VERIFY(5 == a[1]);
		VERIFY(4 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(1 == a[5]);
	}
	{
		int a[] { 1, 2, 3 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a), hamon::end(a));

		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
	}
	{
		int a[] { 3, 2, 1 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a), hamon::end(a), hamon::greater<>());

		VERIFY(3 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(1 == a[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		hamon::array<int, 10> a {{ 1,2,5,7,  2,2,3,3,5,6 }};

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 4, hamon::end(a));

		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(2 == a[3]);
		VERIFY(3 == a[4]);
		VERIFY(3 == a[5]);
		VERIFY(5 == a[6]);
		VERIFY(5 == a[7]);
		VERIFY(6 == a[8]);
		VERIFY(7 == a[9]);
	}
	{
		hamon::array<int, 10> a {{ 7,5,2,1,  6,5,3,3,2,2 }};

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 4, hamon::end(a), hamon::greater<>());

		VERIFY(7 == a[0]);
		VERIFY(6 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(5 == a[3]);
		VERIFY(3 == a[4]);
		VERIFY(3 == a[5]);
		VERIFY(2 == a[6]);
		VERIFY(2 == a[7]);
		VERIFY(2 == a[8]);
		VERIFY(1 == a[9]);
	}
	{
		hamon::array<int, 2> a {{ 3, 1 }};

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 1, hamon::end(a));

		VERIFY(1 == a[0]);
		VERIFY(3 == a[1]);
	}
	{
		hamon::array<int, 2> a {{ 1, 3 }};

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 1, hamon::end(a), hamon::greater<>());

		VERIFY(3 == a[0]);
		VERIFY(1 == a[1]);
	}
	return true;
}

inline bool test3()
{
	{
		hamon::vector<int> a { 1,2,4,5,6,  3 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 5, hamon::end(a));

		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(5 == a[4]);
		VERIFY(6 == a[5]);
	}
	{
		hamon::vector<int> a { 6,5,4,2,1,  3 };

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a) + 5, hamon::end(a), hamon::greater<>());

		VERIFY(6 == a[0]);
		VERIFY(5 == a[1]);
		VERIFY(4 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(1 == a[5]);
	}
	{
		hamon::vector<int> a;

		hamon::inplace_merge(hamon::begin(a), hamon::begin(a), hamon::end(a));

		VERIFY(a.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, InplaceMergeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());
	EXPECT_TRUE(test3());
}

}	// namespace inplace_merge_test

}	// namespace hamon_algorithm_test
