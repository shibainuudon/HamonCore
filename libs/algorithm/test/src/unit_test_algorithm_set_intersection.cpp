/**
 *	@file	unit_test_algorithm_set_intersection.cpp
 *
 *	@brief	set_intersection のテスト
 */

#include <hamon/algorithm/set_intersection.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace set_intersection_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool SetIntersectionTest1()
{
	{
		const int a[] { 1, 2, 3, 4 };
		const int b[] { 0, 3, 4 };
		int c[6]{};
		auto ret = hamon::set_intersection(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			hamon::begin(c));

		VERIFY(ret == hamon::next(hamon::begin(c), 2));

		VERIFY(3 == c[0]);
		VERIFY(4 == c[1]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool SetIntersectionTest2()
{
	{
		const int a[] { 1, 2, 3, 4 };
		const hamon::array<int, 4> b {{ 2, 4, 5, 6 }};
		int c[6]{};
		auto ret = hamon::set_intersection(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			hamon::begin(c));

		VERIFY(ret == hamon::next(hamon::begin(c), 2));

		VERIFY(2 == c[0]);
		VERIFY(4 == c[1]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, SetIntersectionTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SetIntersectionTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SetIntersectionTest2());

	{
		const hamon::array<int, 4> a {{ 6, 5, 2, 1 }};
		const hamon::vector<int> b { 5, 3, 1 };
		std::list<int> c;
		auto ret = hamon::set_intersection(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c),
			hamon::greater<>());

		(void)ret;

		auto it = c.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == c.end());
	}
	{
		const int a[] { 1, 2, 3 };
		const std::list<int> b { 1, 2, 3 };
		hamon::vector<int> c;
		auto ret = hamon::set_intersection(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_EQ(3u, c.size());
		EXPECT_EQ(1, c[0]);
		EXPECT_EQ(2, c[1]);
		EXPECT_EQ(3, c[2]);
	}
	{
		const std::list<int> a { 5, 6, 7 };
		const int b[] { 1, 2, 3 };
		hamon::vector<int> c;
		auto ret = hamon::set_intersection(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_TRUE(c.empty());
	}
	{
		const hamon::vector<int> a;
		const std::list<int> b;
		hamon::vector<int> c;
		auto ret = hamon::set_intersection(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_TRUE(c.empty());
	}
}

#undef VERIFY

}	// namespace set_intersection_test

}	// namespace hamon_algorithm_test
