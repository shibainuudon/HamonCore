/**
 *	@file	unit_test_algorithm_replace_copy_if.cpp
 *
 *	@brief	replace_copy_if のテスト
 */

#include <hamon/algorithm/replace_copy_if.hpp>
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

namespace replace_copy_if_test
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

HAMON_CONSTEXPR bool pred1(int a)
{
	return a == 1;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int a) const
	{
		return a == 2;
	}
};

struct pred3
{
	HAMON_CONSTEXPR bool operator()(Point const& p) const
	{
		return p == Point{1,2};
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		const int a[] { 3,1,2,1,2 };
		int b[7]{};
		auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), pred1, 4);
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

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		const int a[] { 3,1,2,1,2 };
		hamon::array<int, 5> b{};
		auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), pred2(), 5);
		VERIFY(ret == hamon::next(hamon::begin(b), 5));
		VERIFY(3 == b[0]);
		VERIFY(1 == b[1]);
		VERIFY(5 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(5 == b[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	Point const a[]
	{
		{1, 1}, {1, 2}, {1, 2}, {1, 3},
	};
	Point b[4]{};

	auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), pred3{}, {2,1});
	VERIFY(ret == hamon::end(b));
	VERIFY(Point{1, 1} == b[0]);
	VERIFY(Point{2, 1} == b[1]);
	VERIFY(Point{2, 1} == b[2]);
	VERIFY(Point{1, 3} == b[3]);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, ReplaceCopyIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());

	{
		const int a[] { 3,1,2,1,2 };
		hamon::vector<int> b;
		auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), pred2(), 5);
		(void)ret;
		EXPECT_EQ(5u, b.size());
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(1, b[3]);
		EXPECT_EQ(5, b[4]);
	}
	{
		const hamon::array<int, 6> a {{ 3,1,2,1,2,3 }};
		hamon::list<int> b;
		auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), [](int x) { return x == 3; }, 5);
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
		const hamon::vector<int> a { 3,1,4,1,5,9,2 };
		hamon::array<int, 7> b{{}};
		auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int x) { return (x % 2) == 0; }, 0);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 7));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(0, b[2]);
		EXPECT_EQ(1, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(9, b[5]);
		EXPECT_EQ(0, b[6]);
	}
	{
		hamon::vector<int> a;
		int b[5] {};
		auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int x) { return x == 0; }, 10);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 0));
		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const hamon::list<int> a { 1,1,2,3,5,8,13 };
		int b[9] {};
		auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int x) { return x == 10; }, 0);
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
		hamon::list<int> a;
		hamon::vector<int> b;
		auto ret = hamon::replace_copy_if(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), [](int) { return true; }, 1);
		(void)ret;
		EXPECT_TRUE(a.empty());
		EXPECT_TRUE(b.empty());
	}
}

}	// namespace replace_copy_if_test

}	// namespace hamon_algorithm_test
