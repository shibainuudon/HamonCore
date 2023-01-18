/**
 *	@file	unit_test_algorithm_count_if.cpp
 *
 *	@brief	count_if のテスト
 */

#include <hamon/algorithm/count_if.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace count_if_test
{

HAMON_CONSTEXPR bool pred1(int x)
{
	return x == 1;
}

HAMON_CONSTEXPR bool pred2(int x)
{
	return (x % 2) == 0;
}

struct pred3
{
	HAMON_CONSTEXPR bool operator()(int x) const
	{
		return x >= 3;
	}
};

struct pred4
{
	HAMON_CONSTEXPR bool operator()(int x) const
	{
		return x < 3;
	}
};

GTEST_TEST(AlgorithmTest, CountIfTest)
{
	{
		HAMON_CONSTEXPR_OR_CONST int a[] {1, 3, 1, 2, 3, 1, 2, 2, 1};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, hamon::count_if(hamon::begin(a), hamon::end(a), pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, hamon::count_if(hamon::begin(a), hamon::end(a), pred2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, hamon::count_if(hamon::begin(a), hamon::end(a), pred3()));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(7, hamon::count_if(hamon::begin(a), hamon::end(a), pred4()));
	}
	{
		HAMON_CONSTEXPR_OR_CONST std::array<int, 21> a{ { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6 } };
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ( 2, hamon::count_if(hamon::begin(a), hamon::end(a), pred1));
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ( 8, hamon::count_if(hamon::begin(a), hamon::end(a), pred2));
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(17, hamon::count_if(hamon::begin(a), hamon::end(a), pred3()));
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ( 4, hamon::count_if(hamon::begin(a), hamon::end(a), pred4()));
	}
	{
		const std::vector<int> v{10, 20, 10, 30, 10, 20};
		EXPECT_EQ(0, hamon::count_if(hamon::begin(v), hamon::end(v), pred1));
		EXPECT_EQ(6, hamon::count_if(hamon::begin(v), hamon::end(v), pred2));
		EXPECT_EQ(6, hamon::count_if(hamon::begin(v), hamon::end(v), pred3()));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(v), hamon::end(v), pred4()));
		EXPECT_EQ(2, hamon::count_if(hamon::begin(v), hamon::end(v), [](int x) { return x == 20;}));
		EXPECT_EQ(4, hamon::count_if(hamon::begin(v), hamon::end(v), [](int x) { return x != 20;}));
	}
	{
		const std::vector<int> v;
		EXPECT_EQ(0, hamon::count_if(hamon::begin(v), hamon::end(v), pred1));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(v), hamon::end(v), pred2));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(v), hamon::end(v), pred3()));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(v), hamon::end(v), pred4()));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(v), hamon::end(v), [](int x) { return x == 0;}));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(v), hamon::end(v), [](int  ) { return true;}));
	}
	{
		const std::list<int> l{10, 20, 40, 40, 10};
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), pred1));
		EXPECT_EQ(5, hamon::count_if(hamon::begin(l), hamon::end(l), pred2));
		EXPECT_EQ(5, hamon::count_if(hamon::begin(l), hamon::end(l), pred3()));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), pred4()));
		EXPECT_EQ(3, hamon::count_if(hamon::begin(l), hamon::end(l), [](int x) { return x >= 20;}));
		EXPECT_EQ(4, hamon::count_if(hamon::begin(l), hamon::end(l), [](int x) { return x != 20;}));
	}
	{
		const std::list<int> l;
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), pred1));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), pred2));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), pred3()));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), pred4()));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), [](int x) { return x >= 20;}));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), [](int x) { return x == 0;}));
		EXPECT_EQ(0, hamon::count_if(hamon::begin(l), hamon::end(l), [](int  ) { return true;}));
	}
}

}	// namespace count_if_test

}	// namespace hamon_algorithm_test
