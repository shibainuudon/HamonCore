/**
 *	@file	unit_test_algorithm_reverse.cpp
 *
 *	@brief	reverse のテスト
 */

#include <hamon/algorithm/reverse.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace reverse_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool ReverseTest1()
{
	{
		int a[] { 1,2,3 };
		hamon::reverse(hamon::begin(a), hamon::end(a));
		VERIFY(3 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(1 == a[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ReverseTest2()
{
	{
		int a[] { 4 };
		hamon::reverse(hamon::begin(a), hamon::end(a));
		VERIFY(4 == a[0]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ReverseTest3()
{
	{
		hamon::array<int, 4> a {{ 1,2,3,4 }};
		hamon::reverse(hamon::begin(a), hamon::end(a));
		VERIFY(4 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(1 == a[3]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, ReverseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseTest3());

	{
		std::vector<int> a { 1,2,3,4,5 };
		hamon::reverse(hamon::begin(a), hamon::end(a));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(1, a[4]);
	}
	{
		std::vector<int> a;
		hamon::reverse(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(a.empty());
	}
	{
		std::list<int> a { 1,2 };
		hamon::reverse(hamon::begin(a), hamon::end(a));
		auto it = a.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::list<int> a;
		hamon::reverse(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(a.empty());
	}
}

#undef VERIFY

}	// namespace reverse_test

}	// namespace hamon_algorithm_test
