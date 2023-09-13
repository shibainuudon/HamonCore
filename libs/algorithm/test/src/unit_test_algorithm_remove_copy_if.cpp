/**
 *	@file	unit_test_algorithm_remove_copy_if.cpp
 *
 *	@brief	remove_copy_if のテスト
 */

#include <hamon/algorithm/remove_copy_if.hpp>
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

namespace remove_copy_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CONSTEXPR bool pred1(int a)
{
	return a == 1;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int a) const
	{
		return a > 1;
	}
};

HAMON_CONSTEXPR bool pred3(int a)
{
	return a == 3;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveCopyIfTest1()
{
	{
		const int a[] = {1,2,3,1,3,1,2};
		int b[10] {};
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), pred1);
		VERIFY(ret == hamon::next(hamon::begin(b), 4));
		VERIFY(2 == b[0]);
		VERIFY(3 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(2 == b[3]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveCopyIfTest2()
{
	{
		const int a[] = {1,2,3,1,3,1,2};
		int b[10] {};
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), pred2());
		VERIFY(ret == hamon::next(hamon::begin(b), 3));
		VERIFY(1 == b[0]);
		VERIFY(1 == b[1]);
		VERIFY(1 == b[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveCopyIfTest3()
{
	{
		const hamon::array<int, 7> a = {{1,2,3,1,3,1,2}};
		int b[10] {};
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), pred3);
		VERIFY(ret == hamon::next(hamon::begin(b), 5));
		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(1 == b[2]);
		VERIFY(1 == b[3]);
		VERIFY(2 == b[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RemoveCopyIfTest4()
{
	{
		const hamon::array<int, 4> a = {{1,1,1,1}};
		int b[10] {};
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), pred1);
		VERIFY(ret == hamon::begin(b));
	}
	return true;
}

GTEST_TEST(AlgorithmTest, RemoveCopyIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveCopyIfTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveCopyIfTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveCopyIfTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemoveCopyIfTest4());

	{
		const int a[] = {1,2,3,1,3,1,2};
		hamon::vector<int> b;
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), std::back_inserter(b), pred1);
		(void)ret;
		EXPECT_EQ(4u, b.size());
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(2, b[3]);
	}
	{
		const hamon::array<int, 7> a = {{1,2,3,1,3,1,2}};
		std::list<int> b;
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), std::back_inserter(b), [](int x) { return x >= 3; });
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
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), std::back_inserter(b), [](int x) { return x >= 0; });
		(void)ret;
		EXPECT_TRUE(b.empty());
	}
	{
		const hamon::vector<int> a = {1,2,3,1,3,1,2,2};
		hamon::array<int, 10> b {{}};
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int x) { return x == 2; });
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
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int ) { return true; });
		EXPECT_TRUE(ret == hamon::begin(b));
	}
	{
		const std::list<int> a = {1,2,3,1,3,1,2,1,1};
		int b[10] {};
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int x) { return x == 2; });
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
		const std::list<int> a;
		int b[10] {};
		auto ret = hamon::remove_copy_if(hamon::begin(a), hamon::end(a), hamon::begin(b), [](int ) { return false; });
		EXPECT_TRUE(ret == hamon::begin(b));
	}
}

#undef VERIFY

}	// namespace remove_copy_if_test

}	// namespace hamon_algorithm_test
