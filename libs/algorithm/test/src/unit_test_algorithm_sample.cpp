﻿/**
 *	@file	unit_test_algorithm_sample.cpp
 *
 *	@brief	sample のテスト
 */

#include <hamon/algorithm/sample.hpp>
#include <hamon/random/engines/xorshift.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <list>
#include <forward_list>
#include <iterator>

namespace hamon_algorithm_test
{

namespace sample_test
{

GTEST_TEST(AlgorithmTest, SampleTest)
{
	auto g = hamon::xorshift32();

	{
		int const a[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::vector<int> out;
		auto i = hamon::sample(
			hamon::begin(a), hamon::end(a),
			std::back_inserter(out),
			5, g);
		(void)i;
		EXPECT_EQ(5u, out.size());
		EXPECT_TRUE(0 <= out[0] && out[0] <= 9);
		EXPECT_TRUE(0 <= out[1] && out[1] <= 9);
		EXPECT_TRUE(0 <= out[2] && out[2] <= 9);
		EXPECT_TRUE(0 <= out[3] && out[3] <= 9);
		EXPECT_TRUE(0 <= out[4] && out[4] <= 9);
	}
	{
		std::vector<int> const a {10, 11, 12, 13, 14, 15, 16};
		int out[4] {};
		auto i = hamon::sample(
			hamon::begin(a), hamon::end(a),
			out,
			3, g);
		EXPECT_TRUE(10 <= out[0] && out[0] <= 16);
		EXPECT_TRUE(10 <= out[1] && out[1] <= 16);
		EXPECT_TRUE(10 <= out[2] && out[2] <= 16);
		EXPECT_EQ(0, out[3]);
		EXPECT_TRUE(i == hamon::next(hamon::begin(out), 3));
	}
	{
		std::forward_list<int> const a {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::list<int> out;
		auto i = hamon::sample(
			hamon::begin(a), hamon::end(a),
			std::back_inserter(out),
			3, g);
		(void)i;
		auto it = hamon::begin(out);
		EXPECT_TRUE(0 <= *it && *it <= 9); ++it;
		EXPECT_TRUE(0 <= *it && *it <= 9); ++it;
		EXPECT_TRUE(0 <= *it && *it <= 9); ++it;
		EXPECT_TRUE(it == hamon::end(out));
	}
	{
		std::stringstream ss("0 1 2 3 4 5 6 7 8 9");
		std::istream_iterator<int> ii_first(ss);
		std::istream_iterator<int> ii_last;
		int out[4] {};
		auto i = hamon::sample(
			ii_first, ii_last,
			out,
			4, g);
		EXPECT_TRUE(0 <= out[0] && out[0] <= 9);
		EXPECT_TRUE(0 <= out[1] && out[1] <= 9);
		EXPECT_TRUE(0 <= out[2] && out[2] <= 9);
		EXPECT_TRUE(0 <= out[3] && out[3] <= 9);
		EXPECT_TRUE(i == hamon::end(out));
	}
	{
		int const a[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::vector<int> out;
		auto i = hamon::sample(
			hamon::begin(a), hamon::end(a),
			std::back_inserter(out),
			10, g);
		(void)i;
		EXPECT_EQ(10u, out.size());
		EXPECT_EQ(0, out[0]);
		EXPECT_EQ(1, out[1]);
		EXPECT_EQ(2, out[2]);
		EXPECT_EQ(3, out[3]);
		EXPECT_EQ(4, out[4]);
		EXPECT_EQ(5, out[5]);
		EXPECT_EQ(6, out[6]);
		EXPECT_EQ(7, out[7]);
		EXPECT_EQ(8, out[8]);
		EXPECT_EQ(9, out[9]);
	}
	{
		int const a[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::vector<int> out;
		auto i = hamon::sample(
			hamon::begin(a), hamon::end(a),
			std::back_inserter(out),
			20, g);
		(void)i;
		EXPECT_EQ(10u, out.size());
		EXPECT_EQ(0, out[0]);
		EXPECT_EQ(1, out[1]);
		EXPECT_EQ(2, out[2]);
		EXPECT_EQ(3, out[3]);
		EXPECT_EQ(4, out[4]);
		EXPECT_EQ(5, out[5]);
		EXPECT_EQ(6, out[6]);
		EXPECT_EQ(7, out[7]);
		EXPECT_EQ(8, out[8]);
		EXPECT_EQ(9, out[9]);
	}
	{
		std::list<int> a {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::vector<int> out;
		auto i = hamon::sample(
			hamon::begin(a), hamon::end(a),
			std::back_inserter(out),
			0, g);
		(void)i;
		EXPECT_EQ(0u, out.size());
	}
}

}	// namespace sample_test

}	// namespace hamon_algorithm_test
