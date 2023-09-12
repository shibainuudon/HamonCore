/**
 *	@file	unit_test_algorithm_generate_n.cpp
 *
 *	@brief	generate_n のテスト
 */

#include <hamon/algorithm/generate_n.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace generate_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct pred1
{
	HAMON_CXX14_CONSTEXPR int operator()()
	{
		return value++;
	}

	int value = 0;
};

struct pred2
{
	HAMON_CXX14_CONSTEXPR int operator()()
	{
		value += 2;
		return value;
	}

	int value = 1;
};

HAMON_CXX11_CONSTEXPR int pred3()
{
	return 42;
}

inline HAMON_CXX14_CONSTEXPR bool GenerateNArrayTest()
{
	{
		int a[5] {};
		auto ret = hamon::generate_n(hamon::begin(a), 5, pred1());
		VERIFY(ret == hamon::end(a));
		VERIFY(0 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(4 == a[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool GenerateNStdArrayTest()
{
	{
		hamon::array<int, 6> a {{}};
		auto ret = hamon::generate_n(hamon::begin(a), 4, pred2());
		VERIFY(ret == hamon::next(hamon::begin(a), 4));
		VERIFY(3 == a[0]);
		VERIFY(5 == a[1]);
		VERIFY(7 == a[2]);
		VERIFY(9 == a[3]);
		VERIFY(0 == a[4]);
		VERIFY(0 == a[5]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, GenerateNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(GenerateNArrayTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(GenerateNStdArrayTest());

	{
		std::vector<int> a(3);
		auto ret = hamon::generate_n(hamon::begin(a), 2, pred3);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		EXPECT_EQ(42, a[0]);
		EXPECT_EQ(42, a[1]);
		EXPECT_EQ( 0, a[2]);
	}
	{
		std::vector<int> a(4);
		auto ret = hamon::generate_n(hamon::begin(a), 0, pred3);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(0, a[1]);
		EXPECT_EQ(0, a[2]);
		EXPECT_EQ(0, a[3]);
	}
	{
		int n = 1;
		std::list<int> a(4);
		auto ret = hamon::generate_n(hamon::begin(a), 4, [&]() { auto t = n; n *= 2; return t;});
		EXPECT_TRUE(ret == hamon::end(a));

		auto it = a.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(8, *it++);
		EXPECT_TRUE(it == a.end());

		EXPECT_EQ(16, n);
	}
	{
		int n = 1;
		std::list<int> a;
		auto ret = hamon::generate_n(hamon::begin(a), 0, [&]() { auto t = n; n *= 2; return t;});
		EXPECT_TRUE(ret == hamon::end(a));
		EXPECT_TRUE(a.empty());
		EXPECT_EQ(1, n);
	}
}

#undef VERIFY

}	// namespace generate_n_test

}	// namespace hamon_algorithm_test
