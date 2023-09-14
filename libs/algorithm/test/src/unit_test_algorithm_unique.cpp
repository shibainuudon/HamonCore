/**
 *	@file	unit_test_algorithm_unique.cpp
 *
 *	@brief	unique のテスト
 */

#include <hamon/algorithm/unique.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <memory>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace unique_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

bool pred1(const std::shared_ptr<int>& x, const std::shared_ptr<int>& y)
{
	return *x == *y;
}

struct pred2
{
	bool operator()(const std::unique_ptr<int>& x, const std::unique_ptr<int>& y) const
	{
		return *x == *y;
	}
};

inline HAMON_CXX14_CONSTEXPR bool UniqueTest1()
{
	{
		int a[] = { 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 };
		auto ret = hamon::unique(hamon::begin(a), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 10));

		VERIFY(2 == a[0]);
		VERIFY(5 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);
		VERIFY(4 == a[5]);
		VERIFY(2 == a[6]);
		VERIFY(1 == a[7]);
		VERIFY(4 == a[8]);
		VERIFY(3 == a[9]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool UniqueTest2()
{
	{
		hamon::array<int, 10> a = {{ 1,1,2,2,2,3,4,4,5,5 }};
		auto ret = hamon::unique(hamon::begin(a), hamon::end(a));
		VERIFY(ret == hamon::next(hamon::begin(a), 5));

		VERIFY(1 == a[0]);
		VERIFY(2 == a[1]);
		VERIFY(3 == a[2]);
		VERIFY(4 == a[3]);
		VERIFY(5 == a[4]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, UniqueTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UniqueTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UniqueTest2());

	{
		hamon::vector<std::shared_ptr<int>> a;
		a.emplace_back(new int(1));
		a.emplace_back(new int(4));
		a.emplace_back(new int(4));
		a.emplace_back(new int(2));
		a.emplace_back(new int(1));
		a.emplace_back(new int(1));
		a.emplace_back(new int(3));
		a.emplace_back(new int(3));
		a.emplace_back(new int(3));
		auto ret = hamon::unique(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 5));

		EXPECT_EQ(1, *a[0]);
		EXPECT_EQ(4, *a[1]);
		EXPECT_EQ(2, *a[2]);
		EXPECT_EQ(1, *a[3]);
		EXPECT_EQ(3, *a[4]);
	}
	{
		hamon::vector<int> a;
		auto ret = hamon::unique(hamon::begin(a), hamon::end(a), [](int, int){ return true; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
		EXPECT_TRUE(a.empty());
	}
	{
		hamon::list<std::unique_ptr<int>> a;
		a.emplace_back(new int(1));
		a.emplace_back(new int(1));
		a.emplace_back(new int(1));
		a.emplace_back(new int(4));
		a.emplace_back(new int(4));
		a.emplace_back(new int(2));
		a.emplace_back(new int(3));
		a.emplace_back(new int(3));
		a.emplace_back(new int(3));
		auto ret = hamon::unique(hamon::begin(a), hamon::end(a), pred2());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));

		auto it = a.begin();
		EXPECT_EQ(1, *(*it++));
		EXPECT_EQ(4, *(*it++));
		EXPECT_EQ(2, *(*it++));
		EXPECT_EQ(3, *(*it++));
		EXPECT_TRUE(it == ret);
	}
	{
		hamon::list<int> a;
		auto ret = hamon::unique(hamon::begin(a), hamon::end(a), [](int, int){ return false; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
		EXPECT_TRUE(a.empty());
	}
}

#undef VERIFY

}	// namespace unique_test

}	// namespace hamon_algorithm_test
