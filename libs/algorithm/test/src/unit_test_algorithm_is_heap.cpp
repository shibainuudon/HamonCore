/**
 *	@file	unit_test_algorithm_is_heap.cpp
 *
 *	@brief	is_heap のテスト
 */

#include <hamon/algorithm/is_heap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace is_heap_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

GTEST_TEST(AlgorithmTest, IsHeapTest)
{
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 1, 2, 3 };
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a)));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 3, 2, 1 };
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_heap(hamon::begin(a), hamon::end(a)));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 9, 5, 4, 1, 1, 3, 2, 6 };
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_STATIC_CONSTEXPR const hamon::array<int, 3> a {{ 1, 2, 3 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		HAMON_STATIC_CONSTEXPR const hamon::array<int, 3> a {{ 3, 2, 1 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		HAMON_STATIC_CONSTEXPR const hamon::array<int, 8> a {{ 9, 5, 4, 1, 1, 3, 2, 6 }};
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a), pred1));
	}
	{
		const std::vector<int> a { 9, 9, 7, 3, 4, 3, 2 };
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a)));
	}
	{
		const std::vector<int> a { 9, 7, 7, 8, 4, 3, 2 };
		EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a)));
	}
	{
		const std::vector<int> a { 3, 2, 1 };
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), [](int x, int y){return x < y;}));
	}
	{
		const std::vector<int> a { 1, 2, 3 };
		EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a), [](int x, int y){return x < y;}));
	}
	{
		const std::vector<int> a { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		EXPECT_TRUE(hamon::is_heap(hamon::begin(a), hamon::end(a), [](int x, int y){return x < y;}));
	}
}

}	// namespace is_heap_test

}	// namespace hamon_algorithm_test
