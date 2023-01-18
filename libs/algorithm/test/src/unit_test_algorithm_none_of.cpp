/**
 *	@file	unit_test_algorithm_none_of.cpp
 *
 *	@brief	none_of のテスト
 */

#include <hamon/algorithm/none_of.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace none_of_test
{

HAMON_CONSTEXPR bool pred1(int x)
{
	return x == 1;
}
HAMON_CONSTEXPR bool pred2(int x)
{
	return x < 0;
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
		return x > 3;
	}
};

GTEST_TEST(AlgorithmTest, NoneOfTest)
{
	HAMON_STATIC_CONSTEXPR int a1[] {0,1,2};
	HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::none_of(hamon::begin(a1), hamon::end(a1), pred1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::none_of(hamon::begin(a1), hamon::end(a1), pred2));
	HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::none_of(hamon::begin(a1), hamon::end(a1), pred3()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::none_of(hamon::begin(a1), hamon::end(a1), pred4()));

	HAMON_STATIC_CONSTEXPR std::array<int, 8> a2{{2, 4, 4, 8, 6, 4, 0, 6}};
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE (hamon::none_of(hamon::begin(a2), hamon::end(a2), pred1));
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE (hamon::none_of(hamon::begin(a2), hamon::end(a2), pred2));
	HAMON_CXX17_CONSTEXPR_EXPECT_FALSE(hamon::none_of(hamon::begin(a2), hamon::end(a2), pred3()));
	HAMON_CXX17_CONSTEXPR_EXPECT_FALSE(hamon::none_of(hamon::begin(a2), hamon::end(a2), pred4()));

	const std::vector<int> v1 {7, 8, 9};
	EXPECT_TRUE (hamon::none_of(hamon::begin(v1), hamon::end(v1), pred1));
	EXPECT_TRUE (hamon::none_of(hamon::begin(v1), hamon::end(v1), pred2));
	EXPECT_FALSE(hamon::none_of(hamon::begin(v1), hamon::end(v1), pred4()));
	EXPECT_FALSE(hamon::none_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x == 7; }));
	EXPECT_FALSE(hamon::none_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x == 9; }));
	EXPECT_TRUE (hamon::none_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x == 10; }));

	const std::vector<int> v2;
	EXPECT_TRUE (hamon::none_of(hamon::begin(v2), hamon::end(v2), pred1));
	EXPECT_TRUE (hamon::none_of(hamon::begin(v2), hamon::end(v2), [](int) { return true; }));
	EXPECT_TRUE (hamon::none_of(hamon::begin(v2), hamon::end(v2), [](int) { return false; }));

	const std::list<int> l1 {0,1,2};
	EXPECT_FALSE(hamon::none_of(hamon::begin(l1), hamon::end(l1), pred1));
	EXPECT_TRUE (hamon::none_of(hamon::begin(l1), hamon::end(l1), pred2));
	EXPECT_FALSE(hamon::none_of(hamon::begin(l1), hamon::end(l1), pred3()));
	EXPECT_TRUE (hamon::none_of(hamon::begin(l1), hamon::end(l1), pred4()));
	EXPECT_FALSE(hamon::none_of(hamon::begin(l1), hamon::end(l1), [](int x) { return x == 0; }));
	EXPECT_TRUE (hamon::none_of(hamon::begin(l1), hamon::end(l1), [](int x) { return x == 3; }));
}

}	// namespace none_of_test

}	// namespace hamon_algorithm_test
