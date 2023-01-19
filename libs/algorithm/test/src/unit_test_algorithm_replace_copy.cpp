/**
 *	@file	unit_test_algorithm_replace_copy.cpp
 *
 *	@brief	replace_copy のテスト
 */

#include <hamon/algorithm/replace_copy.hpp>
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

namespace replace_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool ReplaceCopyTest1()
{
	{
		const int a[] { 3,1,2,1,2 };
		int b[7]{};
		auto ret = hamon::replace_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 1, 4);
		VERIFY(ret == hamon::next(hamon::begin(b), 5));
		VERIFY(3 == b[0]);
		VERIFY(4 == b[1]);
		VERIFY(2 == b[2]);
		VERIFY(4 == b[3]);
		VERIFY(2 == b[4]);
		VERIFY(0 == b[5]);
		VERIFY(0 == b[6]);
	}
	return true;
}

inline HAMON_CXX17_CONSTEXPR bool ReplaceCopyTest2()
{
	{
		const int a[] { 3,1,2,1,2 };
		std::array<int, 5> b {};
		auto ret = hamon::replace_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 2, 5);
		VERIFY(ret == hamon::next(hamon::begin(b), 5));
		VERIFY(3 == b[0]);
		VERIFY(1 == b[1]);
		VERIFY(5 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(5 == b[4]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, ReplaceCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceCopyTest1());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(ReplaceCopyTest2());

	{
		const int a[] { 3,1,2,1,2 };
		std::vector<int> b;
		auto ret = hamon::replace_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b), 2, 5);
		(void)ret;
		EXPECT_EQ(5u, b.size());
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(1, b[3]);
		EXPECT_EQ(5, b[4]);
	}
	{
		const std::array<int, 6> a {{ 3,1,2,1,2,3 }};
		std::list<int> b;
		auto ret = hamon::replace_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b), 3, 5);
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::vector<int> a { 3,1,4,1,5,9,2 };
		std::array<int, 7> b{{}};
		auto ret = hamon::replace_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 2, 0);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 7));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(1, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(9, b[5]);
		EXPECT_EQ(0, b[6]);
	}
	{
		std::vector<int> a;
		int b[5] {};
		auto ret = hamon::replace_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 0, 10);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 0));
		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const std::list<int> a { 1,1,2,3,5,8,13 };
		int b[9] {};
		auto ret = hamon::replace_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 9, 0);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 7));
		EXPECT_EQ( 1, b[0]);
		EXPECT_EQ( 1, b[1]);
		EXPECT_EQ( 2, b[2]);
		EXPECT_EQ( 3, b[3]);
		EXPECT_EQ( 5, b[4]);
		EXPECT_EQ( 8, b[5]);
		EXPECT_EQ(13, b[6]);
		EXPECT_EQ( 0, b[7]);
		EXPECT_EQ( 0, b[8]);
	}
	{
		std::list<int> a;
		std::vector<int> b;
		auto ret = hamon::replace_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b), 0, 1);
		(void)ret;
		EXPECT_TRUE(a.empty());
		EXPECT_TRUE(b.empty());
	}
}

#undef VERIFY

}	// namespace replace_copy_test

}	// namespace hamon_algorithm_test
