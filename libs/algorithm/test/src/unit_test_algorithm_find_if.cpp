/**
 *	@file	unit_test_algorithm_find_if.cpp
 *
 *	@brief	find_if のテスト
 */

#include <hamon/algorithm/find_if.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace find_if_test
{

HAMON_CONSTEXPR bool pred1(int x)
{
	return x == 1;
}
HAMON_CONSTEXPR bool pred2(int x)
{
	return x > 2;
}

struct pred3
{
	HAMON_CONSTEXPR bool operator()(int x) const
	{
		return x % 2 == 0;
	}
};

struct pred4
{
	HAMON_CONSTEXPR bool operator()(int x) const
	{
		return x % 2 == 1;
	}
};

GTEST_TEST(AlgorithmTest, FindIfTest)
{
	HAMON_STATIC_CONSTEXPR int a1[] {0,1,2};
	{
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_if(hamon::begin(a1), hamon::end(a1), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a1) + 1);
	}
	{
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_if(hamon::begin(a1), hamon::end(a1), pred2);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a1));
	}
	{
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_if(hamon::begin(a1), hamon::end(a1), pred3());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a1));
	}
	{
		HAMON_CXX14_CONSTEXPR_OR_CONST auto it = hamon::find_if(hamon::begin(a1), hamon::end(a1), pred4());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a1) + 1);
	}

	HAMON_STATIC_CONSTEXPR std::array<int, 8> a2{{3, 4, 4, 5, 5, 5, 3, 6}};
	{
		HAMON_CXX17_CONSTEXPR_OR_CONST auto it = hamon::find_if(hamon::begin(a2), hamon::end(a2), pred1);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(it == hamon::end(a2));
	}
	{
		HAMON_CXX17_CONSTEXPR_OR_CONST auto it = hamon::find_if(hamon::begin(a2), hamon::end(a2), pred2);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a2));
	}
	{
		HAMON_CXX17_CONSTEXPR_OR_CONST auto it = hamon::find_if(hamon::begin(a2), hamon::end(a2), pred3());
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a2) + 1);
	}
	{
		HAMON_CXX17_CONSTEXPR_OR_CONST auto it = hamon::find_if(hamon::begin(a2), hamon::end(a2), pred4());
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(it == hamon::begin(a2));
	}

	int a3[] {0,1,2};
	{
		auto it = hamon::find_if(hamon::begin(a3), hamon::end(a3), pred3());
		EXPECT_TRUE(it == hamon::begin(a3));
		*it = 10;
	}
	{
		auto it = hamon::find_if(hamon::begin(a3), hamon::end(a3), [](int x) { return x == 2; });
		EXPECT_TRUE(it == hamon::begin(a3) + 2);
		*it = 20;
	}
	{
		auto it = hamon::find_if(hamon::begin(a3), hamon::end(a3), [](int x) { return x < 0; });
		EXPECT_TRUE(it == hamon::end(a3));
	}
	EXPECT_EQ(10, a3[0]);
	EXPECT_EQ( 1, a3[1]);
	EXPECT_EQ(20, a3[2]);

	const std::vector<int> v1 {7, 8, 9};
	{
		auto it = hamon::find_if(hamon::begin(v1), hamon::end(v1), [](int x) { return x == 7; });
		EXPECT_TRUE(it == hamon::begin(v1));
	}
	{
		auto it = hamon::find_if(hamon::begin(v1), hamon::end(v1), [](int x) { return x > 8; });
		EXPECT_TRUE(it == hamon::begin(v1) + 2);
	}
	{
		auto it = hamon::find_if(hamon::begin(v1), hamon::end(v1), [](int x) { return x == 10; });
		EXPECT_TRUE(it == hamon::end(v1));
	}

	const std::list<int> l1 {0,1,2};
	{
		auto it = hamon::find_if(hamon::begin(l1), hamon::end(l1), pred1);
		EXPECT_TRUE(it == ++hamon::begin(l1));
	}
	{
		auto it = hamon::find_if(hamon::begin(l1), hamon::end(l1), pred3());
		EXPECT_TRUE(it == hamon::begin(l1));
	}
	{
		auto it = hamon::find_if(hamon::begin(l1), hamon::end(l1), [](int x) { return x < 0; });
		EXPECT_TRUE(it == hamon::end(l1));
	}

	std::list<int> l2 {0,1,2};
	{
		auto it = hamon::find_if(hamon::begin(l2), hamon::end(l2), [](int x) { return x % 2 == 1; });
		EXPECT_TRUE(it == ++hamon::begin(l2));
		*it = 30;
	}
	{
		auto it = hamon::find_if(hamon::begin(l2), hamon::end(l2), [](int x) { return x == 10; });
		EXPECT_TRUE(it == hamon::end(l2));
	}
	{
		auto it = l2.begin();
		EXPECT_EQ( 0, *it++);
		EXPECT_EQ(30, *it++);
		EXPECT_EQ( 2, *it++);
	}
}

}	// namespace find_if_test

}	// namespace hamon_algorithm_test
