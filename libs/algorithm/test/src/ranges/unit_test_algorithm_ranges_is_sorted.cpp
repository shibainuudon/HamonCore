﻿/**
 *	@file	unit_test_algorithm_ranges_is_sorted.cpp
 *
 *	@brief	ranges::is_sorted のテスト
 */

#include <hamon/algorithm/ranges/is_sorted.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_is_sorted_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const a[] = {1,2,3,4,5};
		VERIFY(true  == ranges::is_sorted(a));
		VERIFY(false == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {5,4,3,2,1};
		VERIFY(false == ranges::is_sorted(a));
		VERIFY(true  == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {1,2,0,3,4};
		VERIFY(false == ranges::is_sorted(a));
		VERIFY(false == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {1};
		VERIFY(true  == ranges::is_sorted(a));
		VERIFY(true  == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {1,1};
		VERIFY(true  == ranges::is_sorted(a));
		VERIFY(true  == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {0,0,0,1,1,2,3,3,3,4,5,5,5,5};
		test_range<int const, forward_iterator_wrapper> r(a);
		VERIFY(true  == ranges::is_sorted(r));
		VERIFY(false == ranges::is_sorted(r, ranges::greater{}));
	}
	{
		int const a[] = {3,1,4,1,5,9,2};
		test_range<int const, forward_iterator_wrapper> r(a);
		VERIFY(false == ranges::is_sorted(r));
		VERIFY(false == ranges::is_sorted(r, ranges::greater{}));
	}
	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X const a[] = { {1},{1},{3},{5} };
		VERIFY(true  == ranges::is_sorted(a, {}, &X::i));
		VERIFY(false == ranges::is_sorted(a, ranges::greater{}, &X::i));
	}
	{
		std::forward_list<int> const a = {};
		VERIFY(true  == ranges::is_sorted(a));
		VERIFY(true  == ranges::is_sorted(a, ranges::greater{}));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIsSortedTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_is_sorted_test

}	// namespace hamon_algorithm_test
