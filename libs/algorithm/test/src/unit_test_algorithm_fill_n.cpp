/**
 *	@file	unit_test_algorithm_fill_n.cpp
 *
 *	@brief	fill_n のテスト
 */

#include <hamon/algorithm/fill_n.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace fill_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool FillNTestArray()
{
	{
		int a1[3]{};
		auto it = hamon::fill_n(hamon::begin(a1), 3, 1);
		VERIFY(1 == a1[0]);
		VERIFY(1 == a1[1]);
		VERIFY(1 == a1[2]);
		VERIFY(it == hamon::end(a1));

		it = hamon::fill_n(hamon::begin(a1), 2, 2);
		VERIFY(2 == a1[0]);
		VERIFY(2 == a1[1]);
		VERIFY(1 == a1[2]);
		VERIFY(it == hamon::begin(a1) + 2);

		it = hamon::fill_n(hamon::begin(a1), 0, 3);
		VERIFY(2 == a1[0]);
		VERIFY(2 == a1[1]);
		VERIFY(1 == a1[2]);
		VERIFY(it == hamon::begin(a1));
	}

	return true;
}

inline HAMON_CXX17_CONSTEXPR bool FillNTestStdArray()
{
	{
		std::array<int, 4> a2{ { 1, 2, 3, 4 } };
		auto it = hamon::fill_n(hamon::begin(a2), 3, -1);
		VERIFY(-1 == a2[0]);
		VERIFY(-1 == a2[1]);
		VERIFY(-1 == a2[2]);
		VERIFY( 4 == a2[3]);
		VERIFY(it == hamon::begin(a2) + 3);
	}

	return true;
}

GTEST_TEST(AlgorithmTest, FillNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FillNTestArray());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(FillNTestStdArray());

	{
		std::vector<int> v1(5);
		auto it = hamon::fill_n(hamon::begin(v1), 2, 3);
		EXPECT_EQ(3, v1[0]);
		EXPECT_EQ(3, v1[1]);
		EXPECT_EQ(0, v1[2]);
		EXPECT_EQ(0, v1[3]);
		EXPECT_EQ(0, v1[4]);
		EXPECT_TRUE(it == hamon::begin(v1) + 2);
	}
	{
		std::vector<int> v2;
		hamon::fill_n(std::back_inserter(v2), 3, 11);
		EXPECT_EQ(11, v2[0]);
		EXPECT_EQ(11, v2[1]);
		EXPECT_EQ(11, v2[2]);
	}
	{
		std::list<int> l1(3);
		hamon::fill_n(hamon::begin(l1), 3, 4);
		auto it = l1.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == l1.end());
	}
	{
		std::list<int> l2;
		hamon::fill_n(std::back_inserter(l2), 2, 12);
		auto it = l2.begin();
		EXPECT_EQ(12, *it++);
		EXPECT_EQ(12, *it++);
		EXPECT_TRUE(it == l2.end());
	}
}

#undef VERIFY

}	// namespace fill_n_test

}	// namespace hamon_algorithm_test
