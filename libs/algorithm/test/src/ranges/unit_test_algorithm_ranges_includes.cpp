/**
 *	@file	unit_test_algorithm_ranges_includes.cpp
 *
 *	@brief	ranges::includes のテスト
 */

#include <hamon/algorithm/ranges/includes.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_includes_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,2,3,4,5,6,7 };
		int y[] = { 2,4,6 };
		test_input_range<int> rx(x);
		test_input_range<int> ry(y);
		VERIFY(ranges::includes(rx, ry));
	}
	{
		int x[] = { 7,6,5,4,3,2,1 };
		int y[] = { 6,4,2 };
		test_input_range<int> rx(x);
		test_input_range<int> ry(y);
		VERIFY(ranges::includes(rx, ry, ranges::greater{}));
	}
	{
		int x[] = { 1,2,3 };
		int y[] = { 1 };
		VERIFY( ranges::includes(x, y));
		VERIFY(!ranges::includes(y, x));
	}
	{
		int x[] = { 1,2,3,4 };
		int y[] = { 2,3,4,5 };
		VERIFY(!ranges::includes(x, y));
		VERIFY(!ranges::includes(y, x));
	}
	{
		int x[] = { 1,2,3 };
		int y[] = { 1,2,3,4 };
		VERIFY(!ranges::includes(x, y));
		VERIFY( ranges::includes(y, x));
	}
	{
		int x[] = { 1,2,3 };
		int y[] = { 1,2,3 };
		VERIFY( ranges::includes(x, y));
		VERIFY( ranges::includes(y, x));
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
		X x[] = { {1},{2},{3} };
		X y[] = { {1} };
		VERIFY( ranges::includes(x, y, {}, &X::i, &X::i));
		VERIFY(!ranges::includes(y, x, {}, &X::i, &X::i));
	}
	{
		hamon::vector<int> x = {};
		hamon::vector<int> y = {};
		VERIFY( ranges::includes(x, y));
		VERIFY( ranges::includes(y, x));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIncludesTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_includes_test

}	// namespace hamon_algorithm_test
