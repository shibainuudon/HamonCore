/**
 *	@file	unit_test_algorithm_reverse_copy.cpp
 *
 *	@brief	reverse_copy のテスト
 */

#include <hamon/algorithm/reverse_copy.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace reverse_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool ReverseCopyTest1()
{
	{
		const int a[] { 1,2,3 };
		int b[3] {};
		auto it = hamon::reverse_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(it == hamon::next(hamon::begin(b), 3));
		VERIFY(3 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(1 == b[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ReverseCopyTest2()
{
	{
		const int a[] { 4 };
		int b[3] {};
		auto it = hamon::reverse_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(it == hamon::next(hamon::begin(b), 1));
		VERIFY(4 == b[0]);
		VERIFY(0 == b[1]);
		VERIFY(0 == b[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ReverseCopyTest3()
{
	{
		const int a[] { 1,2,3 };
		hamon::array<int, 5> b {{}};
		auto it = hamon::reverse_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(it == hamon::next(hamon::begin(b), 3));
		VERIFY(3 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(1 == b[2]);
		VERIFY(0 == b[3]);
		VERIFY(0 == b[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ReverseCopyTest4()
{
	{
		const hamon::array<int, 4> a {{ 1,2,3,4 }};
		int b[4] {};
		auto it = hamon::reverse_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(it == hamon::next(hamon::begin(b), 4));
		VERIFY(4 == b[0]);
		VERIFY(3 == b[1]);
		VERIFY(2 == b[2]);
		VERIFY(1 == b[3]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, ReverseCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseCopyTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseCopyTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseCopyTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseCopyTest4());

	{
		const hamon::array<int, 4> a {{ 1,2,3,4 }};
		std::list<int> b;
		hamon::reverse_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b));
		auto it = b.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::vector<int> a { 1,2,3,4,5 };
		hamon::vector<int> b;
		hamon::reverse_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b));
		EXPECT_EQ(5, b[0]);
		EXPECT_EQ(4, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(2, b[3]);
		EXPECT_EQ(1, b[4]);
	}
	{
		const hamon::vector<int> a { 1,2,3,4 };
		int b[4] {};
		auto it = hamon::reverse_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		EXPECT_TRUE(it == hamon::next(hamon::begin(b), 4));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(1, b[3]);
	}
	{
		const hamon::vector<int> a;
		hamon::vector<int> b;
		hamon::reverse_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b));
		EXPECT_TRUE(b.empty());
	}
	{
		const std::list<int> a { 1,2 };
		std::list<int> b;
		hamon::reverse_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b));
		auto it = b.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::list<int> a { 1,2,3 };
		hamon::array<int, 4> b {{}};
		auto it = hamon::reverse_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		EXPECT_TRUE(it == hamon::next(hamon::begin(b), 3));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(0, b[3]);
	}
	{
		const std::list<int> a;
		std::list<int> b;
		hamon::reverse_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b));
		EXPECT_TRUE(b.empty());
	}
}

#undef VERIFY

}	// namespace reverse_copy_test

}	// namespace hamon_algorithm_test
