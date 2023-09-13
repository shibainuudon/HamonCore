/**
 *	@file	unit_test_algorithm_push_heap.cpp
 *
 *	@brief	push_heap のテスト
 */

#include <hamon/algorithm/push_heap.hpp>
#include <hamon/algorithm/make_heap.hpp>
#include <hamon/algorithm/is_heap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace push_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool PushHeapTest1()
{
	{
		int a[] { 2, 0, 3, 1, 4, 1 };
		auto first = hamon::begin(a);
		auto last  = first + 1;

		hamon::push_heap(first, last);
		VERIFY(hamon::is_heap(first, last));
		++last;
		VERIFY(2 == a[0]);

		hamon::push_heap(first, last);
		VERIFY(hamon::is_heap(first, last));
		++last;
		VERIFY(2 == a[0]);
		VERIFY(0 == a[1]);

		hamon::push_heap(first, last);
		VERIFY(hamon::is_heap(first, last));
		++last;
		VERIFY(3 == a[0]);
		VERIFY(0 == a[1]);
		VERIFY(2 == a[2]);

		hamon::push_heap(first, last);
		VERIFY(hamon::is_heap(first, last));
		++last;
		VERIFY(3 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(0 == a[3]);

		hamon::push_heap(first, last);
		VERIFY(hamon::is_heap(first, last));
		++last;
		VERIFY(4 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(0 == a[3]);
		VERIFY(1 == a[4]);

		hamon::push_heap(first, last);
		VERIFY(hamon::is_heap(first, last));
		VERIFY(4 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(0 == a[3]);
		VERIFY(1 == a[4]);
		VERIFY(1 == a[5]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, PushHeapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PushHeapTest1());

	{
		hamon::vector<int> a { 3, 1, 4 };

		hamon::make_heap(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(3, a[2]);

		a.push_back(2);
		hamon::push_heap(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);

		a.push_back(5);
		hamon::push_heap(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);

		a.push_back(0);
		hamon::push_heap(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(0, a[5]);

		a.push_back(4);
		hamon::push_heap(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(0, a[5]);
		EXPECT_EQ(3, a[6]);
	}
	{
		hamon::vector<int> a { 3, 2, 1 };

		hamon::make_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);

		a.push_back(2);
		hamon::push_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(2, a[3]);

		a.push_back(3);
		hamon::push_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(3, a[4]);

		a.push_back(1);
		hamon::push_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(3, a[5]);

		a.push_back(0);
		hamon::push_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(3, a[5]);
		EXPECT_EQ(1, a[6]);
	}
}

#undef VERIFY

}	// namespace push_heap_test

}	// namespace hamon_algorithm_test
