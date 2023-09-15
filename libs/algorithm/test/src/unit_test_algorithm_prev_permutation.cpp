/**
 *	@file	unit_test_algorithm_prev_permutation.cpp
 *
 *	@brief	prev_permutation のテスト
 */

#include <hamon/algorithm/prev_permutation.hpp>
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

namespace prev_permutation_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }


HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

inline HAMON_CXX14_CONSTEXPR bool PrevPermutationTest1()
{
	{
		int a[] {3,2,1};

		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a));
			VERIFY(ret);
			VERIFY(3 == a[0]);
			VERIFY(1 == a[1]);
			VERIFY(2 == a[2]);
		}
		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a));
			VERIFY(ret);
			VERIFY(2 == a[0]);
			VERIFY(3 == a[1]);
			VERIFY(1 == a[2]);
		}
		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a));
			VERIFY(ret);
			VERIFY(2 == a[0]);
			VERIFY(1 == a[1]);
			VERIFY(3 == a[2]);
		}
		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a));
			VERIFY(ret);
			VERIFY(1 == a[0]);
			VERIFY(3 == a[1]);
			VERIFY(2 == a[2]);
		}
		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a));
			VERIFY(ret);
			VERIFY(1 == a[0]);
			VERIFY(2 == a[1]);
			VERIFY(3 == a[2]);
		}
		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a));
			VERIFY(!ret);
			VERIFY(3 == a[0]);
			VERIFY(2 == a[1]);
			VERIFY(1 == a[2]);
		}
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PrevPermutationTest2()
{
	{
		hamon::array<int, 4> a {{7,6,5,4}};

		const int expected[][4]
		{
			{ 7, 6, 5, 4 },
			{ 7, 6, 4, 5 },
			{ 7, 5, 6, 4 },
			{ 7, 5, 4, 6 },
			{ 7, 4, 6, 5 },
			{ 7, 4, 5, 6 },
			{ 6, 7, 5, 4 },
			{ 6, 7, 4, 5 },
			{ 6, 5, 7, 4 },
			{ 6, 5, 4, 7 },
			{ 6, 4, 7, 5 },
			{ 6, 4, 5, 7 },
			{ 5, 7, 6, 4 },
			{ 5, 7, 4, 6 },
			{ 5, 6, 7, 4 },
			{ 5, 6, 4, 7 },
			{ 5, 4, 7, 6 },
			{ 5, 4, 6, 7 },
			{ 4, 7, 6, 5 },
			{ 4, 7, 5, 6 },
			{ 4, 6, 7, 5 },
			{ 4, 6, 5, 7 },
			{ 4, 5, 7, 6 },
			{ 4, 5, 6, 7 },
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
		while (hamon::prev_permutation(hamon::begin(a), hamon::end(a), pred1));

		VERIFY(hamon::size(expected) == i);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, PrevPermutationTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PrevPermutationTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PrevPermutationTest2());

	{
		hamon::string a = "abb";
		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a), hamon::greater<>());
			EXPECT_EQ(true, ret);
			EXPECT_EQ("bab", a);
		}
		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a), hamon::greater<>());
			EXPECT_EQ(true, ret);
			EXPECT_EQ("bba", a);
		}
		{
			auto ret = hamon::prev_permutation(hamon::begin(a), hamon::end(a), hamon::greater<>());
			EXPECT_EQ(false, ret);
			EXPECT_EQ("abb", a);
		}
	}
}

#undef VERIFY

}	// namespace prev_permutation_test

}	// namespace hamon_algorithm_test
