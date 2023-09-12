/**
 *	@file	unit_test_algorithm_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 */

#include <hamon/algorithm/iter_swap.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace iter_swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool IterSwapTest1()
{
	int a1[] = {1, 2, 3};
	int a2[] = {4, 5, 6};

	hamon::iter_swap(hamon::begin(a1), hamon::begin(a2));

	VERIFY( 4 == a1[0]);
	VERIFY( 2 == a1[1]);
	VERIFY( 3 == a1[2]);
	VERIFY( 1 == a2[0]);
	VERIFY( 5 == a2[1]);
	VERIFY( 6 == a2[2]);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool IterSwapTest2()
{
	hamon::array<int, 3> a1 {{ 7, 8, 9}};
	hamon::array<int, 3> a2 {{10,11,12}};

	hamon::iter_swap(hamon::begin(a1), hamon::begin(a2) + 2);

	VERIFY(12 == a1[0]);
	VERIFY( 8 == a1[1]);
	VERIFY( 9 == a1[2]);
	VERIFY(10 == a2[0]);
	VERIFY(11 == a2[1]);
	VERIFY( 7 == a2[2]);

	return true;
}

GTEST_TEST(AlgorithmTest, IterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IterSwapTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(IterSwapTest2());


	{
		std::vector<int> v1{13,14,15};
		std::vector<int> v2{16,17,18};
		hamon::iter_swap(hamon::begin(v1), hamon::begin(v2));
		EXPECT_EQ(16, v1[0]);
		EXPECT_EQ(14, v1[1]);
		EXPECT_EQ(15, v1[2]);
		EXPECT_EQ(13, v2[0]);
		EXPECT_EQ(17, v2[1]);
		EXPECT_EQ(18, v2[2]);
	}

	{
		std::list<int> l1{19,20,21};
		std::list<int> l2{22,23,24};
		hamon::iter_swap(++hamon::begin(l1), hamon::begin(l2));
		{
			auto i = l1.begin();
			EXPECT_EQ(19, *i++);
			EXPECT_EQ(22, *i++);
			EXPECT_EQ(21, *i++);
		}
		{
			auto i = l2.begin();
			EXPECT_EQ(20, *i++);
			EXPECT_EQ(23, *i++);
			EXPECT_EQ(24, *i++);
		}
	}

	{
		int a1[] = {1, 2, 3};
		std::list<int> l1{19,20,21};
		hamon::iter_swap(hamon::begin(a1), hamon::begin(l1));
		EXPECT_EQ(19, a1[0]);
		EXPECT_EQ( 2, a1[1]);
		EXPECT_EQ( 3, a1[2]);
		{
			auto i = l1.begin();
			EXPECT_EQ( 1, *i++);
			EXPECT_EQ(20, *i++);
			EXPECT_EQ(21, *i++);
		}
	}
}

#undef VERIFY

}	// namespace iter_swap_test

}	// namespace hamon_algorithm_test
