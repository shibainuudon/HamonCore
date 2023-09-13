/**
 *	@file	unit_test_algorithm_for_each_n.cpp
 *
 *	@brief	for_each_n のテスト
 */

#include <hamon/algorithm/for_each_n.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace for_each_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR void func1(int& x)
{
	x++;
}

struct Sum
{
	HAMON_CXX11_CONSTEXPR Sum(int* p) : m_p(p) {}
	HAMON_CXX14_CONSTEXPR void operator()(int x) { *m_p += x; }
	HAMON_CXX11_CONSTEXPR Sum(Sum&& rhs) noexcept : m_p(hamon::move(rhs.m_p)) {}
	HAMON_CXX14_CONSTEXPR Sum& operator=(Sum&& rhs) noexcept { m_p = hamon::move(rhs.m_p); return *this; }

private:
	Sum(Sum const&) = delete;
	Sum& operator=(Sum const&) = delete;

	int* m_p;
};

inline HAMON_CXX14_CONSTEXPR bool ForEachNArrayTest()
{
	{
		int a [] { 3, 1, 4, 1, 5 };
		auto i = hamon::for_each_n(hamon::begin(a), 5, func1);
		VERIFY(4 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(2 == a[3]);
		VERIFY(6 == a[4]);
		VERIFY(i == hamon::end(a));
	}
	{
		int a [] { 3, 1, 4, 1, 5 };
		auto i = hamon::for_each_n(hamon::begin(a), 3, func1);
		VERIFY(4 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(5 == a[4]);
		VERIFY(i == hamon::next(hamon::begin(a), 3));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ForEachNStdArrayTest()
{
	{
		const hamon::array<int, 5> a {{ 3, 1, 4, 1, 5 }};
		int n = 0;
		auto i = hamon::for_each_n(hamon::begin(a), a.size(), Sum(&n));
		VERIFY(14 == n);
		VERIFY(i == hamon::end(a));
	}
	{
		const hamon::array<int, 5> a {{ 3, 1, 4, 1, 5 }};
		int n = 0;
		auto i = hamon::for_each_n(hamon::begin(a), a.size() - 1, Sum(&n));
		VERIFY(9 == n);
		VERIFY(i == hamon::next(hamon::begin(a), 4));
	}
	return true;
}

GTEST_TEST(AlgorithmTest, ForEachNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ForEachNArrayTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ForEachNStdArrayTest());

	{
		hamon::vector<int> v { 1, 2, 3 };
		auto i = hamon::for_each_n(hamon::begin(v), v.size(), [](int& x) { x *= 2; });
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(6, v[2]);
		EXPECT_TRUE(i == hamon::end(v));
	}
	{
		hamon::vector<int> v { 1, 2, 3 };
		auto i = hamon::for_each_n(hamon::begin(v), 1, [](int& x) { x *= 2; });
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_TRUE(i == hamon::next(hamon::begin(v), 1));
	}
	{
		const std::list<int> l { 5, 6, 7, 8 };
		int n = 0;
		auto i = hamon::for_each_n(hamon::begin(l), l.size(), Sum(&n));
		EXPECT_EQ(26, n);
		EXPECT_TRUE(i == hamon::end(l));
	}
	{
		const std::list<int> l { 5, 6, 7, 8 };
		int n = 0;
		auto i = hamon::for_each_n(hamon::begin(l), 2, Sum(&n));
		EXPECT_EQ(11, n);
		EXPECT_TRUE(i == hamon::next(hamon::begin(l), 2));
	}
}

#undef VERIFY

}	// namespace for_each_n_test

}	// namespace hamon_algorithm_test
