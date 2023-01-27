/**
 *	@file	unit_test_numeric_inner_product.cpp
 *
 *	@brief	inner_product のテスト
 */

#include <hamon/numeric/inner_product.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

GTEST_TEST(NumericTest, InnerProductTest)
{
	{
		int a1[] = { 1, 2, 3 };
		int a2[] = { 4, 5, 6 };
		auto x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 0);
		EXPECT_EQ(32, x1);
		auto x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 10);
		EXPECT_EQ(42, x2);
	}
	{
		HAMON_CONSTEXPR_OR_CONST int a1[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9 };
		HAMON_CONSTEXPR_OR_CONST int a2[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
		HAMON_CXX14_CONSTEXPR auto x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 0);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(735, x1);
		HAMON_CXX14_CONSTEXPR auto x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 10);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(745, x2);
	}
	{
		HAMON_CONSTEXPR_OR_CONST int a1[] = { 2 };
		HAMON_CONSTEXPR_OR_CONST int a2[] = { 3 };
		HAMON_CXX14_CONSTEXPR auto x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 0);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(6, x1);
		HAMON_CXX14_CONSTEXPR auto x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 10);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16, x2);
	}
	{
		std::array<int, 3> a1 = {{ 2, 3, 4 }};
		std::array<int, 3> a2 = {{ 4, 5, 6 }};
		auto x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 0);
		EXPECT_EQ(47, x1);
		auto x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 20);
		EXPECT_EQ(67, x2);
	}
	{
		HAMON_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 2, 3, 4 }};
		HAMON_CONSTEXPR_OR_CONST std::array<int, 3> a2 = {{ 4, 5, 6 }};
		HAMON_CXX17_CONSTEXPR auto x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 0);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(47, x1);
		HAMON_CXX17_CONSTEXPR auto x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 20);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(67, x2);
	}
	{
		HAMON_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 4 }};
		HAMON_CONSTEXPR_OR_CONST std::array<int, 3> a2 = {{ 6 }};
		HAMON_CXX17_CONSTEXPR auto x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 0);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(24, x1);
		HAMON_CXX17_CONSTEXPR auto x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 20);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(44, x2);
	}
	{
		HAMON_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 2, 3, 4 }};
		HAMON_CONSTEXPR_OR_CONST int a2[] = { 4, 5, 6 };
		HAMON_CXX17_CONSTEXPR auto x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 0);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(47, x1);
		HAMON_CXX17_CONSTEXPR auto x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), 20);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(67, x2);
	}
	{
		HAMON_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 2, 3, 4 }};
		const std::vector<int> v1 = {{ 4, 5, 6 }};
		auto const x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(v1), 0);
		EXPECT_EQ(47, x1);
		auto const x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(v1), 20);
		EXPECT_EQ(67, x2);
	}
	{
		HAMON_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 2, 3, 4 }};
		const std::list<int> l1 = {{ 4, 5, 6 }};
		auto const x1 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(l1), 0);
		EXPECT_EQ(47, x1);
		auto const x2 = hamon::inner_product(hamon::begin(a1), hamon::end(a1), hamon::begin(l1), 20);
		EXPECT_EQ(67, x2);
	}
	{
		std::vector<int> v1 = { 3, 4, 5, 6 };
		std::vector<int> v2 = { 5, 6, 7, 8 };
		auto x1 = hamon::inner_product(hamon::begin(v1), hamon::end(v1), hamon::begin(v2), 0);
		EXPECT_EQ(122, x1);
		auto x2 = hamon::inner_product(hamon::begin(v1), hamon::end(v1), hamon::begin(v2), 30);
		EXPECT_EQ(152, x2);
	}
	{
		std::vector<int> v1 = { 3, 4, 5, 6 };
		std::list<int> l1 = { 5, 6, 7, 8 };
		auto x1 = hamon::inner_product(hamon::begin(v1), hamon::end(v1), hamon::begin(l1), 0);
		EXPECT_EQ(122, x1);
		auto x2 = hamon::inner_product(hamon::begin(v1), hamon::end(v1), hamon::begin(l1), 30);
		EXPECT_EQ(152, x2);
	}
	{
		std::vector<int> v1;
		std::vector<int> v2;
		auto x1 = hamon::inner_product(hamon::begin(v1), hamon::end(v1), hamon::begin(v2), 0);
		EXPECT_EQ(0, x1);
		auto x2 = hamon::inner_product(hamon::begin(v1), hamon::end(v1), hamon::begin(v2), 30);
		EXPECT_EQ(30, x2);
	}
	{
		std::list<int> l1 = { 1, 2, 3, 4, 5 };
		std::list<int> l2 = { 6, 7, 8, 9, 10 };
		auto x1 = hamon::inner_product(hamon::begin(l1), hamon::end(l1), hamon::begin(l2), 0);
		EXPECT_EQ(130, x1);
		auto x2 = hamon::inner_product(hamon::begin(l1), hamon::end(l1), hamon::begin(l2), 40);
		EXPECT_EQ(170, x2);
	}
	{
		std::list<int> l1;
		std::list<int> l2;
		auto x1 = hamon::inner_product(hamon::begin(l1), hamon::end(l1), hamon::begin(l2), 0);
		EXPECT_EQ(0, x1);
		auto x2 = hamon::inner_product(hamon::begin(l1), hamon::end(l1), hamon::begin(l2), 40);
		EXPECT_EQ(40, x2);
	}
}
