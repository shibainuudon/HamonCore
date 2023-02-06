/**
 *	@file	unit_test_algorithm_ranges_lexicographical_compare.cpp
 *
 *	@brief	ranges::lexicographical_compare のテスト
 */

#include <hamon/algorithm/ranges/lexicographical_compare.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_lexicographical_compare_test
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
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4,5 };
		test_input_range<int const> rx(x);
		test_input_range<int const> ry(y);
		VERIFY(!ranges::lexicographical_compare(rx, ry));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4,6 };
		test_input_range<int const> rx(x);
		test_input_range<int const> ry(y);
		VERIFY( ranges::lexicographical_compare(rx, ry));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,6 };
		int const y[] = { 1,2,3,4,5 };
		test_input_range<int const> rx(x);
		test_input_range<int const> ry(y);
		VERIFY(!ranges::lexicographical_compare(rx, ry));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4,5,6 };
		test_input_range<int const> rx(x);
		test_input_range<int const> ry(y);
		VERIFY( ranges::lexicographical_compare(rx, ry));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4 };
		test_input_range<int const> rx(x);
		test_input_range<int const> ry(y);
		VERIFY(!ranges::lexicographical_compare(rx, ry));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		int const y[] = { 1,2,3,4,-6 };
		test_input_range<int const> rx(x);
		test_input_range<int const> ry(y);
		VERIFY(!ranges::lexicographical_compare(rx, ry));
		VERIFY( ranges::lexicographical_compare(rx, ry, ranges::greater{}));
		VERIFY( ranges::lexicographical_compare(rx, ry, {}, Abs{}, Abs{}));
		VERIFY(!ranges::lexicographical_compare(rx, ry, ranges::greater{}, Abs{}, Abs{}));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesLexicographicalCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ranges_lexicographical_compare_test

}	// namespace hamon_algorithm_test
