/**
 *	@file	unit_test_algorithm_all_of.cpp
 *
 *	@brief	all_of のテスト
 */

#include <hamon/algorithm/all_of.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace all_of_test
{

HAMON_CONSTEXPR bool pred1(int x)
{
	return x == 1;
}
HAMON_CONSTEXPR bool pred2(int x)
{
	return x >= 0;
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
		return x < 3;
	}
};

GTEST_TEST(AlgorithmTest, AllOfTest)
{
	HAMON_CXX11_CONSTEXPR int a1[] {0,1,2};
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::all_of(hamon::begin(a1), hamon::end(a1), pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::all_of(hamon::begin(a1), hamon::end(a1), pred2));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::all_of(hamon::begin(a1), hamon::end(a1), pred3()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::all_of(hamon::begin(a1), hamon::end(a1), pred4()));

	HAMON_CXX11_CONSTEXPR hamon::array<int, 8> a2{{2, 4, 4, 8, 6, 4, 0, 6}};
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::all_of(hamon::begin(a2), hamon::end(a2), pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::all_of(hamon::begin(a2), hamon::end(a2), pred2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::all_of(hamon::begin(a2), hamon::end(a2), pred3()));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::all_of(hamon::begin(a2), hamon::end(a2), pred4()));

	const std::vector<int> v1 {7, 8, 9};
	EXPECT_FALSE(hamon::all_of(hamon::begin(v1), hamon::end(v1), pred1));
	EXPECT_TRUE (hamon::all_of(hamon::begin(v1), hamon::end(v1), pred2));
	EXPECT_TRUE (hamon::all_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x >= 7; }));
	EXPECT_FALSE(hamon::all_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x > 8; }));
	EXPECT_FALSE(hamon::all_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x < 9; }));

	const std::vector<int> v2;
	EXPECT_TRUE (hamon::all_of(hamon::begin(v2), hamon::end(v2), pred1));
	EXPECT_TRUE (hamon::all_of(hamon::begin(v2), hamon::end(v2), [](int) { return true; }));
	EXPECT_TRUE (hamon::all_of(hamon::begin(v2), hamon::end(v2), [](int) { return false; }));

	const std::list<int> l1 {0,1,2};
	EXPECT_FALSE(hamon::all_of(hamon::begin(l1), hamon::end(l1), pred1));
	EXPECT_TRUE (hamon::all_of(hamon::begin(l1), hamon::end(l1), pred2));
	EXPECT_FALSE(hamon::all_of(hamon::begin(l1), hamon::end(l1), pred3()));
	EXPECT_TRUE (hamon::all_of(hamon::begin(l1), hamon::end(l1), pred4()));
	EXPECT_FALSE(hamon::all_of(hamon::begin(l1), hamon::end(l1), [](int x) { return x < 0; }));
}

}	// namespace all_of_test

}	// namespace hamon_algorithm_test
