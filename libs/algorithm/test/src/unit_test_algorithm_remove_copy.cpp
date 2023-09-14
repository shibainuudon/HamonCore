/**
 *	@file	unit_test_algorithm_remove_copy.cpp
 *
 *	@brief	remove_copy のテスト
 */

#include <hamon/algorithm/remove_copy.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace remove_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool RemoveCopyTest1()
{
	{
		const int a[] = {1,2,3,1,3,1,2};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 1);
		VERIFY(ret == hamon::next(hamon::begin(b), 4));
		VERIFY(2 == b[0]);
		VERIFY(3 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(2 == b[3]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveCopyTest2()
{
	{
		const int a[] = {1,2,3,1,3,1,2};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 0);
		VERIFY(ret == hamon::next(hamon::begin(b), 7));
		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(3 == b[4]);
		VERIFY(1 == b[5]);
		VERIFY(2 == b[6]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveCopyTest3()
{
	{
		const hamon::array<int, 7> a = {{1,2,3,1,3,1,2}};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 3);
		VERIFY(ret == hamon::next(hamon::begin(b), 5));
		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(1 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(2 == b[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveCopyTest4()
{
	{
		const hamon::array<int, 4> a = {{1,1,1,1}};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 1);
		VERIFY(ret == hamon::begin(b));
	}
	return true;
}

GTEST_TEST(AlgorithmTest, RemoveCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveCopyTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveCopyTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveCopyTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveCopyTest4());

	{
		const int a[] = {1,2,3,1,3,1,2};
		hamon::vector<int> b;
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b), 1);
		(void)ret;
		EXPECT_EQ(4u, b.size());
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(2, b[3]);
	}
	{
		const hamon::array<int, 7> a = {{1,2,3,1,3,1,2}};
		hamon::list<int> b;
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b), 3);
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::array<int, 4> a = {{1,1,1,1}};
		hamon::vector<int> b;
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), std::back_inserter(b), 1);
		(void)ret;
		EXPECT_TRUE(b.empty());
	}
	{
		const hamon::vector<int> a = {1,2,3,1,3,1,2,2};
		hamon::array<int, 10> b {{}};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 2);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 5));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(1, b[4]);
	}
	{
		const hamon::vector<int> a;
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 2);
		EXPECT_TRUE(ret == hamon::begin(b));
	}
	{
		const hamon::list<int> a = {1,2,3,1,3,1,2,1,1};
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 2);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 7));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(1, b[4]);
		EXPECT_EQ(1, b[5]);
		EXPECT_EQ(1, b[6]);
	}
	{
		const hamon::list<int> a;
		int b[10] {};
		auto ret = hamon::remove_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), 0);
		EXPECT_TRUE(ret == hamon::begin(b));
	}
}

#undef VERIFY

}	// namespace remove_copy_test

}	// namespace hamon_algorithm_test
