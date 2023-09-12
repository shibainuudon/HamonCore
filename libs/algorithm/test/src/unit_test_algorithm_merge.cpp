/**
 *	@file	unit_test_algorithm_merge.cpp
 *
 *	@brief	merge のテスト
 */

#include <hamon/algorithm/merge.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace merge_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool MergeTest1()
{
	{
		const int a[] { 1, 2, 3, 4 };
		const int b[] { 3, 4, 5, 6 };
		int c[8]{};
		auto ret = hamon::merge(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			hamon::begin(c));

		VERIFY(ret == hamon::next(hamon::begin(c), 8));

		VERIFY(1 == c[0]);
		VERIFY(2 == c[1]);
		VERIFY(3 == c[2]);
		VERIFY(3 == c[3]);
		VERIFY(4 == c[4]);
		VERIFY(4 == c[5]);
		VERIFY(5 == c[6]);
		VERIFY(6 == c[7]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool MergeTest2()
{
	{
		const int a[] { 1, 2, 3, 4 };
		const hamon::array<int, 4> b {{ 3, 4, 5, 6 }};
		int c[8]{};
		auto ret = hamon::merge(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			hamon::begin(c));

		VERIFY(ret == hamon::next(hamon::begin(c), 8));

		VERIFY(1 == c[0]);
		VERIFY(2 == c[1]);
		VERIFY(3 == c[2]);
		VERIFY(3 == c[3]);
		VERIFY(4 == c[4]);
		VERIFY(4 == c[5]);
		VERIFY(5 == c[6]);
		VERIFY(6 == c[7]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, MergeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MergeTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MergeTest2());

	{
		const hamon::array<int, 4> a {{ 6, 5, 2, 1 }};
		const std::vector<int> b { 5, 3, 1 };
		std::list<int> c;
		auto ret = hamon::merge(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c),
			hamon::greater<>());

		(void)ret;

		auto it = c.begin();
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == c.end());
	}
	{
		const int a[] { 1, 2, 3 };
		const std::list<int> b { 1, 2, 3 };
		std::vector<int> c(6);
		auto ret = hamon::merge(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			c.begin());

		EXPECT_TRUE(ret == c.end());

		EXPECT_EQ(6u, c.size());
		EXPECT_EQ(1, c[0]);
		EXPECT_EQ(1, c[1]);
		EXPECT_EQ(2, c[2]);
		EXPECT_EQ(2, c[3]);
		EXPECT_EQ(3, c[4]);
		EXPECT_EQ(3, c[5]);
	}
	{
		const std::list<int> a { 5, 6, 7 };
		const int b[] { 1, 2, 3 };
		std::vector<int> c;
		auto ret = hamon::merge(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_EQ(6u, c.size());
		EXPECT_EQ(1, c[0]);
		EXPECT_EQ(2, c[1]);
		EXPECT_EQ(3, c[2]);
		EXPECT_EQ(5, c[3]);
		EXPECT_EQ(6, c[4]);
		EXPECT_EQ(7, c[5]);
	}
	{
		const std::vector<int> a;
		const std::list<int> b;
		std::vector<int> c;
		auto ret = hamon::merge(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_TRUE(c.empty());
	}
}

#undef VERIFY

}	// namespace merge_test

}	// namespace hamon_algorithm_test
