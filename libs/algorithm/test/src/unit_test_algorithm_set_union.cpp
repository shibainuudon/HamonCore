/**
 *	@file	unit_test_algorithm_set_union.cpp
 *
 *	@brief	set_union のテスト
 */

#include <hamon/algorithm/set_union.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace set_union_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool SetUnionTest1()
{
	{
		const int a[] { 1, 2, 3, 4 };
		const int b[] { 4, 5, 6 };
		int c[6]{};
		auto ret = hamon::set_union(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			hamon::begin(c));

		VERIFY(ret == hamon::next(hamon::begin(c), 6));

		VERIFY(1 == c[0]);
		VERIFY(2 == c[1]);
		VERIFY(3 == c[2]);
		VERIFY(4 == c[3]);
		VERIFY(5 == c[4]);
		VERIFY(6 == c[5]);
	}
	return true;
}

inline HAMON_CXX17_CONSTEXPR bool SetUnionTest2()
{
	{
		const int a[] { 1, 2, 3, 4 };
		const std::array<int, 4> b {{ 3, 4, 5, 6 }};
		int c[6]{};
		auto ret = hamon::set_union(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			hamon::begin(c));

		VERIFY(ret == hamon::next(hamon::begin(c), 6));

		VERIFY(1 == c[0]);
		VERIFY(2 == c[1]);
		VERIFY(3 == c[2]);
		VERIFY(4 == c[3]);
		VERIFY(5 == c[4]);
		VERIFY(6 == c[5]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, SetUnionTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SetUnionTest1());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(SetUnionTest2());

	{
		const std::array<int, 4> a {{ 6, 4, 2, 0 }};
		const std::vector<int> b { 5, 3, 1 };
		std::list<int> c;
		auto ret = hamon::set_union(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c),
			hamon::greater<>());

		(void)ret;

		auto it = c.begin();
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == c.end());
	}
	{
		const std::list<int> a { 5, 6, 7 };
		const int b[] { 1, 2, 3 };
		std::vector<int> c;
		auto ret = hamon::set_union(
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
		auto ret = hamon::set_union(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_TRUE(c.empty());
	}
}

#undef VERIFY

}	// namespace set_union_test

}	// namespace hamon_algorithm_test
