/**
 *	@file	unit_test_algorithm_generate.cpp
 *
 *	@brief	generate のテスト
 */

#include <hamon/algorithm/generate.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace generate_test
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

inline HAMON_CXX14_CONSTEXPR bool GenerateArrayTest()
{
	{
		int a[5] {};
		hamon::generate(hamon::begin(a), hamon::end(a), pred1());
		VERIFY(0 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(4 == a[4]);
	}
	return true;
}

inline HAMON_CXX17_CONSTEXPR bool GenerateStdArrayTest()
{
	{
		std::array<int, 6> a {{}};
		hamon::generate(hamon::begin(a), hamon::end(a), pred2());
		VERIFY( 3 == a[0]);
		VERIFY( 5 == a[1]);
		VERIFY( 7 == a[2]);
		VERIFY( 9 == a[3]);
		VERIFY(11 == a[4]);
		VERIFY(13 == a[5]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, GenerateTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(GenerateArrayTest());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(GenerateStdArrayTest());

	{
		std::vector<int> a(3);
		hamon::generate(hamon::begin(a), hamon::end(a), pred3);
		EXPECT_EQ(42, a[0]);
		EXPECT_EQ(42, a[1]);
		EXPECT_EQ(42, a[2]);
	}
	{
		int n = 1;
		std::list<int> a(4);
		hamon::generate(hamon::begin(a), hamon::end(a), [&]() { auto t = n; n *= 2; return t;});

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
		hamon::generate(hamon::begin(a), hamon::end(a), [&]() { auto t = n; n *= 2; return t;});
		EXPECT_TRUE(a.empty());

		EXPECT_EQ(1, n);
	}
}

#undef VERIFY

}	// namespace generate_test

}	// namespace hamon_algorithm_test
