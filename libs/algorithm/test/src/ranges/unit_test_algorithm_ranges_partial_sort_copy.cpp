/**
 *	@file	unit_test_algorithm_ranges_partial_sort_copy.cpp
 *
 *	@brief	ranges::partial_sort_copy のテスト
 */

#include <hamon/algorithm/ranges/partial_sort_copy.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_partial_sort_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[1] = {};
		auto res = ranges::partial_sort_copy(x, w);
		VERIFY(res.in  == x+11);
		VERIFY(res.out == w+1);
		int const y[] = { 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[1] = {};
		auto res = ranges::partial_sort_copy(x, w, ranges::greater{});
		VERIFY(res.in  == x+11);
		VERIFY(res.out == w+1);
		int const y[] = { 9 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[4] = {};
		auto res = ranges::partial_sort_copy(x, w);
		VERIFY(res.in  == x+11);
		VERIFY(res.out == w+4);
		int const y[] = { 1, 1, 2, 3 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[5] = {};
		auto res = ranges::partial_sort_copy(x, w, ranges::greater{});
		VERIFY(res.in  == x+11);
		VERIFY(res.out == w+5);
		int const y[] = { 9, 6, 5, 5, 5 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[6] = {};
		test_input_range<int const> rx(x);
		test_random_access_range<int> rw(w);
		auto res = ranges::partial_sort_copy(rx, rw);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 1, 1, 2, 3, 3, 4 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		int w[7] = {};
		test_input_range<int const> rx(x);
		test_random_access_range<int> rw(w);
		auto res = ranges::partial_sort_copy(rx, rw, ranges::greater{});
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 9, 6, 5, 5, 5, 4, 3 };
		VERIFY(ranges::equal(w, y));
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
		X const x[] = { {5},{1},{3},{2},{4},{6} };
		X w[2] = {};
		auto res = ranges::partial_sort_copy(x, w, {}, &X::i, &X::i);
		VERIFY(res.in  == x+6);
		VERIFY(res.out == w+2);
		X const y[] = { {1},{2} };
		VERIFY(ranges::equal(w, y, {}, &X::i, &X::i));
	}
	{
		X const x[] = { {5},{1},{3},{2},{4},{6} };
		X w[3] = {};
		auto res = ranges::partial_sort_copy(x, w, ranges::greater{}, &X::i, &X::i);
		VERIFY(res.in  == x+6);
		VERIFY(res.out == w+3);
		X const y[] = { {6},{5},{4} };
		VERIFY(ranges::equal(w, y, {}, &X::i, &X::i));
	}
	{
		hamon::vector<int> x = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
		hamon::vector<int> w = {};
		auto res = ranges::partial_sort_copy(x, w);
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w.end());
		VERIFY(w.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPartialSortCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_partial_sort_copy_test

}	// namespace hamon_algorithm_test
