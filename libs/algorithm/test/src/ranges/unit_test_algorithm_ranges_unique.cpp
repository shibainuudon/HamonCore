/**
 *	@file	unit_test_algorithm_ranges_unique.cpp
 *
 *	@brief	ranges::unique のテスト
 */

#include <hamon/algorithm/ranges/unique.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_unique_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,2,2,3,3,3,4,5,5 };
		auto res = ranges::unique(x, x+9);
		VERIFY(res.begin() == x+5);
		VERIFY(res.end()   == x+9);
		int const y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, x+5, y, y+5));
	}
	{
		int x[] = { 1,1,2,1,2,2,1 };
		test_forward_range<int> rx(x);
		auto res = ranges::unique(rx);
		VERIFY(res.begin() == ranges::next(rx.begin(), 5));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 1,2,1,2,1 };
		VERIFY(ranges::equal(x, x+5, y, y+5));
	}
	{
		int x[] = { 1,2,3,4 };
		test_forward_range<int> rx(x);
		auto res = ranges::unique(rx);
		VERIFY(res.begin() == rx.end());
		VERIFY(res.end()   == rx.end());
		int const y[] = { 1,2,3,4 };
		VERIFY(ranges::equal(x, x+4, y, y+4));
	}
	{
		int x[] = { 1,2,1,3,5,4,4,5 };
		test_forward_range<int> rx(x);
		auto res = ranges::unique(rx, ranges::greater{});
		VERIFY(res.begin() == ranges::next(rx.begin(), 5));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 1,2,3,5,5 };
		VERIFY(ranges::equal(x, x+5, y, y+5));
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
		X x[] = { {1},{1},{1},{2},{2},{3},{3},{3} };
		auto res = ranges::unique(x, {}, &X::i);
		VERIFY(res.begin() == x+3);
		VERIFY(res.end()   == x+8);
		int const y[] = { 1,2,3 };
		VERIFY(ranges::equal(x, x+3, y, y+3, {}, &X::i));
	}
	{
		int x[] = { 5,6,4,6,7,3,4,5,8,2,9,8,7,6,5,4,3,1 };
		test_forward_range<int> rx(x);
		auto res = ranges::unique(rx, [](int a, int b){return a < b;});
		VERIFY(res.begin() == ranges::next(rx.begin(), 5));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 5,4,3,2,1 };
		VERIFY(ranges::equal(x, x+5, y, y+5));
	}
	{
		std::forward_list<int> x = {};
		auto res = ranges::unique(x);
		VERIFY(res.begin() == x.end());
		VERIFY(res.end()   == x.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesUniqueTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_unique_test

}	// namespace hamon_algorithm_test
