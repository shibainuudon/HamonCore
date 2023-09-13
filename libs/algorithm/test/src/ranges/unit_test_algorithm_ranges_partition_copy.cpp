/**
 *	@file	unit_test_algorithm_ranges_partition_copy.cpp
 *
 *	@brief	ranges::partition_copy のテスト
 */

#include <hamon/algorithm/ranges/partition_copy.hpp>
#include <hamon/algorithm/ranges/none_of.hpp>
#include <hamon/algorithm/ranges/all_of.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_partition_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsEven
{
	constexpr bool operator()(int a) const
	{
		return a%2==0;
	}
};

struct IsOdd
{
	constexpr bool operator()(int a) const
	{
		return a%2==1;
	}
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 3,1,4,1,5,9,2,6,5,3 };
		int y[3] = {};
		int z[7] = {};
		test_input_range<int const> rx(x);
		test_output_range<int> ry(y);
		test_output_range<int> rz(z);
		auto pred = IsEven{};
		auto res = ranges::partition_copy(rx, ry.begin(), rz.begin(), pred);
		VERIFY(res.in   == rx.end());
		VERIFY(res.out1 == ry.end());
		VERIFY(res.out2 == rz.end());
		VERIFY(ranges::all_of(y, pred));
		VERIFY(ranges::none_of(z, pred));
	}
	{
		int const x[] = { 1,3,5,7,9 };
		int y[5] = {};
		int z[5] = {};
		test_input_range<int const> rx(x);
		test_output_range<int> ry(y);
		test_output_range<int> rz(z);
		auto pred = IsOdd{};
		auto res = ranges::partition_copy(rx, ry.begin(), rz.begin(), pred);
		VERIFY(res.in.m_ptr   == x+5);
		VERIFY(res.out1.m_ptr == y+5);
		VERIFY(res.out2.m_ptr == z+0);
		VERIFY(ranges::all_of(y, y+5, pred));
		VERIFY(ranges::none_of(z, z+0, pred));
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
		X x[] = { {1},{2},{3},{4},{5},{6},{7},{8},{9} };
		X y[4] = {};
		X z[5] = {};
		test_input_range<X> rx(x);
		test_output_range<X> ry(y);
		test_output_range<X> rz(z);
		auto pred = [](int a) { return a%2==0; };
		auto proj = &X::i;
		auto res = ranges::partition_copy(rx, ry.begin(), rz.begin(), pred, proj);
		VERIFY(res.in   == rx.end());
		VERIFY(res.out1 == ry.end());
		VERIFY(res.out2 == rz.end());
		VERIFY(ranges::all_of(y, pred, proj));
		VERIFY(ranges::none_of(z, pred, proj));
	}
	{
		hamon::vector<int> x {};
		int y[1] = {};
		int z[1] = {};
		auto res = ranges::partition_copy(x, y, z, [](int a) { return a%2==0; });
		VERIFY(res.in   == x.end());
		VERIFY(res.out1 == y);
		VERIFY(res.out2 == z);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPartitionCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_partition_copy_test

}	// namespace hamon_algorithm_test
