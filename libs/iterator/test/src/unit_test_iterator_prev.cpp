/**
 *	@file	unit_test_iterator_prev.cpp
 *
 *	@brief	prev のテスト
 */

#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4146) // 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません。
HAMON_WARNING_DISABLE_MSVC(4307) // '+': 整数定数がオーバーフローしました。
HAMON_WARNING_DISABLE_MSVC(4308) // 負の整数定数が符号なしの型に変換されました。

#include <hamon/iterator/prev.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace prev_test
{

GTEST_TEST(IteratorTest, PrevTest)
{
	{
		int a[] = {0,1,2};

		auto it = hamon::end(a);
		it = hamon::prev(it);
		EXPECT_EQ(2, *it);
		it = hamon::prev(it);
		EXPECT_EQ(1, *it);
		it = hamon::prev(it);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it == hamon::begin(a));
	}
	{
		const int a[] = {0,1,2};

		auto it = hamon::end(a);
		it = hamon::prev(it, 2);
		EXPECT_EQ(1, *it);
		it = hamon::prev(it, -1);
		EXPECT_EQ(2, *it);
		it = hamon::prev(it, 2);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it == hamon::begin(a));
	}
	{
		HAMON_STATIC_CONSTEXPR int a[] = {0, 1, 2, 3, 4};

		HAMON_CONSTEXPR auto it1 = hamon::end(a);
		HAMON_CONSTEXPR auto it2 = hamon::prev(it1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, *it2);
		HAMON_CONSTEXPR auto it3 = hamon::prev(it2, 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, *it3);
		HAMON_CONSTEXPR auto it4 = hamon::prev(it3, -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, *it4);
		HAMON_CONSTEXPR auto it5 = hamon::prev(it4, 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, *it5);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(it5 == hamon::begin(a));
	}
	{
		const std::vector<float> v {3,1,4,1,5};

		auto it = hamon::end(v);
		it = hamon::prev(it);
		EXPECT_EQ(5, *it);
		it = hamon::prev(it);
		EXPECT_EQ(1, *it);
		it = hamon::prev(it);
		EXPECT_EQ(4, *it);
		it = hamon::prev(it);
		EXPECT_EQ(1, *it);
		it = hamon::prev(it);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it == hamon::begin(v));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = hamon::end(v);
		it = hamon::prev(it, 3);
		EXPECT_EQ(4, *it);
		it = hamon::prev(it, -1);
		EXPECT_EQ(1, *it);
		it = hamon::prev(it, 2);
		EXPECT_EQ(1, *it);
		it = hamon::prev(it, -3);
		EXPECT_EQ(5, *it);
		it = hamon::prev(it, 4);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it == hamon::begin(v));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = hamon::end(l);
		it = hamon::prev(it);
		EXPECT_EQ(4, *it);
		it = hamon::prev(it);
		EXPECT_EQ(3, *it);
		it = hamon::prev(it);
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it == hamon::begin(l));
	}
	{
		const std::list<int> l {2, 3, 4};

		auto it = hamon::end(l);
		it = hamon::prev(it, 2);
		EXPECT_EQ(3, *it);
		it = hamon::prev(it, -1);
		EXPECT_EQ(4, *it);
		it = hamon::prev(it, 2);
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it == hamon::begin(l));
	}
	{
		const hamon::array<float, 4> a{{1, 2, 3, 4}};

		auto it = hamon::end(a);
		it = hamon::prev(it);
		EXPECT_EQ(4, *it);
		it = hamon::prev(it);
		EXPECT_EQ(3, *it);
		it = hamon::prev(it);
		EXPECT_EQ(2, *it);
		it = hamon::prev(it);
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it == hamon::begin(a));
	}
	{
		hamon::array<float, 4> a{{1, 2, 3, 4}};

		auto it = hamon::end(a);
		it = hamon::prev(it, 2);
		EXPECT_EQ(3, *it);
		it = hamon::prev(it, -1);
		EXPECT_EQ(4, *it);
		it = hamon::prev(it, 3);
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it == hamon::begin(a));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int,5> a {{0, 1, 2, 3, 4}};

		HAMON_CXX14_CONSTEXPR auto it1 = hamon::end(a);
		HAMON_CXX14_CONSTEXPR auto it2 = hamon::prev(it1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, *it2);
		HAMON_CXX14_CONSTEXPR auto it3 = hamon::prev(it2, 2);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(2, *it3);
		HAMON_CXX14_CONSTEXPR auto it4 = hamon::prev(it3, -1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, *it4);
		HAMON_CXX14_CONSTEXPR auto it5 = hamon::prev(it4, 3);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(0, *it5);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(it5 == hamon::begin(a));
	}
}

}	// namespace prev_test

}	// namespace hamon_iterator_test

HAMON_WARNING_POP()
