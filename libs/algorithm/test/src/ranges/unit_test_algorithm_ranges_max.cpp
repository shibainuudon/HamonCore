/**
 *	@file	unit_test_algorithm_ranges_max.cpp
 *
 *	@brief	ranges::max のテスト
 */

#include <hamon/algorithm/ranges/max.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_max_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	VERIFY(ranges::max(2,3) == 3);
	VERIFY(ranges::max(2,3, ranges::greater{}) == 2);
	VERIFY(ranges::max(3,2) == 3);
	VERIFY(ranges::max(3,2, ranges::greater{}) == 2);
	{
		int const x[] = { 1, 2, 3, 4 };
		test_input_range<int const> rx(x);
		VERIFY(ranges::max(rx) == 4);
	}
	{
		int const x[] = { 1, 2, 3, 4 };
		test_input_range<int const> rx(x);
		VERIFY(ranges::max(rx, ranges::greater{}) == 1);
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

	VERIFY(ranges::max(X{2}, X{3}, {}, &X::i).i == 3);
	VERIFY(ranges::max(X{2}, X{3}, ranges::greater{}, &X::i).i == 2);

	VERIFY(ranges::max({2,3,4}) == 4);
	VERIFY(ranges::max({2,3,4}, ranges::greater{}) == 2);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMaxTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_max_test

}	// namespace hamon_algorithm_test
