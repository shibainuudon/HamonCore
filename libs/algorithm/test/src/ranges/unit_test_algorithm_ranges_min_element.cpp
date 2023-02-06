/**
 *	@file	unit_test_algorithm_ranges_min_element.cpp
 *
 *	@brief	ranges::min_element のテスト
 */

#include <hamon/algorithm/ranges/min_element.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_min_element_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Abs
{
	constexpr int operator()(int x) const
	{
		return x < 0 ? -x : x;
	}
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 3, 1, -4, 1, 5, -9 };
		test_forward_range<int const> rx(x);
		VERIFY(ranges::min_element(rx) == ranges::next(rx.begin(), 5));
		VERIFY(ranges::min_element(rx, ranges::greater{}) == ranges::next(rx.begin(), 4));
		VERIFY(ranges::min_element(rx, {}, Abs{}) == ranges::next(rx.begin(), 1));
		VERIFY(ranges::min_element(rx.begin(), rx.begin()) == rx.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMinElementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ranges_min_element_test

}	// namespace hamon_algorithm_test
