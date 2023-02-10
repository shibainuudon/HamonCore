/**
 *	@file	unit_test_algorithm_ranges_remove_if.cpp
 *
 *	@brief	ranges::remove_if のテスト
 */

#include <hamon/algorithm/ranges/remove_if.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_remove_if_test
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
		int x[] = { 1,2,3,4,5 };
		auto res = ranges::remove_if(x, x+5, IsEven{});
		VERIFY(res.begin() == x+3 && res.end() == x+5);
		int const y[] = { 1,3,5 };
		VERIFY(ranges::equal(x, x+3, y, y+3));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_forward_range<int> rx(x);
		auto res = ranges::remove_if(rx, IsOdd{});
		VERIFY(res.begin() == ranges::next(rx.begin(), 2) && res.end() == rx.end());
		int const y[] = { 2,4 };
		VERIFY(ranges::equal(x, x+2, y, y+2));
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
		int x[] = { 1,2,3,4,5 };
		auto res = ranges::remove_if(x, x+5, [](int a) {return a == 3; });
		VERIFY(res.begin() == x+4 && res.end() == x+5);
		int const y[4] = { 1,2,4,5 };
		VERIFY(ranges::equal(x, x+4, y, y+4));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto res = ranges::remove_if(x, x+5, [](int a) {return a == 9; });
		VERIFY(res.begin() == x+5 && res.end() == x+5);
		int const y[5] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, x+5, y, y+5));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_forward_range<int> rx(x);
		auto res = ranges::remove_if(rx, [](int a) {return a % 2 == 1; });
		VERIFY(res.begin() == ranges::next(rx.begin(), 2) && res.end() == rx.end());
		int const y[2] = { 2,4 };
		VERIFY(ranges::equal(x, x+2, y, y+2));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_forward_range<int> rx(x);
		auto res = ranges::remove_if(rx, [](int a) {return a < 9; });
		VERIFY(res.begin() == rx.begin() && res.end() == rx.end());
	}
	{
		X x[] = { {3},{1},{4},{1},{5} };
		test_forward_range<X> rx(x);
		auto res = ranges::remove_if(rx, [](int a) {return a < 4; }, &X::i);
		VERIFY(res.begin() == ranges::next(rx.begin(), 2) && res.end() == rx.end());
		int const y[2] = { 4,5 };
		VERIFY(ranges::equal(x, x+2, y, y+2, {}, &X::i));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesRemoveIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_remove_if_test

}	// namespace hamon_algorithm_test
