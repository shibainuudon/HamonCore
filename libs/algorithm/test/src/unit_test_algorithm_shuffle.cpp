/**
 *	@file	unit_test_algorithm_shuffle.cpp
 *
 *	@brief	shuffle のテスト
 */

#include <hamon/algorithm/shuffle.hpp>
#include <hamon/algorithm/is_sorted.hpp>
#include <hamon/algorithm/is_unique.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/random/engines/xorshift.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace hamon_algorithm_test
{

namespace shuffle_test
{

GTEST_TEST(AlgorithmTest, ShuffleTest)
{
	auto g = hamon::xorshift32();

	{
		int a[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		EXPECT_TRUE (hamon::is_sorted(hamon::begin(a), hamon::end(a)));
		EXPECT_TRUE (hamon::is_unique(hamon::begin(a), hamon::end(a)));
		hamon::shuffle(hamon::begin(a), hamon::end(a), g);
		EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
		EXPECT_TRUE (hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		int a1[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		int a2[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), hamon::end(a2)));
		hamon::shuffle(hamon::begin(a1), hamon::end(a1), g);
		hamon::shuffle(hamon::begin(a2), hamon::end(a2), g);
		EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), hamon::end(a2)));
	}
	{
		hamon::array<int, 11> a{ { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
		EXPECT_TRUE (hamon::is_sorted(hamon::begin(a), hamon::end(a)));
		EXPECT_TRUE (hamon::is_unique(hamon::begin(a), hamon::end(a)));
		hamon::shuffle(hamon::begin(a), hamon::end(a), g);
		EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
		EXPECT_TRUE (hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
	{
		std::vector<int> a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		EXPECT_TRUE (hamon::is_sorted(hamon::begin(a), hamon::end(a)));
		EXPECT_TRUE (hamon::is_unique(hamon::begin(a), hamon::end(a)));
		hamon::shuffle(hamon::begin(a), hamon::end(a), g);
		EXPECT_FALSE(hamon::is_sorted(hamon::begin(a), hamon::end(a)));
		EXPECT_TRUE (hamon::is_unique(hamon::begin(a), hamon::end(a)));
	}
}

}	// namespace shuffle_test

}	// namespace hamon_algorithm_test
