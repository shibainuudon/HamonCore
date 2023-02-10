/**
 *	@file	unit_test_algorithm_ranges_minmax.cpp
 *
 *	@brief	ranges::minmax のテスト
 */

#include <hamon/algorithm/ranges/minmax.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_minmax_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	VERIFY(ranges::minmax(2,3).min == 2);
	VERIFY(ranges::minmax(2,3).max == 3);
	VERIFY(ranges::minmax(3,2).min == 2);
	VERIFY(ranges::minmax(3,2).max == 3);
	VERIFY(ranges::minmax(2,3,ranges::greater{}).min == 3);
	VERIFY(ranges::minmax(2,3,ranges::greater{}).max == 2);
	{
		int const x[] = { 3, 1, 2, 4 };
		test_input_range<int const> rx(x);
		auto res = ranges::minmax(rx);
		VERIFY(res.min == 1);
		VERIFY(res.max == 4);
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
	VERIFY(ranges::minmax(X{1},X{5},{},&X::i).min.i == 1);
	VERIFY(ranges::minmax(X{1},X{5},{},&X::i).max.i == 5);
	{
		auto res = ranges::minmax({2,3,1,4});
		VERIFY(res.min == 1);
		VERIFY(res.max == 4);
	}
	{
		auto res = ranges::minmax({2,3,1,4},ranges::greater{});
		VERIFY(res.min == 4);
		VERIFY(res.max == 1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMinMaxTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_minmax_test

}	// namespace hamon_algorithm_test
