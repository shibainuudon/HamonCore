/**
 *	@file	unit_test_algorithm_ranges_upper_bound.cpp
 *
 *	@brief	ranges::upper_bound のテスト
 */

#include <hamon/algorithm/ranges/upper_bound.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_upper_bound_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	for (int i = 0; i < 8; ++i)
	{
		int x[] = {0,1,2,3,4,5,6,7};
		test_forward_range<int> r(x);
		auto res = ranges::upper_bound(r, i);
		VERIFY(res == ranges::next(r.begin(), std::ptrdiff_t(i) + 1));
	}
	for (int i = 0; i < 8; ++i)
	{
		int x[] = {7,6,5,4,3,2,1,0};
		test_forward_range<int> r(x);
		auto res = ranges::upper_bound(r, i, ranges::greater{});
		VERIFY(res == ranges::next(r.begin(), std::ptrdiff_t(7) - i + 1));
	}
	{
		int x[] = {0,0,1,1,1,2,2,2,2};
		auto res = ranges::upper_bound(x, 0);
		VERIFY(res == ranges::next(x, 2));
	}
	{
		int x[] = {0,0,1,1,1,2,2,2,2};
		auto res = ranges::upper_bound(x, 1);
		VERIFY(res == ranges::next(x, 5));
	}
	{
		int x[] = {0,0,1,1,1,2,2,2,2};
		auto res = ranges::upper_bound(x, 2);
		VERIFY(res == ranges::next(x, 9));
	}
	{
		int x[] = {0,1,2,3,4,5,6,7};
		auto res = ranges::upper_bound(x, 9);
		VERIFY(res == ranges::next(x, 8));
	}
	{
		int x[] = {7,6,5,4,3,2,1,0};
		auto res = ranges::upper_bound(x, -1, ranges::greater{});
		VERIFY(res == ranges::next(x, 8));
	}
	{
		int x[] = {0,1,2,3,4,5,6,7};
		auto res = ranges::upper_bound(x, x, 5);
		VERIFY(res == ranges::next(x, 0));
	}
	{
		int x[] = {7,6,5,4,3,2,1,0};
		auto res = ranges::upper_bound(x, x, 5, ranges::greater{});
		VERIFY(res == ranges::next(x, 0));
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
		X const x[] = { {0},{1},{1},{2},{2},{2},{4} };
		VERIFY(ranges::upper_bound(x, 0, {}, &X::i) == ranges::next(x, 1));
		VERIFY(ranges::upper_bound(x, 1, {}, &X::i) == ranges::next(x, 3));
		VERIFY(ranges::upper_bound(x, 2, {}, &X::i) == ranges::next(x, 6));
		VERIFY(ranges::upper_bound(x, 3, {}, &X::i) == ranges::next(x, 6));
		VERIFY(ranges::upper_bound(x, 4, {}, &X::i) == ranges::next(x, 7));
		VERIFY(ranges::upper_bound(x, 5, {}, &X::i) == ranges::next(x, 7));
	}
	{
		auto pred = ranges::greater{};
		X const x[] = { {5},{5},{5},{4},{3},{2},{1} };
		VERIFY(ranges::upper_bound(x, 6, pred, &X::i) == ranges::next(x, 0));
		VERIFY(ranges::upper_bound(x, 5, pred, &X::i) == ranges::next(x, 3));
		VERIFY(ranges::upper_bound(x, 4, pred, &X::i) == ranges::next(x, 4));
		VERIFY(ranges::upper_bound(x, 3, pred, &X::i) == ranges::next(x, 5));
		VERIFY(ranges::upper_bound(x, 2, pred, &X::i) == ranges::next(x, 6));
		VERIFY(ranges::upper_bound(x, 1, pred, &X::i) == ranges::next(x, 7));
		VERIFY(ranges::upper_bound(x, 0, pred, &X::i) == ranges::next(x, 7));
	}
	{
		std::forward_list<int> x {};
		VERIFY(ranges::upper_bound(x, 0) == x.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesUpperBoundTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_upper_bound_test

}	// namespace hamon_algorithm_test
