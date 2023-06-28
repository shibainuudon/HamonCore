/**
 *	@file	unit_test_algorithm_any_of.cpp
 *
 *	@brief	any_of のテスト
 */

#include <hamon/algorithm/any_of.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace any_of_test
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

GTEST_TEST(AlgorithmTest, AnyOfTest)
{
	HAMON_CXX11_CONSTEXPR int a1[] {0,1,2};
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::any_of(hamon::begin(a1), hamon::end(a1), pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::any_of(hamon::begin(a1), hamon::end(a1), pred2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::any_of(hamon::begin(a1), hamon::end(a1), pred3()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::any_of(hamon::begin(a1), hamon::end(a1), pred4()));

	HAMON_CXX11_CONSTEXPR hamon::array<int, 8> a2{{3, 4, 4, 5, 5, 5, 3, 6}};
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::any_of(hamon::begin(a2), hamon::end(a2), pred1));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::any_of(hamon::begin(a2), hamon::end(a2), pred2));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::any_of(hamon::begin(a2), hamon::end(a2), pred3()));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::any_of(hamon::begin(a2), hamon::end(a2), pred4()));

	const std::vector<int> v1 {7, 8, 9};
	EXPECT_FALSE(hamon::any_of(hamon::begin(v1), hamon::end(v1), pred1));
	EXPECT_TRUE (hamon::any_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x == 7; }));
	EXPECT_TRUE (hamon::any_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x > 8; }));
	EXPECT_FALSE(hamon::any_of(hamon::begin(v1), hamon::end(v1), [](int x) { return x == 10; }));

	const std::vector<int> v2;
	EXPECT_FALSE(hamon::any_of(hamon::begin(v2), hamon::end(v2), pred1));
	EXPECT_FALSE(hamon::any_of(hamon::begin(v2), hamon::end(v2), [](int) { return true; }));

	const std::list<int> l1 {0,1,2};
	EXPECT_TRUE (hamon::any_of(hamon::begin(l1), hamon::end(l1), pred1));
	EXPECT_FALSE(hamon::any_of(hamon::begin(l1), hamon::end(l1), pred2));
	EXPECT_TRUE (hamon::any_of(hamon::begin(l1), hamon::end(l1), pred3()));
	EXPECT_FALSE(hamon::any_of(hamon::begin(l1), hamon::end(l1), [](int x) { return x < 0; }));
}

}	// namespace any_of_test

}	// namespace hamon_algorithm_test
