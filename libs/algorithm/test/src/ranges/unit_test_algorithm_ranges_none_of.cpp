﻿/**
 *	@file	unit_test_algorithm_ranges_none_of.cpp
 *
 *	@brief	ranges::none_of のテスト
 */

#include <hamon/algorithm/ranges/none_of.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_none_of_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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

	VERIFY(!ranges::none_of(x, x+6, ILess{ 3 }));
	VERIFY( ranges::none_of(x+1, x+6, ILess{ 3 }));
	VERIFY(!ranges::none_of(x, ILess{ 5 }));

	test_forward_range<int> c(x);
	VERIFY(!ranges::none_of(c, NotZero<int>{}));

	test_input_range<int> r(x);
	VERIFY(!ranges::none_of(r, NotZero<int>{}));

	return true;
}

struct X { int i; };

struct XLess
{
	int val;
	constexpr bool operator()(X& x) const { return x.i < val; }
};

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

	X x[] = { {2}, {4}, {6}, {8}, {10}, {11} };

	VERIFY(!ranges::none_of(x, x+6, XLess{ 3 }));
	VERIFY( ranges::none_of(x+1, x+6, XLess{ 3 }));
	VERIFY(!ranges::none_of(x, XLess{ 5 }));

	return true;
}

inline bool test03()
{
	namespace ranges = hamon::ranges;

	X x[] = { {2}, {4}, {6}, {8}, {10}, {11} };

	VERIFY(!ranges::none_of(x, x+6, ILess{ 3 }, &X::i));
	VERIFY( ranges::none_of(x+1, x+6, ILess{ 3 }, &X::i));
	VERIFY(!ranges::none_of(x, ILess{ 5 }, &X::i));

	test_forward_range<X> c(x);
	VERIFY(!ranges::none_of(c, NotZero<int>{}, &X::i));

	test_input_range<X> r(x);
	VERIFY(!ranges::none_of(r, NotZero<int>{}, &X::i));
	VERIFY(!ranges::none_of(r, NotZero<X* const>{}, [](X& xx) { return &xx; }));

	return true;
}

struct Y { int i; int j; };

inline bool test04()
{
	namespace ranges = hamon::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };
	VERIFY(!ranges::none_of(y, [](int i) { return i%2 == 0; }, &Y::i));
	VERIFY(!ranges::none_of(y, [](const Y& yy) { return yy.i + yy.j == 3; }));
	VERIFY( ranges::none_of(y, [](const Y& yy) { return yy.i == yy.j; }));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesNoneOfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_none_of_test

}	// namespace hamon_algorithm_test
