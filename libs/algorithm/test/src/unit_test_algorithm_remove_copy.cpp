﻿/**
 *	@file	unit_test_algorithm_remove_copy.cpp
 *
 *	@brief	remove_copy のテスト
 */

#include <hamon/algorithm/remove_copy.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace remove_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		const int a[] = {1,2,3,1,3,1,2};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 1);
		VERIFY(ret == hamon::next(hamon::begin(b), 4));
		VERIFY(2 == b[0]);
		VERIFY(3 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(2 == b[3]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		const int a[] = {1,2,3,1,3,1,2};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 0);
		VERIFY(ret == hamon::next(hamon::begin(b), 7));
		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(3 == b[4]);
		VERIFY(1 == b[5]);
		VERIFY(2 == b[6]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		const hamon::array<int, 7> a = {{1,2,3,1,3,1,2}};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 3);
		VERIFY(ret == hamon::next(hamon::begin(b), 5));
		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(1 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(2 == b[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	{
		const hamon::array<int, 4> a = {{1,1,1,1}};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 1);
		VERIFY(ret == hamon::begin(b));
	}
	return true;
}

struct Point
{
	int x;
	int y;
};

inline HAMON_CXX11_CONSTEXPR bool
operator==(Point const& lhs, Point const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline HAMON_CXX14_CONSTEXPR bool test05()
{
	{
		Point const a[] =
		{
			{1, 2},
			{2, 3},
			{1, 2},
			{1, 3},
			{1, 2},
			{3, 2},
		};
		Point b[5]{};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), {1,2});
		VERIFY(ret == hamon::next(hamon::begin(b), 3));
		VERIFY(Point{2,3} == b[0]);
		VERIFY(Point{1,3} == b[1]);
		VERIFY(Point{3,2} == b[2]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, RemoveCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());

	{
		const int a[] = {1,2,3,1,3,1,2};
		hamon::vector<int> b;
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), 1);
		(void)ret;
		EXPECT_EQ(4u, b.size());
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(2, b[3]);
	}
	{
		const hamon::array<int, 7> a = {{1,2,3,1,3,1,2}};
		hamon::list<int> b;
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), 3);
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::array<int, 4> a = {{1,1,1,1}};
		hamon::vector<int> b;
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), 1);
		(void)ret;
		EXPECT_TRUE(b.empty());
	}
	{
		const hamon::vector<int> a = {1,2,3,1,3,1,2,2};
		hamon::array<int, 10> b {{}};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 2);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 5));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(1, b[4]);
	}
	{
		const hamon::vector<int> a;
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 2);
		EXPECT_TRUE(ret == hamon::begin(b));
	}
	{
		const hamon::list<int> a = {1,2,3,1,3,1,2,1,1};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 2);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 7));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(1, b[4]);
		EXPECT_EQ(1, b[5]);
		EXPECT_EQ(1, b[6]);
	}
	{
		const hamon::list<int> a;
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 0);
		EXPECT_TRUE(ret == hamon::begin(b));
	}
}

#undef VERIFY

}	// namespace remove_copy_test

}	// namespace hamon_algorithm_test
