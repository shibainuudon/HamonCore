/**
 *	@file	unit_test_algorithm_is_heap_until.cpp
 *
 *	@brief	is_heap_until のテスト
 */

#include <hamon/algorithm/is_heap_until.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace is_heap_until_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

GTEST_TEST(AlgorithmTest, IsHeapUntilTest)
{
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 1, 2, 3 };
		HAMON_CXX14_CONSTEXPR const auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 1, 2, 3 };
		HAMON_CXX14_CONSTEXPR const auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a), hamon::greater<>());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 3, 2, 1 };
		HAMON_CXX14_CONSTEXPR const auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 3, 2, 1 };
		HAMON_CXX14_CONSTEXPR const auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a), hamon::greater<>());
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
	}
	{
		HAMON_STATIC_CONSTEXPR const int a[] { 9, 5, 4, 1, 1, 3, 2, 6 };
		HAMON_CXX14_CONSTEXPR const auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 7));
	}
	{
		HAMON_STATIC_CONSTEXPR const hamon::array<int, 3> a {{ 1, 2, 3 }};
		HAMON_CXX14_CONSTEXPR const auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
	}
	{
		HAMON_STATIC_CONSTEXPR const hamon::array<int, 3> a {{ 3, 2, 1 }};
		HAMON_CXX14_CONSTEXPR const auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
	}
	{
		HAMON_STATIC_CONSTEXPR const hamon::array<int, 8> a {{ 9, 5, 4, 1, 1, 3, 2, 6 }};
		HAMON_CXX14_CONSTEXPR const auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 7));
	}
	{
		const hamon::vector<int> a { 9, 9, 7, 3, 4, 3, 2 };
		auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 7));
	}
	{
		const hamon::vector<int> a { 9, 7, 7, 8, 4, 3, 2 };
		auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
	}
	{
		const hamon::vector<int> a { 3, 2, 1 };
		auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a), [](int x, int y){return x < y;});
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
	}
	{
		const hamon::vector<int> a { 1, 2, 3 };
		auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a), [](int x, int y){return x < y;});
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
	}
	{
		const hamon::vector<int> a { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		auto ret = hamon::is_heap_until(hamon::begin(a), hamon::end(a), [](int x, int y){return x < y;});
		EXPECT_TRUE(ret == hamon::end(a));
	}
}

}	// namespace is_heap_until_test

}	// namespace hamon_algorithm_test
