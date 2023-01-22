﻿/**
 *	@file	unit_test_algorithm_stable_sort.cpp
 *
 *	@brief	stable_sort のテスト
 */

#include <hamon/algorithm/stable_sort.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>

namespace hamon_algorithm_test
{

namespace stable_sort_test
{

struct Foo
{
	int key;
	float value;
};

bool operator<(const Foo& lhs, const Foo& rhs)
{
	return lhs.key < rhs.key;
}

bool operator>(const Foo& lhs, const Foo& rhs)
{
	return lhs.key > rhs.key;
}

GTEST_TEST(AlgorithmTest, StableSortTest)
{
	{
		Foo a[]
		{
			{ 1, 0.5f },
			{ 2, 1.5f },
			{ 1, 2.5f },
		};

		hamon::stable_sort(hamon::begin(a), hamon::end(a));

		EXPECT_EQ(0.5, a[0].value);
		EXPECT_EQ(2.5, a[1].value);
		EXPECT_EQ(1.5, a[2].value);
	}
	{
		std::array<Foo, 5> a
		{{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
		}};

		hamon::stable_sort(hamon::begin(a), hamon::end(a));

		EXPECT_EQ(1.5, a[0].value);
		EXPECT_EQ(3.5, a[1].value);
		EXPECT_EQ(0.5, a[2].value);
		EXPECT_EQ(2.5, a[3].value);
		EXPECT_EQ(4.5, a[4].value);
	}
	{
		std::vector<Foo> a
		{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
			{ 9, 5.5f },
			{ 2, 6.5f },
			{ 6, 7.5f },
			{ 5, 8.5f },
			{ 3, 9.5f },
		};

		hamon::stable_sort(hamon::begin(a), hamon::end(a));

		EXPECT_EQ(1.5, a[0].value);
		EXPECT_EQ(3.5, a[1].value);
		EXPECT_EQ(6.5, a[2].value);
		EXPECT_EQ(0.5, a[3].value);
		EXPECT_EQ(9.5, a[4].value);
		EXPECT_EQ(2.5, a[5].value);
		EXPECT_EQ(4.5, a[6].value);
		EXPECT_EQ(8.5, a[7].value);
		EXPECT_EQ(7.5, a[8].value);
		EXPECT_EQ(5.5, a[9].value);
	}
	{
		Foo a[]
		{
			{ 1, 0.5f },
			{ 2, 1.5f },
			{ 1, 2.5f },
		};

		hamon::stable_sort(hamon::begin(a), hamon::end(a), hamon::greater<>());

		EXPECT_EQ(1.5, a[0].value);
		EXPECT_EQ(0.5, a[1].value);
		EXPECT_EQ(2.5, a[2].value);
	}
	{
		std::array<Foo, 5> a
		{{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
		}};

		hamon::stable_sort(hamon::begin(a), hamon::end(a), hamon::greater<>());

		EXPECT_EQ(4.5, a[0].value);
		EXPECT_EQ(2.5, a[1].value);
		EXPECT_EQ(0.5, a[2].value);
		EXPECT_EQ(1.5, a[3].value);
		EXPECT_EQ(3.5, a[4].value);
	}
	{
		std::vector<Foo> a
		{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
			{ 9, 5.5f },
			{ 2, 6.5f },
			{ 6, 7.5f },
			{ 5, 8.5f },
			{ 3, 9.5f },
		};

		hamon::stable_sort(hamon::begin(a), hamon::end(a), hamon::greater<>());

		EXPECT_EQ(5.5, a[0].value);
		EXPECT_EQ(7.5, a[1].value);
		EXPECT_EQ(4.5, a[2].value);
		EXPECT_EQ(8.5, a[3].value);
		EXPECT_EQ(2.5, a[4].value);
		EXPECT_EQ(0.5, a[5].value);
		EXPECT_EQ(9.5, a[6].value);
		EXPECT_EQ(6.5, a[7].value);
		EXPECT_EQ(1.5, a[8].value);
		EXPECT_EQ(3.5, a[9].value);
	}
}

}	// namespace stable_sort_test

}	// namespace hamon_algorithm_test
