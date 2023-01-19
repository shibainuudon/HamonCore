/**
 *	@file	unit_test_algorithm_pop_heap.cpp
 *
 *	@brief	pop_heap のテスト
 */

#include <hamon/algorithm/pop_heap.hpp>
#include <hamon/algorithm/make_heap.hpp>
#include <hamon/algorithm/is_heap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace pop_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool PopHeapTest1()
{
	int a[] { 3, 1, 4, 1, 5, 9 };

	auto first = hamon::begin(a);
	auto last  = hamon::end(a);
	hamon::make_heap(first, last);
	VERIFY(hamon::is_heap(first, last));

	VERIFY(9 == a[0]);
	VERIFY(5 == a[1]);
	VERIFY(4 == a[2]);
	VERIFY(1 == a[3]);
	VERIFY(1 == a[4]);
	VERIFY(3 == a[5]);

	hamon::pop_heap(first, last);
	--last;

	VERIFY(5 == a[0]);
	VERIFY(3 == a[1]);
	VERIFY(4 == a[2]);
	VERIFY(1 == a[3]);
	VERIFY(1 == a[4]);

	hamon::pop_heap(first, last);
	--last;

	VERIFY(4 == a[0]);
	VERIFY(3 == a[1]);
	VERIFY(1 == a[2]);
	VERIFY(1 == a[3]);

	hamon::pop_heap(first, last);
	--last;

	VERIFY(3 == a[0]);
	VERIFY(1 == a[1]);
	VERIFY(1 == a[2]);

	hamon::pop_heap(first, last);
	--last;

	VERIFY(1 == a[0]);
	VERIFY(1 == a[1]);

	hamon::pop_heap(first, last);
	--last;

	VERIFY(1 == a[0]);

	return true;
}

GTEST_TEST(AlgorithmTest, PopHeapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PopHeapTest1());

	{
		std::vector<int> a { 3, 1, 4, 1, 5, 9 };

		hamon::make_heap(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a)));

		EXPECT_EQ(9, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(3, a[5]);

		hamon::pop_heap(hamon::begin(a), hamon::end(a));
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a)));

		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(1, a[4]);

		hamon::pop_heap(hamon::begin(a), hamon::end(a));
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a)));

		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(1, a[3]);

		hamon::pop_heap(hamon::begin(a), hamon::end(a));
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a)));

		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(1, a[2]);

		hamon::pop_heap(hamon::begin(a), hamon::end(a));
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a)));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(1, a[1]);
	}
	{
		std::vector<int> a { 1, 1, 2, 2, 2, 3, 5, 9 };

		hamon::make_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));

		hamon::pop_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));

		hamon::pop_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));

		hamon::pop_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));

		hamon::pop_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));

		hamon::pop_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		a.pop_back();
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
}

#undef VERIFY

}	// namespace pop_heap_test

}	// namespace hamon_algorithm_test
