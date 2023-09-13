/**
 *	@file	unit_test_algorithm_mismatch.cpp
 *
 *	@brief	mismatch のテスト
 */

#include <hamon/algorithm/mismatch.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace mismatch_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return (x % 2) == (y % 2);
}

GTEST_TEST(AlgorithmTest, MismatchTest)
{
	{
		HAMON_STATIC_CONSTEXPR int a1[] = { 1,2,3 };
		HAMON_STATIC_CONSTEXPR int a2[] = { 1,2,3 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto p =
			hamon::mismatch(hamon::begin(a1), hamon::end(a1), hamon::begin(a2));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == hamon::end(a1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == hamon::end(a2));
	}
	{
		HAMON_STATIC_CONSTEXPR int a1[] = { 1,2,3 };
		HAMON_STATIC_CONSTEXPR int a2[] = { 1,2,3,4 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto p =
			hamon::mismatch(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), hamon::end(a2));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == hamon::end(a1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == hamon::next(hamon::begin(a2), 3));
	}
	{
		HAMON_STATIC_CONSTEXPR int a1[] = { 1,2,3,4 };
		HAMON_STATIC_CONSTEXPR int a2[] = { 1,2,3 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto p =
			hamon::mismatch(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), hamon::end(a2));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == hamon::next(hamon::begin(a1), 3));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == hamon::end(a2));
	}
	{
		HAMON_STATIC_CONSTEXPR int a1[] = { 1,2,3,4,5 };
		HAMON_STATIC_CONSTEXPR int a2[] = { 1,2,5,6,4 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto p =
			hamon::mismatch(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == hamon::next(hamon::begin(a1), 4));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == hamon::next(hamon::begin(a2), 4));
	}
	{
		HAMON_STATIC_CONSTEXPR int a1[] = { 1,2,3,4,5 };
		HAMON_STATIC_CONSTEXPR int a2[] = { 1,2,5,6,4 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto p =
			hamon::mismatch(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), hamon::end(a2), pred1);
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == hamon::next(hamon::begin(a1), 4));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == hamon::next(hamon::begin(a2), 4));
	}
	{
		HAMON_STATIC_CONSTEXPR hamon::array<int, 6> a1 ={{ 1,2,3,4,5,6 }};
		HAMON_STATIC_CONSTEXPR int a2[]              = { 1,2,3,1,5 };
		HAMON_CXX14_CONSTEXPR_OR_CONST auto p =
			hamon::mismatch(hamon::begin(a1), hamon::end(a1), hamon::begin(a2));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == hamon::next(hamon::begin(a1), 3));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == hamon::next(hamon::begin(a2), 3));
	}
	{
		const hamon::vector<int>   v = { 1,2,3,4,3,2 };
		const hamon::array<int, 6> a ={{ 1,2,4,3,2,1 }};
		auto const p = hamon::mismatch(hamon::begin(v), hamon::end(v), hamon::begin(a));
		EXPECT_TRUE(p.first  == hamon::next(hamon::begin(v), 2));
		EXPECT_TRUE(p.second == hamon::next(hamon::begin(a), 2));
	}
	{
		const std::list<int>   l = { 1,2,3,4,3, };
		const hamon::vector<int> v = { 1,2,3,4,3,2 };
		auto const p = hamon::mismatch(hamon::begin(l), hamon::end(l), hamon::begin(v));
		EXPECT_TRUE(p.first  == hamon::end(l));
		EXPECT_TRUE(p.second == hamon::next(hamon::begin(v), 5));
	}
	{
		const std::list<int>   l = { 1,2,3,4,5 };
		const hamon::vector<int> v = { 3,4,3,3,5 };
		auto const p = hamon::mismatch(hamon::begin(l), hamon::end(l), hamon::begin(v), pred1);
		EXPECT_TRUE(p.first  == hamon::next(hamon::begin(l), 3));
		EXPECT_TRUE(p.second == hamon::next(hamon::begin(v), 3));
	}
	{
		const std::list<int>   l = { 1,2,3,4,5 };
		const hamon::vector<int> v = { 1,2,3,4 };
		auto const p = hamon::mismatch(hamon::begin(l), hamon::end(l), hamon::begin(v), hamon::end(v));
		EXPECT_TRUE(p.first  == hamon::next(hamon::begin(l), 4));
		EXPECT_TRUE(p.second == hamon::end(v));
	}
	{
		const std::list<int>   l = { 1,2,3,4 };
		const hamon::vector<int> v = { 1,2,3,4,5 };
		auto const p = hamon::mismatch(hamon::begin(l), hamon::end(l), hamon::begin(v), hamon::end(v), [](int x, int y) { return x == y; });
		EXPECT_TRUE(p.first  == hamon::end(l));
		EXPECT_TRUE(p.second == hamon::next(hamon::begin(v), 4));
	}
}

}	// namespace mismatch_test

}	// namespace hamon_algorithm_test
