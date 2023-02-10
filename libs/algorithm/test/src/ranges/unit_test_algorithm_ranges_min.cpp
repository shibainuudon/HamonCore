﻿/**
 *	@file	unit_test_algorithm_ranges_min.cpp
 *
 *	@brief	ranges::min のテスト
 */

#include <hamon/algorithm/ranges/min.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_min_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	VERIFY(ranges::min(2,3) == 2);
	VERIFY(ranges::min(2,3, ranges::greater{}) == 3);
	VERIFY(ranges::min(3,2) == 2);
	VERIFY(ranges::min(3,2, ranges::greater{}) == 3);
	{
		int const x[] = { 1, 2, 3, 4 };
		test_input_range<int const> rx(x);
		VERIFY(ranges::min(rx) == 1);
	}
	{
		int const x[] = { 1, 2, 3, 4 };
		test_input_range<int const> rx(x);
		VERIFY(ranges::min(rx, ranges::greater{}) == 4);
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

	VERIFY(ranges::min(X{2}, X{3}, {}, &X::i).i == 2);
	VERIFY(ranges::min(X{2}, X{3}, ranges::greater{}, &X::i).i == 3);

	VERIFY(ranges::min({2,3,4}) == 2);
	VERIFY(ranges::min({2,3,4}, ranges::greater{}) == 4);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMinTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_min_test

}	// namespace hamon_algorithm_test
