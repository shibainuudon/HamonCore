﻿/**
 *	@file	unit_test_algorithm_ranges_find_if_not.cpp
 *
 *	@brief	ranges::find_if_not のテスト
 */

#include <hamon/algorithm/ranges/find_if_not.hpp>
#include <hamon/ranges/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_find_if_not_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <int N>
struct Equal
{
	constexpr bool operator()(int i) const
	{
		return i == N;
	}
};

template <int N>
struct Less
{
	constexpr bool operator()(int i) const
	{
		return i < N;
	}
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 2, 2, 6, 8, 10, 11 };

	{
		auto res = ranges::find_if_not(x, x+6, Equal<2>{});
		VERIFY(res == x+2);
	}
	{
		auto res = ranges::find_if_not(x, x+6, Equal<6>{});
		VERIFY(res == x+0);
	}
	{
		auto res = ranges::find_if_not(x, Less<2>{});
		VERIFY(res == x+0);
	}
	{
		auto res = ranges::find_if_not(x, Less<3>{});
		VERIFY(res == x+2);
	}
	{
		auto res = ranges::find_if_not(x, Less<8>{});
		VERIFY(res == x+3);
	}
	{
		auto res = ranges::find_if_not(x, Less<11>{});
		VERIFY(res == x+5);
	}
	{
		auto res = ranges::find_if_not(x, Less<12>{});
		VERIFY(res == x+6);
	}

	return true;
}

struct X { int i; };

inline bool test02()
{
	namespace ranges = hamon::ranges;

	X x[] = { {2}, {2}, {6}, {8}, {10}, {11} };
	{
		auto res = ranges::find_if_not(x, x+6, [](X& v) { return v.i != 8; });
		VERIFY(res == x+3);
		res = ranges::find_if_not(x, x+6, [](X& v) { return v.i % 2 == 1; });
		VERIFY(res == x+0);
		res = ranges::find_if_not(x, x+6, [](X& v) { return v.i != 9; });
		VERIFY(res == x+6);
	}
	{
		test_range<X, forward_iterator_wrapper> c(x);
		auto res2 = ranges::find_if_not(c, [](int i) { return i <= 7; }, &X::i);
		VERIFY(res2 != ranges::end(c) && (*res2).i == 8);
		res2 = ranges::find_if_not(c, [](int i) { return i <= 11; }, &X::i);
		VERIFY(res2 == ranges::end(c));
	}
	{
		test_range<X, input_iterator_wrapper> r(x);
		auto res3 = ranges::find_if_not(r, [](int i) { return i <= 10; }, &X::i);
		VERIFY(res3 != ranges::end(r) && (*res3).i == 11);
	}
	{
		test_range<X, input_iterator_wrapper> r(x);
		auto res3 = ranges::find_if_not(r, [](int i) { return i != 9; }, &X::i);
		VERIFY(res3 == ranges::end(r));
	}

	return true;
}

struct Y { int i; int j; };

inline bool test03()
{
	namespace ranges = hamon::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };
	VERIFY(ranges::find_if_not(y, [](int i) { return i <= 3; }, &Y::j) == y+1);
	VERIFY(ranges::find_if_not(y, [](int i) { return i != 5; }, &Y::j) == y+3);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFindIfNotTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_find_if_not_test

}	// namespace hamon_algorithm_test
