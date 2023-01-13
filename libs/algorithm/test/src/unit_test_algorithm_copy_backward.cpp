/**
 *	@file	unit_test_algorithm_copy_backward.cpp
 *
 *	@brief	copy_backward のテスト
 */

#include <hamon/algorithm/copy_backward.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace copy_backward_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool CopyBackwardArrayTest()
{
	{
		const int a1[] { 1, 2, 3 };
		int a2[3]{};

		auto it = hamon::copy_backward(hamon::begin(a1), hamon::end(a1), hamon::end(a2));

		VERIFY(1 == a2[0]);
		VERIFY(2 == a2[1]);
		VERIFY(3 == a2[2]);
		VERIFY(it == hamon::begin(a2));
	}
	{
		int a1[] { 1, 2, 3 };

		auto it = hamon::copy_backward(a1, a1+2, a1+3);

		VERIFY(1 == a1[0]);
		VERIFY(1 == a1[1]);
		VERIFY(2 == a1[2]);
		VERIFY(it == hamon::begin(a1)+1);
	}
	{
		short a1[] { 1, 2, 3 };

		auto it = hamon::copy_backward(a1, a1+2, a1+3);

		VERIFY(1 == a1[0]);
		VERIFY(1 == a1[1]);
		VERIFY(2 == a1[2]);
		VERIFY(it == hamon::begin(a1)+1);
	}
	{
		char a1[] { 1, 2, 3 };

		auto it = hamon::copy_backward(a1, a1+2, a1+3);

		VERIFY(1 == a1[0]);
		VERIFY(1 == a1[1]);
		VERIFY(2 == a1[2]);
		VERIFY(it == hamon::begin(a1)+1);
	}

	return true;
}

inline HAMON_CXX17_CONSTEXPR bool CopyBackwardStdArrayTest()
{
	{
		const int a1[] { 1, 2, 3 };
		std::array<int, 5> a2{{}};

		auto it = hamon::copy_backward(hamon::begin(a1), hamon::end(a1), hamon::end(a2));

		VERIFY(0 == a2[0]);
		VERIFY(0 == a2[1]);
		VERIFY(1 == a2[2]);
		VERIFY(2 == a2[3]);
		VERIFY(3 == a2[4]);
		VERIFY(it == hamon::begin(a2) + 2);
	}

	return true;
}

GTEST_TEST(AlgorithmTest, CopyBackwardTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyBackwardArrayTest());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(CopyBackwardStdArrayTest());

	{
		std::vector<int> v{ 1, 2, 3, 4, 5 };

		auto it = hamon::copy_backward(hamon::begin(v), hamon::begin(v) + 3, hamon::end(v));

		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(1, v[2]);
		EXPECT_EQ(2, v[3]);
		EXPECT_EQ(3, v[4]);
		EXPECT_TRUE(it == hamon::begin(v) + 2);
	}
	{
		const std::vector<int> v{ 1, 2, 3, 4, 5 };
		std::list<int> l{ 6, 7, 8, 9 };

		{
			auto it = hamon::copy_backward(hamon::begin(v), hamon::begin(v) + 2, hamon::end(l));
			EXPECT_TRUE(it == hamon::next(l.begin(), 2));
		}
		{
			auto it = l.begin();
			EXPECT_EQ(6, *it++);
			EXPECT_EQ(7, *it++);
			EXPECT_EQ(1, *it++);
			EXPECT_EQ(2, *it++);
			EXPECT_TRUE(it == l.end());
		}
	}
}

#undef VERIFY

}	// namespace copy_backward_test

}	// namespace hamon_algorithm_test
