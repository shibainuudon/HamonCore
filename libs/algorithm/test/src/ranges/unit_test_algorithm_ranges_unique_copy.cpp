/**
 *	@file	unit_test_algorithm_ranges_unique_copy.cpp
 *
 *	@brief	ranges::unique_copy のテスト
 */

#include <hamon/algorithm/ranges/unique_copy.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_unique_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 1,2,2,3,3,3,4,5,5 };
		int w[9] = {};
		auto res = ranges::unique_copy(x, x+9, w);
		VERIFY(res.in  == x+9);
		VERIFY(res.out == w+5);
		int const y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(w, w+5, y, y+5));
	}
	{
		int const x[] = { 1,1,2,1,2,2,1 };
		test_input_range<int const> rx(x);
		int w[5] = {};
		auto res = ranges::unique_copy(rx, w);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+5);
		int const y[] = { 1,2,1,2,1 };
		VERIFY(ranges::equal(w, w+5, y, y+5));
	}
	{
		char const x[] = { 1,1,2,1,2,2,1 };
		test_input_range<char const> rx(x);
		int w[5] = {};
		auto res = ranges::unique_copy(rx, w);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+5);
		int const y[] = { 1,2,1,2,1 };
		VERIFY(ranges::equal(w, w+5, y, y+5));
	}
	{
		int const x[] = { 1,2,1,3,5,4,4,5 };
		test_forward_range<int const> rx(x);
		int w[5] = {};
		auto res = ranges::unique_copy(rx, w, ranges::greater{});
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+5);
		int const y[] = { 1,2,3,5,5 };
		VERIFY(ranges::equal(w, w+5, y, y+5));
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
		X w[8] = {};
		auto res = ranges::unique_copy(x, w, {}, &X::i);
		VERIFY(res.in  == x+8);
		VERIFY(res.out == w+3);
		int const y[] = { 1,2,3 };
		VERIFY(ranges::equal(w, w+3, y, y+3, {}, &X::i));
	}
	{
		int x[] = { 5,6,4,6,7,3,4,5,8,2,9,8,7,6,5,4,3,1 };
		int w[10] = {};
		test_forward_range<int> rx(x);
		auto res = ranges::unique_copy(rx, w, [](int a, int b){return a < b;});
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+5);
		int const y[] = { 5,4,3,2,1 };
		VERIFY(ranges::equal(w, w+5, y, y+5));
	}
	{
		std::forward_list<int> x = {};
		int w[1] = {};
		auto res = ranges::unique_copy(x, w);
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesUniqueCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_unique_copy_test

}	// namespace hamon_algorithm_test
