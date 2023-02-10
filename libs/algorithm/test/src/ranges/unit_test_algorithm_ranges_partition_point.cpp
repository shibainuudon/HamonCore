/**
 *	@file	unit_test_algorithm_ranges_partition_point.cpp
 *
 *	@brief	ranges::partition_point のテスト
 */

#include <hamon/algorithm/ranges/partition_point.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_partition_point_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct LessEqual
{
	int k;
	constexpr bool operator()(int a) const
	{
		return a <= k;
	}
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	for (int k = 1; k <= 7; k++)
	{
		int x[] = { 1,2,3,4,5,6,7 };
		test_forward_range<int> r(x);
		auto pred = LessEqual{k};
		auto middle = ranges::partition_point(r, pred);
		VERIFY(middle == ranges::next(r.begin(), k));
	}
	{
		int x[] = { 1,2,3,4,5,6,7 };
		test_forward_range<int> r(x);
		auto pred = LessEqual{0};
		auto middle = ranges::partition_point(r, pred);
		VERIFY(middle == r.begin());
	}
	{
		int x[] = { 1,2,3,4,5,6,7 };
		test_forward_range<int> r(x);
		auto pred = LessEqual{8};
		auto middle = ranges::partition_point(r, pred);
		VERIFY(middle == ranges::next(r.begin(), 7));
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
		X x[] = { {1},{2},{3},{4},{5} };
		auto middle = ranges::partition_point(x, [](int a) { return a < 6; }, &X::i);
		VERIFY(middle == x+5);
	}
	{
		X x[] = { {1},{2},{3},{4},{5} };
		auto middle = ranges::partition_point(x, [](int a) { return a < 0; }, &X::i);
		VERIFY(middle == x+0);
	}
	{
		std::vector<int> x {};
		auto middle = ranges::partition_point(x, [](int a) { return a < 0; });
		VERIFY(middle == x.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPartitionPointTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_partition_point_test

}	// namespace hamon_algorithm_test
