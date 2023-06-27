/**
 *	@file	unit_test_numeric_accumulate.cpp
 *
 *	@brief	accumulate のテスト
 */

#include <hamon/numeric/accumulate.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/functional/multiplies.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

GTEST_TEST(NumericTest, AccumulateTest)
{
	{
		const int a[] = { 1, 2, 3 };
		auto x1 = hamon::accumulate(hamon::begin(a), hamon::end(a), 0);
		EXPECT_EQ( 6, x1);
		auto x2 = hamon::accumulate(hamon::begin(a), hamon::end(a), 10);
		EXPECT_EQ(16, x2);
		auto x3 = hamon::accumulate(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x + (y * y); });
		EXPECT_EQ(14, x3);
	}
	{
		const hamon::array<int, 4> a = {{ 11, 12, 13, 14 }};
		auto x1 = hamon::accumulate(hamon::begin(a), hamon::end(a), 0);
		EXPECT_EQ(50, x1);
		auto x2 = hamon::accumulate(hamon::begin(a), hamon::end(a), -10);
		EXPECT_EQ(40, x2);
		auto x3 = hamon::accumulate(hamon::begin(a), hamon::end(a), 100, [](int x, int y) { return x + (y * 2); });
		EXPECT_EQ(200, x3);
	}
	{
		const std::vector<int> v = { 3, 1, 4, 1, 5 };
		auto x1 = hamon::accumulate(hamon::begin(v), hamon::end(v), 0);
		EXPECT_EQ(14, x1);
		auto x2 = hamon::accumulate(hamon::begin(v), hamon::end(v), 20);
		EXPECT_EQ(34, x2);
		auto x3 = hamon::accumulate(hamon::begin(v), hamon::end(v), -20, [](int x, int y) { return x * y; });
		EXPECT_EQ(-1200, x3);
	}
	{
		const std::list<int> l = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		auto x1 = hamon::accumulate(hamon::begin(l), hamon::end(l), 0);
		EXPECT_EQ(55, x1);
		auto x2 = hamon::accumulate(hamon::begin(l), hamon::end(l), 30);
		EXPECT_EQ(85, x2);
		auto x3 = hamon::accumulate(hamon::begin(l), hamon::end(l), -30, [](int x, int y) { return x + y + 1; });
		EXPECT_EQ(36, x3);
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = { 1, 2, 3, 4 };
		HAMON_CXX11_CONSTEXPR auto x1 = hamon::accumulate(hamon::begin(a), hamon::end(a), 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, x1);
		HAMON_CXX11_CONSTEXPR auto x2 = hamon::accumulate(hamon::begin(a), hamon::end(a), 10);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, x2);
		HAMON_CXX11_CONSTEXPR auto x3 = hamon::accumulate(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, x3);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<int, 5> a = {{ 11, 12, 13, 14, 15 }};
		HAMON_CXX11_CONSTEXPR auto x1 = hamon::accumulate(hamon::begin(a), hamon::end(a), 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(65, x1);
		HAMON_CXX11_CONSTEXPR auto x2 = hamon::accumulate(hamon::begin(a), hamon::end(a), -20);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(45, x2);
		HAMON_CXX11_CONSTEXPR auto x3 = hamon::accumulate(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(360360, x3);
	}
}
