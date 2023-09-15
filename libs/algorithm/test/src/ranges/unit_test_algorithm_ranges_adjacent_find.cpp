﻿/**
 *	@file	unit_test_algorithm_ranges_adjacent_find.cpp
 *
 *	@brief	ranges::adjacent_find のテスト
 */

#include <hamon/algorithm/ranges/adjacent_find.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_adjacent_find_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,2,3,4,5 };
		VERIFY(ranges::adjacent_find(x) == ranges::end(x));
	}
	{
		int x[] = { 1,1,2,3,4,5 };
		VERIFY(ranges::adjacent_find(x) == ranges::begin(x));
	}
	{
		int x[] = { 1,2,3,4,4,5,5 };
		VERIFY(ranges::adjacent_find(x) == ranges::begin(x)+3);
	}
	return true;
}

struct X { int i; };

template <template <typename> class iter_wrapper>
inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X x[] = { {2}, {2}, {6}, {8}, {10}, {11} };
		VERIFY(ranges::adjacent_find(x, x+6, {}, &X::i) == x+0);
		VERIFY(ranges::adjacent_find(x+1, x+6, {}, &X::i) == x+6);

		test_range<X, iter_wrapper<X>> r(x);
		VERIFY(ranges::adjacent_find(r, {}, &X::i) == ranges::begin(r));
	}
	{
		X x[] = { {1}, {2}, {6}, {8}, {10}, {10} };
		test_range<X, iter_wrapper<X>> r(x);
		VERIFY(ranges::adjacent_find(r, {}, &X::i) == ranges::next(ranges::begin(r), 4));
	}
	{
		X x[] = { {1}, {2}, {6}, {8}, {10}, {11} };
		test_range<X, iter_wrapper<X>> r(x);
		VERIFY(ranges::adjacent_find(r, {}, &X::i) == ranges::end(r));
	}
	return true;
}

inline bool test03()
{
	namespace ranges = hamon::ranges;
	{
		hamon::vector<int> x{};
		VERIFY(ranges::adjacent_find(x) == x.end());
	}
	{
		hamon::vector<int> x{1,2,3};
		VERIFY(ranges::adjacent_find(x) == x.end());
	}
	{
		hamon::vector<int> x{1,2,2,3,3,3};
		VERIFY(ranges::adjacent_find(x) == x.begin()+1);
	}
	{
		std::forward_list<int> x{};
		VERIFY(ranges::adjacent_find(x) == x.end());
	}
	{
		std::forward_list<int> x{1,2,3};
		VERIFY(ranges::adjacent_find(x) == x.end());
	}
	{
		std::forward_list<int> x{1,2,2,3,3,3};
		VERIFY(ranges::adjacent_find(x) == ranges::next(x.begin(), 1));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = {1,1,2,3,2};
		VERIFY(ranges::adjacent_find(x, [](int i, int j){ return i == j; }) == ranges::begin(x));
		VERIFY(ranges::adjacent_find(x, [](int i, int j){ return i != j; }) == ranges::begin(x)+1);
		VERIFY(ranges::adjacent_find(x, [](int i, int j){ return i <  j; }) == ranges::begin(x)+1);
		VERIFY(ranges::adjacent_find(x, [](int i, int j){ return i >  j; }) == ranges::begin(x)+3);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesAdjacentFindTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02<forward_iterator_wrapper>());
	EXPECT_TRUE(test02<bidirectional_iterator_wrapper>());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_adjacent_find_test

}	// namespace hamon_algorithm_test
