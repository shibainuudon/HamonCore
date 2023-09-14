/**
 *	@file	unit_test_algorithm_swap_ranges.cpp
 *
 *	@brief	swap_ranges のテスト
 */

#include <hamon/algorithm/swap_ranges.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace swap_ranges_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool SwapRangesTestArray()
{
	int a1[] = {1, 2, 3};
	int a2[] = {4, 5, 6};

	{
		auto it = hamon::swap_ranges(hamon::begin(a1), hamon::end(a1), hamon::begin(a2));
		VERIFY(4 == a1[0]);
		VERIFY(5 == a1[1]);
		VERIFY(6 == a1[2]);
		VERIFY(1 == a2[0]);
		VERIFY(2 == a2[1]);
		VERIFY(3 == a2[2]);
		VERIFY(it == hamon::end(a2));
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool SwapRangesTestStdArray()
{
	hamon::array<int, 3> a3 {{ 7, 8, 9}};
	hamon::array<int, 3> a4 {{10,11,12}};

	{
		auto it = hamon::swap_ranges(hamon::begin(a3), hamon::end(a3), hamon::begin(a4));
		VERIFY(10 == a3[0]);
		VERIFY(11 == a3[1]);
		VERIFY(12 == a3[2]);
		VERIFY( 7 == a4[0]);
		VERIFY( 8 == a4[1]);
		VERIFY( 9 == a4[2]);
		VERIFY(it == hamon::end(a4));
	}

	return true;
}

GTEST_TEST(AlgorithmTest, SwapRangesTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SwapRangesTestArray());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SwapRangesTestStdArray());

	int a1[] = {1, 2, 3};
	int a2[] = {4, 5, 6};
	hamon::array<int, 3> a3 {{ 7, 8, 9}};
	hamon::array<int, 3> a4 {{10,11,12}};
	hamon::vector<int> v1{13,14,15};
	hamon::vector<int> v2{16,17,18};
	hamon::list<int> l1{19,20,21};
	hamon::list<int> l2{22,23,24};

	{
		auto it = hamon::swap_ranges(hamon::begin(a1), hamon::end(a1), hamon::begin(a2));
		EXPECT_EQ( 4, a1[0]);
		EXPECT_EQ( 5, a1[1]);
		EXPECT_EQ( 6, a1[2]);
		EXPECT_EQ( 1, a2[0]);
		EXPECT_EQ( 2, a2[1]);
		EXPECT_EQ( 3, a2[2]);
		EXPECT_TRUE(it == hamon::end(a2));
	}
	{
		auto it = hamon::swap_ranges(hamon::begin(a3), hamon::end(a3), hamon::begin(a4));
		EXPECT_EQ(10, a3[0]);
		EXPECT_EQ(11, a3[1]);
		EXPECT_EQ(12, a3[2]);
		EXPECT_EQ( 7, a4[0]);
		EXPECT_EQ( 8, a4[1]);
		EXPECT_EQ( 9, a4[2]);
		EXPECT_TRUE(it == hamon::end(a4));
	}
	{
		auto it = hamon::swap_ranges(hamon::begin(v1), hamon::end(v1), hamon::begin(v2));
		EXPECT_EQ(16, v1[0]);
		EXPECT_EQ(17, v1[1]);
		EXPECT_EQ(18, v1[2]);
		EXPECT_EQ(13, v2[0]);
		EXPECT_EQ(14, v2[1]);
		EXPECT_EQ(15, v2[2]);
		EXPECT_TRUE(it == hamon::end(v2));
	}
	{
		auto it = hamon::swap_ranges(hamon::begin(l1), hamon::end(l1), hamon::begin(l2));
		{
			auto i = l1.begin();
			EXPECT_EQ(22, *i++);
			EXPECT_EQ(23, *i++);
			EXPECT_EQ(24, *i++);
		}
		{
			auto i = l2.begin();
			EXPECT_EQ(19, *i++);
			EXPECT_EQ(20, *i++);
			EXPECT_EQ(21, *i++);
		}
		EXPECT_TRUE(it == hamon::end(l2));
	}
	{
		auto it = hamon::swap_ranges(hamon::begin(a1), hamon::end(a1), hamon::begin(a3));
		EXPECT_EQ(10, a1[0]);
		EXPECT_EQ(11, a1[1]);
		EXPECT_EQ(12, a1[2]);
		EXPECT_EQ( 4, a3[0]);
		EXPECT_EQ( 5, a3[1]);
		EXPECT_EQ( 6, a3[2]);
		EXPECT_TRUE(it == hamon::end(a3));
	}
	{
		auto it = hamon::swap_ranges(hamon::begin(a1), hamon::end(a1), hamon::begin(v1));
		EXPECT_EQ(16, a1[0]);
		EXPECT_EQ(17, a1[1]);
		EXPECT_EQ(18, a1[2]);
		EXPECT_EQ(10, v1[0]);
		EXPECT_EQ(11, v1[1]);
		EXPECT_EQ(12, v1[2]);
		EXPECT_TRUE(it == hamon::end(v1));
	}
	{
		auto it = hamon::swap_ranges(hamon::begin(a1), hamon::end(a1), hamon::begin(l1));
		EXPECT_EQ(22, a1[0]);
		EXPECT_EQ(23, a1[1]);
		EXPECT_EQ(24, a1[2]);
		{
			auto i = l1.begin();
			EXPECT_EQ(16, *i++);
			EXPECT_EQ(17, *i++);
			EXPECT_EQ(18, *i++);
		}
		EXPECT_TRUE(it == hamon::end(l1));
	}
	{
		auto it = hamon::swap_ranges(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), hamon::end(a2) - 1);
		EXPECT_EQ( 1, a1[0]);
		EXPECT_EQ( 2, a1[1]);
		EXPECT_EQ(24, a1[2]);
		EXPECT_EQ(22, a2[0]);
		EXPECT_EQ(23, a2[1]);
		EXPECT_EQ( 3, a2[2]);
		EXPECT_TRUE(it == hamon::end(a2) - 1);
	}
	{
		auto it = hamon::swap_ranges(hamon::begin(v2), hamon::end(v2) - 1, hamon::begin(l2), hamon::end(l2));
		EXPECT_EQ(19, v2[0]);
		EXPECT_EQ(20, v2[1]);
		EXPECT_EQ(15, v2[2]);
		{
			auto i = l2.begin();
			EXPECT_EQ(13, *i++);
			EXPECT_EQ(14, *i++);
			EXPECT_TRUE(it == i);
			EXPECT_EQ(21, *i++);
		}
	}
}

#undef VERIFY

}	// namespace swap_ranges_test

}	// namespace hamon_algorithm_test
