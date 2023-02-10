/**
 *	@file	unit_test_algorithm_ranges_set_union.cpp
 *
 *	@brief	ranges::set_union のテスト
 */

#include <hamon/algorithm/ranges/set_union.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_set_union_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 1,3,3,5,5,5 };
		int const y[] = { 2,3,4,5 };
		int z[8] = {};
		test_input_range<int const> rx(x);
		test_input_range<int const> ry(y);
		test_output_range<int> rz(z);
		auto res = ranges::set_union(rx, ry, rz.begin());
		VERIFY(res.in1 == rx.end());
		VERIFY(res.in2 == ry.end());
		VERIFY(res.out == rz.end());
		int const a[] = { 1,2,3,3,4,5,5,5 };
		VERIFY(ranges::equal(z, a));
	}
	{
		int const x[] = { 4,2,1,1,0 };
		int const y[] = { 3,2,1 };
		int z[6] = {};
		test_input_range<int const> rx(x);
		test_input_range<int const> ry(y);
		test_output_range<int> rz(z);
		auto res = ranges::set_union(rx, ry, rz.begin(), ranges::greater{});
		VERIFY(res.in1 == ranges::next(rx.begin(), 5));
		VERIFY(res.in2 == ranges::next(ry.begin(), 3));
		VERIFY(res.out == rz.end());
		int const a[] = { 4,3,2,1,1,0 };
		VERIFY(ranges::equal(z, a));
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
		X const x[] = { {1},{3},{5} };
		X const y[] = { {2},{4},{6} };
		X z[6] = {};
		test_input_range<X const> rx(x);
		test_input_range<X const> ry(y);
		test_output_range<X> rz(z);
		auto res = ranges::set_union(rx, ry, rz.begin(), {}, &X::i, &X::i);
		VERIFY(res.in1 == rx.end());
		VERIFY(res.in2 == ry.end());
		VERIFY(res.out == rz.end());
		int const a[] = { 1,2,3,4,5,6 };
		VERIFY(ranges::equal(z, a, {}, &X::i));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesSetUnionTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_set_union_test

}	// namespace hamon_algorithm_test
