/**
 *	@file	unit_test_algorithm_ranges_clamp.cpp
 *
 *	@brief	ranges::clamp のテスト
 */

#include <hamon/algorithm/ranges/clamp.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_clamp_test
{

struct X
{
	int i;
};

GTEST_TEST(AlgorithmTest, RangesClampTest)
{
	namespace ranges = hamon::ranges;

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(0, 1, 3) == 1);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(1, 1, 3) == 1);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(2, 1, 3) == 2);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(3, 1, 3) == 3);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(4, 1, 3) == 3);

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(21, 20, 10, ranges::greater{}) == 20);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(20, 20, 10, ranges::greater{}) == 20);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(19, 20, 10, ranges::greater{}) == 19);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp(10, 20, 10, ranges::greater{}) == 10);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ranges::clamp( 9, 20, 10, ranges::greater{}) == 10);

	EXPECT_TRUE(ranges::clamp(X{0}, X{1}, X{3}, {}, &X::i).i == 1);
	EXPECT_TRUE(ranges::clamp(X{1}, X{1}, X{3}, {}, &X::i).i == 1);
	EXPECT_TRUE(ranges::clamp(X{2}, X{1}, X{3}, {}, &X::i).i == 2);
	EXPECT_TRUE(ranges::clamp(X{3}, X{1}, X{3}, {}, &X::i).i == 3);
	EXPECT_TRUE(ranges::clamp(X{4}, X{1}, X{3}, {}, &X::i).i == 3);
}

}	// namespace ranges_clamp_test

}	// namespace hamon_algorithm_test
