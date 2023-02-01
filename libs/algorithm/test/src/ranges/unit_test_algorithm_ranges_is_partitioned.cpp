/**
 *	@file	unit_test_algorithm_ranges_is_partitioned.cpp
 *
 *	@brief	ranges::is_partitioned のテスト
 */

#include <hamon/algorithm/ranges/is_partitioned.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_is_partitioned_test
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
		int x[] = { 6,2,2,4,6,1,3,7,5 };
		test_range<int, input_iterator_wrapper> rx(x);
		VERIFY( ranges::is_partitioned(rx, IsEven{}));
		VERIFY(!ranges::is_partitioned(rx, IsOdd{}));
	}
	{
		int x[] = { 1,2,4,6,8,6,4,2 };
		test_range<int, input_iterator_wrapper> rx(x);
		VERIFY(!ranges::is_partitioned(rx, IsEven{}));
		VERIFY( ranges::is_partitioned(rx, IsOdd{}));
	}
	{
		int x[] = { 2,4,6,1,3,5,2 };
		test_range<int, input_iterator_wrapper> rx(x);
		VERIFY(!ranges::is_partitioned(rx, IsEven{}));
		VERIFY(!ranges::is_partitioned(rx, IsOdd{}));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,2,3,4,5,6,1 };
		VERIFY( ranges::is_partitioned(x, x+6, [](int a) { return a<=2; }));
		VERIFY(!ranges::is_partitioned(x, x+7, [](int a) { return a<=2; }));
	}
	{
		int x[] = { 2,4,6,1,3,5 };
		test_range<int, input_iterator_wrapper> rx(x);
		VERIFY( ranges::is_partitioned(rx, [](int a) { return a%2==0; }));
		VERIFY(!ranges::is_partitioned(rx, [](int a) { return a%2==1; }));
	}
	{
		int x[] = { 2,4,6,1,3,5 };
		test_range<int, input_iterator_wrapper> rx(x);
		VERIFY(!ranges::is_partitioned(rx, [](int a) { return a%2==0; }, [](int a) { return a+1; }));
		VERIFY( ranges::is_partitioned(rx, [](int a) { return a%2==1; }, [](int a) { return a+1; }));
	}
	{
		std::vector<int> x {};
		VERIFY(ranges::is_partitioned(x, [](int a) { return a%2==0; }));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIsPartitionedTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_is_partitioned_test

}	// namespace hamon_algorithm_test
