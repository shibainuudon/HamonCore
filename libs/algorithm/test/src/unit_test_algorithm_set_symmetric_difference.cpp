/**
 *	@file	unit_test_algorithm_set_symmetric_difference.cpp
 *
 *	@brief	set_symmetric_difference のテスト
 */

#include <hamon/algorithm/set_symmetric_difference.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace set_symmetric_difference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool SetSymmetricDifferenceTest1()
{
	{
		const int a[] { 1, 2, 3, 4 };
		const int b[] { 4, 5, 6 };
		int c[5]{};
		auto ret = hamon::set_symmetric_difference(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			hamon::begin(c));

		VERIFY(ret == hamon::next(hamon::begin(c), 5));

		VERIFY(1 == c[0]);
		VERIFY(2 == c[1]);
		VERIFY(3 == c[2]);
		VERIFY(5 == c[3]);
		VERIFY(6 == c[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool SetSymmetricDifferenceTest2()
{
	{
		const int a[] { 1, 2, 3, 4 };
		const hamon::array<int, 4> b {{ 2, 4, 5, 6 }};
		int c[6]{};
		auto ret = hamon::set_symmetric_difference(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			hamon::begin(c));

		VERIFY(ret == hamon::next(hamon::begin(c), 4));

		VERIFY(1 == c[0]);
		VERIFY(3 == c[1]);
		VERIFY(5 == c[2]);
		VERIFY(6 == c[3]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, SetSymmetricDifferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SetSymmetricDifferenceTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SetSymmetricDifferenceTest2());

	{
		const hamon::array<int, 4> a {{ 6, 5, 2, 1 }};
		const hamon::vector<int> b { 5, 3, 1 };
		hamon::list<int> c;
		auto ret = hamon::set_symmetric_difference(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c),
			hamon::greater<>());

		(void)ret;

		auto it = c.begin();
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it == c.end());
	}
	{
		const int a[] { 1, 2, 3 };
		const hamon::list<int> b { 1, 2, 3 };
		hamon::vector<int> c;
		auto ret = hamon::set_symmetric_difference(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_TRUE(c.empty());
	}
	{
		const hamon::list<int> a { 5, 6, 7 };
		const int b[] { 1, 2, 3 };
		hamon::vector<int> c;
		auto ret = hamon::set_symmetric_difference(
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
		const hamon::vector<int> a;
		const hamon::list<int> b;
		hamon::vector<int> c;
		auto ret = hamon::set_symmetric_difference(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b),
			std::back_inserter(c));

		(void)ret;

		EXPECT_TRUE(c.empty());
	}
}

#undef VERIFY

}	// namespace set_symmetric_difference_test

}	// namespace hamon_algorithm_test
