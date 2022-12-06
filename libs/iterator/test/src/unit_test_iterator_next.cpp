/**
 *	@file	unit_test_iterator_next.cpp
 *
 *	@brief	next のテスト
 */

#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4146) // 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません。
HAMON_WARNING_DISABLE_MSVC(4307) // '+': 整数定数がオーバーフローしました。
HAMON_WARNING_DISABLE_MSVC(4308) // 負の整数定数が符号なしの型に変換されました。

#include <hamon/iterator/next.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace next_test
{

GTEST_TEST(IteratorTest, NextTest)
{
	{
		int a[] = {0,1,2};

		auto it = hamon::begin(a);
		EXPECT_EQ(0, *it);
		it = hamon::next(it);
		EXPECT_EQ(1, *it);
		it = hamon::next(it);
		EXPECT_EQ(2, *it);
		it = hamon::next(it);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const int a[] = {0,1,2};

		auto it = hamon::begin(a);
		EXPECT_EQ(0, *it);
		it = hamon::next(it, 2);
		EXPECT_EQ(2, *it);
		it = hamon::next(it, -1);
		EXPECT_EQ(1, *it);
		it = hamon::next(it, 2);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] = {0, 1, 2, 3, 4};

		HAMON_CONSTEXPR auto it1 = hamon::begin(a);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, *it1);
		HAMON_CONSTEXPR auto it2 = hamon::next(it1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, *it2);
		HAMON_CONSTEXPR auto it3 = hamon::next(it2, 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, *it3);
		HAMON_CONSTEXPR auto it4 = hamon::next(it3, -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, *it4);
		HAMON_CONSTEXPR auto it5 = hamon::next(it4, 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it5 == hamon::end(a));
	}
	{
		const std::vector<float> v {3,1,4,1,5};

		auto it = hamon::begin(v);
		EXPECT_EQ(3, *it);
		it = hamon::next(it);
		EXPECT_EQ(1, *it);
		it = hamon::next(it);
		EXPECT_EQ(4, *it);
		it = hamon::next(it);
		EXPECT_EQ(1, *it);
		it = hamon::next(it);
		EXPECT_EQ(5, *it);
		it = hamon::next(it);
		EXPECT_TRUE(it == hamon::end(v));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = hamon::begin(v);
		EXPECT_EQ(3, *it);
		it = hamon::next(it, 3);
		EXPECT_EQ(1, *it);
		it = hamon::next(it, -1);
		EXPECT_EQ(4, *it);
		it = hamon::next(it, 2);
		EXPECT_EQ(5, *it);
		it = hamon::next(it, -4);
		EXPECT_EQ(3, *it);
		it = hamon::next(it, 5);
		EXPECT_TRUE(it == hamon::end(v));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = hamon::begin(l);
		EXPECT_EQ(2, *it);
		it = hamon::next(it);
		EXPECT_EQ(3, *it);
		it = hamon::next(it);
		EXPECT_EQ(4, *it);
		it = hamon::next(it);
		EXPECT_TRUE(it == hamon::end(l));
	}
	{
		const std::list<int> l {2, 3, 4};

		auto it = hamon::begin(l);
		EXPECT_EQ(2, *it);
		it = hamon::next(it, 2);
		EXPECT_EQ(4, *it);
		it = hamon::next(it, -2);
		EXPECT_EQ(2, *it);
		it = hamon::next(it, 3);
		EXPECT_TRUE(it == hamon::end(l));
	}
	{
		const std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = hamon::begin(a);
		EXPECT_EQ(1, *it);
		it = hamon::next(it);
		EXPECT_EQ(2, *it);
		it = hamon::next(it);
		EXPECT_EQ(3, *it);
		it = hamon::next(it);
		EXPECT_EQ(4, *it);
		it = hamon::next(it);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = hamon::begin(a);
		EXPECT_EQ(1, *it);
		it = hamon::next(it, 2);
		EXPECT_EQ(3, *it);
		it = hamon::next(it, -1);
		EXPECT_EQ(2, *it);
		it = hamon::next(it, 3);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		HAMON_STATIC_CONSTEXPR std::array<float, 4> a{{1, 2, 3, 4}};

		HAMON_CXX17_CONSTEXPR auto it1 = hamon::begin(a);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(1, *it1);
		HAMON_CXX17_CONSTEXPR auto it2 = hamon::next(it1);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(2, *it2);
		HAMON_CXX17_CONSTEXPR auto it3 = hamon::next(it2, 2);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(4, *it3);
		HAMON_CXX17_CONSTEXPR auto it4 = hamon::next(it3, -1);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(3, *it4);
		HAMON_CXX17_CONSTEXPR auto it5 = hamon::next(it4, 2);
		HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == hamon::end(a));

		HAMON_CXX17_CONSTEXPR auto d = hamon::end(a) - hamon::begin(a);
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(4, d);
	}
}

}	// namespace next_test

}	// namespace hamon_iterator_test

HAMON_WARNING_POP()
