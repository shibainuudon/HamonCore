/**
 *	@file	unit_test_algorithm_count.cpp
 *
 *	@brief	count のテスト
 */

#include <hamon/algorithm/count.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace count_test
{

struct Point
{
	int x;
	int y;
};

inline HAMON_CXX11_CONSTEXPR bool
operator==(Point const& lhs, Point const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	int const a[] {1, 3, 1, 2, 3, 1, 2, 2, 1};
	VERIFY(0 == hamon::count(hamon::begin(a), hamon::end(a), 0));
	VERIFY(4 == hamon::count(hamon::begin(a), hamon::end(a), 1));
	VERIFY(3 == hamon::count(hamon::begin(a), hamon::end(a), 2));
	VERIFY(2 == hamon::count(hamon::begin(a), hamon::end(a), 3));
	VERIFY(0 == hamon::count(hamon::begin(a), hamon::end(a), 4));

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	hamon::array<int, 21> a{ { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6 } };
	VERIFY(0 == hamon::count(hamon::begin(a), hamon::end(a), 0));
	VERIFY(2 == hamon::count(hamon::begin(a), hamon::end(a), 1));
	VERIFY(2 == hamon::count(hamon::begin(a), hamon::end(a), 2));
	VERIFY(4 == hamon::count(hamon::begin(a), hamon::end(a), 3));
	VERIFY(2 == hamon::count(hamon::begin(a), hamon::end(a), 4));
	VERIFY(3 == hamon::count(hamon::begin(a), hamon::end(a), 5));
	VERIFY(2 == hamon::count(hamon::begin(a), hamon::end(a), 6));
	VERIFY(1 == hamon::count(hamon::begin(a), hamon::end(a), 7));
	VERIFY(2 == hamon::count(hamon::begin(a), hamon::end(a), 8));
	VERIFY(3 == hamon::count(hamon::begin(a), hamon::end(a), 9));

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	Point const a[]
	{
		{1, 2}, {1, 1}, {1, 2}, {2, 1},
	};

	VERIFY(1 == hamon::count(hamon::begin(a), hamon::end(a), {1, 1}));
	VERIFY(2 == hamon::count(hamon::begin(a), hamon::end(a), {1, 2}));
	VERIFY(0 == hamon::count(hamon::begin(a), hamon::end(a), {1, 3}));
	VERIFY(1 == hamon::count(hamon::begin(a), hamon::end(a), {2, 1}));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, CountTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());

	{
		const hamon::vector<int> v{10, 20, 10, 30, 10, 20};
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v),  0));
		EXPECT_EQ(3, hamon::count(hamon::begin(v), hamon::end(v), 10));
		EXPECT_EQ(2, hamon::count(hamon::begin(v), hamon::end(v), 20));
		EXPECT_EQ(1, hamon::count(hamon::begin(v), hamon::end(v), 30));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 40));
	}
	{
		const hamon::vector<int> v;
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v),  0));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 10));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 20));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 30));
		EXPECT_EQ(0, hamon::count(hamon::begin(v), hamon::end(v), 40));
	}
	{
		const hamon::list<int> l{10, 20, 40, 40, 10};
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l),  0));
		EXPECT_EQ(2, hamon::count(hamon::begin(l), hamon::end(l), 10));
		EXPECT_EQ(1, hamon::count(hamon::begin(l), hamon::end(l), 20));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 30));
		EXPECT_EQ(2, hamon::count(hamon::begin(l), hamon::end(l), 40));
	}
	{
		const hamon::list<int> l;
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l),  0));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 10));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 20));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 30));
		EXPECT_EQ(0, hamon::count(hamon::begin(l), hamon::end(l), 40));
	}
}

}	// namespace count_test

}	// namespace hamon_algorithm_test
