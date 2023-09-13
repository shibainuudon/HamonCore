/**
 *	@file	unit_test_algorithm_replace_if.cpp
 *
 *	@brief	replace_if のテスト
 */

#include <hamon/algorithm/replace_if.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace replace_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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

inline HAMON_CXX14_CONSTEXPR bool ReplaceIfTest1()
{
	{
		int a[] { 3,1,2,1,2 };
		hamon::replace_if(hamon::begin(a), hamon::end(a), pred1, 4);
		VERIFY(3 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(2 == a[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ReplaceIfTest2()
{
	{
		hamon::array<int, 6> a {{ 3,1,2,1,2,3 }};
		hamon::replace_if(hamon::begin(a), hamon::end(a), pred2(), 5);
		VERIFY(3 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(5 == a[4]);
		VERIFY(3 == a[5]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, ReplaceIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIfTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReplaceIfTest2());

	{
		hamon::vector<int> a { 3,1,4,1,5,9,2 };
		hamon::replace_if(hamon::begin(a), hamon::end(a), [](int x) { return x == 2; }, 0);
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
		hamon::replace_if(hamon::begin(a), hamon::end(a), [](int) { return true; }, 0);
		EXPECT_TRUE(a.empty());
	}
	{
		std::list<int> a { 1,2,3,4,5,6 };
		hamon::replace_if(hamon::begin(a), hamon::end(a), [](int x) { return x % 2 == 0; }, 0);
		auto it = a.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::list<int> a;
		hamon::replace_if(hamon::begin(a), hamon::end(a), [](int) { return false; }, 1);
		EXPECT_TRUE(a.empty());
	}
}

#undef VERIFY

}	// namespace replace_if_test

}	// namespace hamon_algorithm_test
