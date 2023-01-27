/**
 *	@file	unit_test_numeric_adjacent_difference.cpp
 *
 *	@brief	adjacent_difference のテスト
 */

#include <hamon/numeric/adjacent_difference.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_numeric_test
{

namespace adjacent_difference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		const int a[5] { 1, 2, 3, 4, 5 };
		int b[5]{};
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(ret == hamon::next(hamon::begin(b), 5));
		VERIFY(1 == b[0]);
		VERIFY(1 == b[1]);
		VERIFY(1 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(1 == b[4]);
	}
	return true;
}

inline HAMON_CXX17_CONSTEXPR bool test02()
{
	{
		const std::array<int, 4> a {{ 3, 1, 4, 1 }};
		int b[4]{};
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::plus<>());
		VERIFY(ret == hamon::next(hamon::begin(b), 4));
		VERIFY(3 == b[0]);
		VERIFY(4 == b[1]);
		VERIFY(5 == b[2]);
		VERIFY(5 == b[3]);
	}
	return true;
}

GTEST_TEST(NumericTest, AdjacentDifferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(test02());

	{
		const int a[5] { 1, 2, 3, 4, 5 };
		int b[5] { 6, 7, 8, 9, 10 };
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int x, int y) { return 2 * x - y; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 5));
		EXPECT_EQ( 1, b[0]);
		EXPECT_EQ( 3, b[1]);
		EXPECT_EQ( 4, b[2]);
		EXPECT_EQ( 5, b[3]);
		EXPECT_EQ( 6, b[4]);
	}
	{
		const std::array<int, 4> a {{ 3, 1, 4, 1 }};
		std::list<int> b;
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a), std::back_inserter(b));
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ( 3, *it++);
		EXPECT_EQ(-2, *it++);
		EXPECT_EQ( 3, *it++);
		EXPECT_EQ(-3, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::array<int, 4> a {{ 3, 1, 4, 1 }};
		std::list<int> b;
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a), std::back_inserter(b), hamon::plus<>());
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ( 3, *it++);
		EXPECT_EQ( 4, *it++);
		EXPECT_EQ( 5, *it++);
		EXPECT_EQ( 5, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::vector<int> a { -3, 2, -5 };
		std::array<int, 4> b {{}};
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a), hamon::begin(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 3));
		EXPECT_EQ(-3, b[0]);
		EXPECT_EQ( 5, b[1]);
		EXPECT_EQ(-7, b[2]);
		EXPECT_EQ( 0, b[3]);
	}
	{
		const std::list<int> a { 2, 2, 2, 2, 2 };
		std::vector<int> b;
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a), std::back_inserter(b));
		(void)ret;
		EXPECT_EQ( 2, b[0]);
		EXPECT_EQ( 0, b[1]);
		EXPECT_EQ( 0, b[2]);
		EXPECT_EQ( 0, b[3]);
		EXPECT_EQ( 0, b[4]);
	}
	{
		std::vector<int> a { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a) - 1, hamon::begin(a) + 1, hamon::plus<>());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 10));
		EXPECT_EQ( 1, a[0]);
		EXPECT_EQ( 1, a[1]);
		EXPECT_EQ( 2, a[2]);
		EXPECT_EQ( 3, a[3]);
		EXPECT_EQ( 5, a[4]);
		EXPECT_EQ( 8, a[5]);
		EXPECT_EQ(13, a[6]);
		EXPECT_EQ(21, a[7]);
		EXPECT_EQ(34, a[8]);
		EXPECT_EQ(55, a[9]);
	}
	{
		const std::vector<int> a;
		std::array<int, 3> b {{ 1, 2, 3 }};
		auto ret = hamon::adjacent_difference(hamon::begin(a), hamon::end(a), hamon::begin(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 0));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
}

#undef VERIFY

}	// namespace adjacent_difference_test

}	// namespace hamon_numeric_test
