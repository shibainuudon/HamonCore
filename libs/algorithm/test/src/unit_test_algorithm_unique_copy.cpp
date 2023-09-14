/**
 *	@file	unit_test_algorithm_unique_copy.cpp
 *
 *	@brief	unique_copy のテスト
 */

#include <hamon/algorithm/unique_copy.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace unique_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

bool pred1(int x, int y)
{
	return x == y;
}

struct pred2
{
	bool operator()(int x, int y) const
	{
		return x == y;
	}
};

inline HAMON_CXX14_CONSTEXPR bool UniqueCopyTest1()
{
	{
		const int a[] { 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 };
		int b[12] {};
		auto ret = hamon::unique_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(ret == hamon::next(hamon::begin(b), 10));

		VERIFY(2 == b[0]);
		VERIFY(5 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(2 == b[4]);
		VERIFY(4 == b[5]);
		VERIFY(2 == b[6]);
		VERIFY(1 == b[7]);
		VERIFY(4 == b[8]);
		VERIFY(3 == b[9]);
		VERIFY(0 == b[10]);
		VERIFY(0 == b[11]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool UniqueCopyTest2()
{
	{
		const int a[] { 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 };
		hamon::array<int, 12> b {{}};
		auto ret = hamon::unique_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(ret == hamon::next(hamon::begin(b), 10));

		VERIFY(2 == b[0]);
		VERIFY(5 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(2 == b[4]);
		VERIFY(4 == b[5]);
		VERIFY(2 == b[6]);
		VERIFY(1 == b[7]);
		VERIFY(4 == b[8]);
		VERIFY(3 == b[9]);
		VERIFY(0 == b[10]);
		VERIFY(0 == b[11]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, UniqueCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UniqueCopyTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UniqueCopyTest2());

	{
		const hamon::array<int, 10> a {{ 1,1,2,2,2,3,4,4,5,5 }};
		hamon::vector<int> b(10);
		auto ret = hamon::unique_copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 5));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(4, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(0, b[5]);
		EXPECT_EQ(0, b[6]);
		EXPECT_EQ(0, b[7]);
		EXPECT_EQ(0, b[8]);
		EXPECT_EQ(0, b[9]);
	}
	{
		const hamon::vector<int> a { 1,4,4,2,1,1,3,3,3 };
		hamon::list<int> b;
		auto ret = hamon::unique_copy(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), pred1);
		(void)ret;

		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::vector<int> a;
		int b[3] {};
		auto ret = hamon::unique_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int, int){ return true; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 0));
		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
	}
	{
		const hamon::list<int> a { 1,1,1,4,4,2,3,3,2 };
		hamon::vector<int> b;
		auto ret = hamon::unique_copy(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), pred2());
		(void)ret;

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(4, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(2, b[4]);
	}
	{
		const hamon::list<int> a;
		hamon::vector<int> b;
		auto ret = hamon::unique_copy(hamon::begin(a), hamon::end(a), hamon::back_inserter(b), [](int, int){ return false; });
		(void)ret;
		EXPECT_TRUE(b.empty());
	}
	{
		std::stringstream ss("1 1 1 2 2 3 33");
		std::istream_iterator<int> ii_first(ss);
		std::istream_iterator<int> ii_last;
		hamon::vector<int> b;
		auto ret = hamon::unique_copy(ii_first, ii_last, hamon::back_inserter(b));
		(void)ret;
		EXPECT_EQ( 4u, b.size());
		EXPECT_EQ( 1, b[0]);
		EXPECT_EQ( 2, b[1]);
		EXPECT_EQ( 3, b[2]);
		EXPECT_EQ(33, b[3]);
	}
}

#undef VERIFY

}	// namespace unique_copy_test

}	// namespace hamon_algorithm_test
