/**
 *	@file	unit_test_algorithm_ranges_remove_copy_if.cpp
 *
 *	@brief	ranges::remove_copy_if のテスト
 */

#include <hamon/algorithm/ranges/remove_copy_if.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_remove_copy_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsEven
{
	constexpr bool operator()(int i) const { return i % 2 == 0; }
};

struct IsOdd
{
	constexpr bool operator()(int i) const { return i % 2 == 1; }
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 1,2,3,4,5 };
		int w[5] = {};
		auto res = ranges::remove_copy_if(x, x+5, w, IsEven{});
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+3);
		int const y[] = { 1,3,5 };
		VERIFY(ranges::equal(w, w+3, y, y+3));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		test_range<int const, forward_iterator_wrapper> rx(x);
		int w[5] = {};
		auto res = ranges::remove_copy_if(rx, w, IsOdd{});
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+2);
		int const y[] = { 2,4 };
		VERIFY(ranges::equal(w, w+2, y, y+2));
	}
	{
		int const x[] = { 1,3,5,7 };
		test_range<int const, forward_iterator_wrapper> rx(x);
		int w[4] = {};
		auto res = ranges::remove_copy_if(rx, w, IsOdd{});
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w);
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
		int const x[] = { 1,2,3,4,5 };
		int w[5] = {};
		auto res = ranges::remove_copy_if(x, x+5, w, [](int a) {return a == 3; });
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+4);
		int const y[4] = { 1,2,4,5 };
		VERIFY(ranges::equal(w, w+4, y, y+4));
	}
	{
		int const x[] = { 1,2,3,4,5 };
		test_range<int const, input_iterator_wrapper> rx(x);
		int w[5] = {};
		auto res = ranges::remove_copy_if(rx, w, [](int a) {return a % 2 == 1; });
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+2);
		int const y[2] = { 2,4 };
		VERIFY(ranges::equal(w, w+2, y, y+2));
	}
	{
		X const x[] = { {3},{1},{4},{1},{5} };
		test_range<X const, forward_iterator_wrapper> rx(x);
		X w[2] = {};
		auto res = ranges::remove_copy_if(rx, w, [](int a) {return a < 4; }, &X::i);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+2);
		int const y[2] = { 4,5 };
		VERIFY(ranges::equal(w, w+2, y, y+2, {}, &X::i));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesRemoveCopyIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_remove_copy_if_test

}	// namespace hamon_algorithm_test
