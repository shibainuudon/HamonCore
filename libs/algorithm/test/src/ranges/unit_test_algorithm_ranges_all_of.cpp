﻿/**
 *	@file	unit_test_algorithm_ranges_all_of.cpp
 *
 *	@brief	ranges::all_of のテスト
 */

#include <hamon/algorithm/ranges/all_of.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_all_of_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct X { int i; };

struct XLess
{
	int val;
	constexpr bool operator()(X& x) const { return x.i < val; }
};

struct ILess
{
	int val;
	constexpr bool operator()(int& i) const { return i < val; }
};

template<typename T>
struct NotZero
{
	constexpr bool operator()(T& t) const { return t != 0; }
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 2, 4, 6, 8, 10, 11 };
	VERIFY( ranges::all_of(x, x+5, ILess{ 11 }));
	VERIFY(!ranges::all_of(x, x+6, ILess{ 11 }));
	VERIFY( ranges::all_of(x, ILess{ 12 }));
	VERIFY(!ranges::all_of(x, ILess{ 11 }));

	test_forward_range<int> c(x);
	VERIFY( ranges::all_of(c, NotZero<int>{}));

	test_input_range<int> r(x);
	VERIFY( ranges::all_of(r, NotZero<int>{}));

	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;

	X x[] = { {2}, {4}, {6}, {8}, {10}, {11} };

	VERIFY( ranges::all_of(x, x+5, XLess{ 11 }));
	VERIFY( ranges::all_of(x, x+5, ILess{ 11 }, &X::i));
	VERIFY(!ranges::all_of(x, x+6, ILess{ 11 }, &X::i));
	VERIFY(!ranges::all_of(x, XLess{ 11 }));
	VERIFY( ranges::all_of(x, XLess{ 12 }));
	VERIFY( ranges::all_of(x, ILess{ 12 }, &X::i));
	VERIFY(!ranges::all_of(x, ILess{ 11 }, &X::i));

	test_forward_range<X> c(x);
	VERIFY( ranges::all_of(c, NotZero<int>{}, &X::i));

	test_input_range<X> r(x);
	VERIFY( ranges::all_of(r, NotZero<int>{}, &X::i));

	return true;
}

struct Y { int i; int j; };

inline bool test03()
{
	namespace ranges = hamon::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };
	VERIFY(ranges::all_of(y, [](int j) { return j%2 == 0; }, &Y::j));
	VERIFY(ranges::all_of(y, [](const Y& yy) { return yy.j == yy.i * 2; }));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesAllOfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_all_of_test

}	// namespace hamon_algorithm_test
