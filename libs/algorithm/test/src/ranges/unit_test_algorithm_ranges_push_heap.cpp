﻿/**
 *	@file	unit_test_algorithm_ranges_push_heap.cpp
 *
 *	@brief	ranges::push_heap のテスト
 */

#include <hamon/algorithm/ranges/push_heap.hpp>
#include <hamon/algorithm/ranges/make_heap.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_push_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int a[] = { 3, 1, 4, 2, 5, 0, 4 };
		int n = 3;

		test_random_access_range<int> r0(a, a+n);
		auto it = ranges::make_heap(r0);
		VERIFY(it == r0.end());
		VERIFY(4 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(3 == a[2]);

		++n;
		test_random_access_range<int> r1(a, a+n);
		it = ranges::push_heap(r1);
		VERIFY(it == r1.end());
		VERIFY(4 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);

		++n;
		test_random_access_range<int> r2(a, a+n);
		it = ranges::push_heap(r2);
		VERIFY(it == r2.end());
		VERIFY(5 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);

		++n;
		test_random_access_range<int> r3(a, a+n);
		it = ranges::push_heap(r3);
		VERIFY(it == r3.end());
		VERIFY(5 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(0 == a[5]);

		++n;
		test_random_access_range<int> r4(a, a+n);
		it = ranges::push_heap(r4);
		VERIFY(it == r4.end());
		VERIFY(5 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(4 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(0 == a[5]);
		VERIFY(3 == a[6]);
	}
	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		hamon::vector<int> a { 3, 1, 4 };

		auto it = ranges::make_heap(a);
		VERIFY(it == a.end());
		VERIFY(4 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(3 == a[2]);

		a.push_back(2);
		it = ranges::push_heap(a);
		VERIFY(it == a.end());
		VERIFY(4 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);

		a.push_back(5);
		it = ranges::push_heap(a);
		VERIFY(it == a.end());
		VERIFY(5 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);

		a.push_back(0);
		it = ranges::push_heap(a);
		VERIFY(it == a.end());
		VERIFY(5 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(0 == a[5]);

		a.push_back(4);
		it = ranges::push_heap(a);
		VERIFY(it == a.end());
		VERIFY(5 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(4 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(0 == a[5]);
		VERIFY(3 == a[6]);
	}
	{
		hamon::vector<int> a { 3, 2, 1 };
		auto pred = ranges::greater{};

		auto it = ranges::make_heap(a, pred);
		VERIFY(it == a.end());
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);

		a.push_back(2);
		it = ranges::push_heap(a, pred);
		VERIFY(it == a.end());
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(2 == a[3]);

		a.push_back(3);
		it = ranges::push_heap(a, pred);
		VERIFY(it == a.end());
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(2 == a[3]);
		VERIFY(3 == a[4]);

		a.push_back(1);
		it = ranges::push_heap(a, pred);
		VERIFY(it == a.end());
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(1 == a[2]);
		VERIFY(2 == a[3]);
		VERIFY(3 == a[4]);
		VERIFY(3 == a[5]);

		a.push_back(0);
		it = ranges::push_heap(a, pred);
		VERIFY(it == a.end());
		VERIFY(0 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(1 == a[2]);
		VERIFY(2 == a[3]);
		VERIFY(3 == a[4]);
		VERIFY(3 == a[5]);
		VERIFY(1 == a[6]);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPushHeapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_push_heap_test

}	// namespace hamon_algorithm_test
