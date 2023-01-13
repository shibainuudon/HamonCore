/**
 *	@file	unit_test_algorithm_copy_n.cpp
 *
 *	@brief	copy_n のテスト
 */

#include <hamon/algorithm/copy_n.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace copy_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool CopyNArrayTest()
{
	{
		const int a1[] { 1, 2, 3 };
		int a2[3]{};

		auto it = hamon::copy_n(hamon::begin(a1), 3, hamon::begin(a2));

		VERIFY(1 == a2[0]);
		VERIFY(2 == a2[1]);
		VERIFY(3 == a2[2]);
		VERIFY(it == hamon::end(a2));
	}
	{
		const int a1[] { 1, 2, 3 };
		int a2[3]{};

		auto it = hamon::copy_n(hamon::begin(a1), 2, hamon::begin(a2));

		VERIFY(1 == a2[0]);
		VERIFY(2 == a2[1]);
		VERIFY(0 == a2[2]);
		VERIFY(it == hamon::begin(a2) + 2);
	}
	{
		char a1[]{ 1, 2, 3 };

		auto it = hamon::copy_n(hamon::begin(a1)+1, 2, hamon::begin(a1));

		VERIFY(2 == a1[0]);
		VERIFY(3 == a1[1]);
		VERIFY(3 == a1[2]);
		VERIFY(it == hamon::begin(a1) + 2);
	}

	return true;
}

inline HAMON_CXX17_CONSTEXPR bool CopyNStdArrayTest()
{
	{
		const std::array<int, 4> a1 {{ 4, 5, 6, 7 }};
		int a2[5] {{}};

		auto it = hamon::copy_n(hamon::begin(a1), 4, hamon::begin(a2));

		VERIFY(4 == a2[0]);
		VERIFY(5 == a2[1]);
		VERIFY(6 == a2[2]);
		VERIFY(7 == a2[3]);
		VERIFY(0 == a2[4]);
		VERIFY(it == hamon::begin(a2) + 4);
	}
	{
		const std::array<int, 4> a1 {{ 4, 5, 6, 7 }};
		int a2[3] {{}};

		auto it = hamon::copy_n(hamon::begin(a1), 1, hamon::begin(a2));

		VERIFY(4 == a2[0]);
		VERIFY(0 == a2[1]);
		VERIFY(0 == a2[2]);
		VERIFY(it == hamon::begin(a2) + 1);
	}

	return true;
}

GTEST_TEST(AlgorithmTest, CopyNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyNArrayTest());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(CopyNStdArrayTest());

	{
		const std::vector<int> v { 5, 6, 7, 8, 9 };
		std::list<int> l;

		hamon::copy_n(hamon::begin(v), 5, std::back_inserter(l));

		auto it = l.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_EQ(8, *it++);
		EXPECT_EQ(9, *it++);
		EXPECT_TRUE(it == l.end());
	}
	{
		const std::list<int> a { 1, 2, 3 };
		std::list<int> b;

		hamon::copy_n(hamon::begin(a), a.size(), std::back_inserter(b));

		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == b.end());
	}
}

#undef VERIFY

}	// namespace copy_n_test

}	// namespace hamon_algorithm_test
