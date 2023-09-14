/**
 *	@file	unit_test_algorithm_fill.cpp
 *
 *	@brief	fill のテスト
 */

#include <hamon/algorithm/fill.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace fill_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool FillTestArray()
{
	{
		int a[3]{};
		hamon::fill(hamon::begin(a), hamon::end(a), 42);
		VERIFY(42 == a[0]);
		VERIFY(42 == a[1]);
		VERIFY(42 == a[2]);
	}
	{
		int a[5]{};
		hamon::fill(a, a + 4, 1);
		VERIFY(1 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(1 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(0 == a[4]);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool FillTestStdArray()
{
	{
		hamon::array<int, 4> a{ { 1, 2, 3, 4 } };
		hamon::fill(hamon::begin(a), hamon::end(a), -1);
		VERIFY(-1 == a[0]);
		VERIFY(-1 == a[1]);
		VERIFY(-1 == a[2]);
		VERIFY(-1 == a[3]);
	}

	return true;
}

GTEST_TEST(AlgorithmTest, FillTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FillTestArray());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FillTestStdArray());

	{
		hamon::vector<int> a(5);
		hamon::fill(hamon::begin(a), hamon::end(a), 3);
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(3, a[4]);
	}
	{
		hamon::vector<int> a;
		hamon::fill(hamon::begin(a), hamon::end(a), 3);
		EXPECT_TRUE(a.empty());
	}
	{
		hamon::list<int> a(3);
		hamon::fill(hamon::begin(a), hamon::end(a), 4);
		auto it = a.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		hamon::list<int> a;
		hamon::fill(hamon::begin(a), hamon::end(a), 0);
		EXPECT_TRUE(a.empty());
	}
}

#undef VERIFY

}	// namespace fill_test

}	// namespace hamon_algorithm_test
