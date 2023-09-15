/**
 *	@file	unit_test_algorithm_next_permutation.cpp
 *
 *	@brief	next_permutation のテスト
 */

#include <hamon/algorithm/next_permutation.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/size.hpp>
#include <hamon/array.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace next_permutation_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

inline HAMON_CXX14_CONSTEXPR bool NextPermutationTest1()
{
	int a[] {1,2,3};

	{
		auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a));
		VERIFY(ret);
		VERIFY(1 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(2 == a[2]);
	}
	{
		auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a));
		VERIFY(ret);
		VERIFY(2 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(3 == a[2]);
	}
	{
		auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a));
		VERIFY(ret);
		VERIFY(2 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(1 == a[2]);
	}
	{
		auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a));
		VERIFY(ret);
		VERIFY(3 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
	}
	{
		auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a));
		VERIFY(ret);
		VERIFY(3 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(1 == a[2]);
	}
	{
		auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a));
		VERIFY(!ret);
		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
	}
	
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool NextPermutationTest2()
{
	{
		hamon::array<int, 4> a {{4,5,6,7}};

		const int expected[][4]
		{
			{ 4, 5, 6, 7 },
			{ 4, 5, 7, 6 },
			{ 4, 6, 5, 7 },
			{ 4, 6, 7, 5 },
			{ 4, 7, 5, 6 },
			{ 4, 7, 6, 5 },
			{ 5, 4, 6, 7 },
			{ 5, 4, 7, 6 },
			{ 5, 6, 4, 7 },
			{ 5, 6, 7, 4 },
			{ 5, 7, 4, 6 },
			{ 5, 7, 6, 4 },
			{ 6, 4, 5, 7 },
			{ 6, 4, 7, 5 },
			{ 6, 5, 4, 7 },
			{ 6, 5, 7, 4 },
			{ 6, 7, 4, 5 },
			{ 6, 7, 5, 4 },
			{ 7, 4, 5, 6 },
			{ 7, 4, 6, 5 },
			{ 7, 5, 4, 6 },
			{ 7, 5, 6, 4 },
			{ 7, 6, 4, 5 },
			{ 7, 6, 5, 4 },
		};

		hamon::size_t i = 0;

		do
		{
			VERIFY(
				hamon::equal(
					hamon::begin(a), hamon::end(a),
					hamon::begin(expected[i])));
			++i;
		}
		while (hamon::next_permutation(hamon::begin(a), hamon::end(a), pred1));

		VERIFY(hamon::size(expected) == i);
	}

	return true;
}

GTEST_TEST(AlgorithmTest, NextPermutationTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NextPermutationTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NextPermutationTest2());

	{
		hamon::string a = "baa";
		{
			auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a), hamon::greater<>());
			EXPECT_EQ(true, ret);
			EXPECT_EQ("aba", a);
		}
		{
			auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a), hamon::greater<>());
			EXPECT_EQ(true, ret);
			EXPECT_EQ("aab", a);
		}
		{
			auto ret = hamon::next_permutation(hamon::begin(a), hamon::end(a), hamon::greater<>());
			EXPECT_EQ(false, ret);
			EXPECT_EQ("baa", a);
		}
	}
}

#undef VERIFY

}	// namespace next_permutation_test

}	// namespace hamon_algorithm_test
