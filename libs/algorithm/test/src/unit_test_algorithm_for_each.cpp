/**
 *	@file	unit_test_algorithm_for_each.cpp
 *
 *	@brief	for_each のテスト
 */

#include <hamon/algorithm/for_each.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace for_each_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR void func1(int& x)
{
	x++;
}

struct Sum
{
	HAMON_CXX11_CONSTEXPR Sum() : n(0) {}
	HAMON_CXX14_CONSTEXPR void operator()(int x) { n += x; }
	HAMON_CXX11_CONSTEXPR int get() const { return n; }
	HAMON_CXX11_CONSTEXPR Sum(Sum&& rhs) noexcept : n(hamon::move(rhs.n)) {}
	HAMON_CXX14_CONSTEXPR Sum& operator=(Sum&& rhs) noexcept { n = hamon::move(rhs.n); return *this; }

private:
	Sum(Sum const&) = delete;
	Sum& operator=(Sum const&) = delete;

	int n;
};

inline HAMON_CXX14_CONSTEXPR bool ForEachArrayTest()
{
	{
		int a [] { 3, 1, 4, 1, 5 };
		auto f = hamon::for_each(hamon::begin(a), hamon::end(a), func1);
		VERIFY(4 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(2 == a[3]);
		VERIFY(6 == a[4]);

		int n = 2;
		f(n);
		VERIFY(3 == n);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ForEachStdArrayTest()
{
	{
		const hamon::array<int, 5> a {{ 3, 1, 4, 1, 5 }};
		auto s = hamon::for_each(hamon::begin(a), hamon::end(a), Sum());
		VERIFY(14 == s.get());
	}

	return true;
}

GTEST_TEST(AlgorithmTest, ForEachTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ForEachArrayTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ForEachStdArrayTest());

	{
		std::vector<int> v { 1, 2, 3 };
		auto f = hamon::for_each(hamon::begin(v), hamon::end(v), [](int& x) { x *= 2; });
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(6, v[2]);

		int n = 2;
		f(n);
		EXPECT_EQ(4, n);
	}
	{
		const std::list<int> l { 5, 6, 7, 8 };
		auto s = hamon::for_each(hamon::begin(l), hamon::end(l), Sum());
		EXPECT_EQ(26, s.get());
	}
}

#undef VERIFY

}	// namespace for_each_test

}	// namespace hamon_algorithm_test
