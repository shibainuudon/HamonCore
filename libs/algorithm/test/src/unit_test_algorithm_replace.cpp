/**
 *	@file	unit_test_algorithm_replace.cpp
 *
 *	@brief	replace のテスト
 */

#include <hamon/algorithm/replace.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace replace_test
{

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int a[] { 3,1,2,1,2 };
		hamon::replace(hamon::begin(a), hamon::end(a), 1, 4);
		VERIFY(3 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(2 == a[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		hamon::array<int, 6> a {{ 3,1,2,1,2,3 }};
		hamon::replace(hamon::begin(a), hamon::end(a), 3, 5);
		VERIFY(5 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(5 == a[5]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	Point a[]
	{
		{1, 1}, {1, 2}, {1, 2}, {1, 3},
	};

	hamon::replace(hamon::begin(a), hamon::end(a), {1,2}, {2,1});
	VERIFY(Point{1, 1} == a[0]);
	VERIFY(Point{2, 1} == a[1]);
	VERIFY(Point{2, 1} == a[2]);
	VERIFY(Point{1, 3} == a[3]);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, ReplaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());

	{
		hamon::vector<int> a { 3,1,4,1,5,9,2 };
		hamon::replace(hamon::begin(a), hamon::end(a), 2, 0);
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(9, a[5]);
		EXPECT_EQ(0, a[6]);
	}
	{
		hamon::vector<int> a;
		hamon::replace(hamon::begin(a), hamon::end(a), 2, 0);
		EXPECT_TRUE(a.empty());
	}
	{
		hamon::list<int> a { 9,1,9 };
		hamon::replace(hamon::begin(a), hamon::end(a), 9, 0);
		auto it = a.begin();
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		hamon::list<int> a;
		hamon::replace(hamon::begin(a), hamon::end(a), 0, 1);
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace replace_test

}	// namespace hamon_algorithm_test
